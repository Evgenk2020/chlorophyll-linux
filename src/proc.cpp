#include "../include/proc.h"

#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <print>
#include <string>
#include <utility>

decree::decree(int argc, char **argv)
{
    _args.reserve(static_cast<std::size_t>(argc > 1 ? argc - 1 : 0));

    for (int i = 1; i < argc; ++i)
    {
        _args.emplace_back(argv[i]);
    }
}

// ============================================================
// processing
// ============================================================

void processing::going()
{
    if (!_args.empty())
    {
        const auto command = _args.front();

        if (command == "-h" || command == "--help" || command == "-i")
        {
            helping();
            return;
        }
    }

    const auto result = parsing();

    if (!result)
    {
        std::println(stderr, "Помилка: {}", result.error());
        std::println(stderr, "Спробуйте знову або використовуйте -h для довідки.");
        std::exit(EXIT_FAILURE);
    }

    counting(*result);
}

// ============================================================
// help
// ============================================================

void decree::helping()
{
    if (_args[0] == "-h" || _args[0] == "--help")
    {
        print_info{new help_info}._print();
        return;
    }

    if (_args[0] == "-i")
    {
        print_info{new inf_info}._print();
    }
}

// ============================================================
// float parsing
// ============================================================

std::expected<float, std::string> decree::parse_float(std::string_view str)
{
    float value{};

    const auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);

    // Check that the entire string has been processed.
    if (ec != std::errc() || ptr != str.data() + str.size())
    {
        return std::unexpected("Некоректне числове значення '" + std::string(str) + "'");
    }

    if (!std::isfinite(value))
    {
        return std::unexpected("Числове значення має бути скінченним");
    }

    if (value < 0.0f)
    {
        return std::unexpected("Значення не може бути від'ємним");
    }

    return value;
}

// ============================================================
// interactive mode
// ============================================================

ch_data decree::run_interactive_wizard()
{
    std::println("\n=== Інтерактивний режим введення даних ===");
    ch_data data;

    const auto prompt_field = [](field target) -> float
    {
        while (true)
        {
            std::print("{}: ", ch_data::label_of(target));
            std::string input;

            if (std::cin >> input)
            {
                const auto result = parse_float(input);

                if (result)
                {
                    return *result;
                }

                std::println(stderr, " -> Помилка: {}", result.error());
                continue;
            }

            // EOF — further interactive reading is not possible
            if (std::cin.eof())
            {
                std::println(stderr, " -> Помилка: завершено введення.");
                std::exit(EXIT_FAILURE);
            }

            // Common typing error
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::println(stderr, " -> Помилка: некоректне введення.");
        }
    };

    data.at(field::mass_of_probe) = prompt_field(field::mass_of_probe);
    data.at(field::vol_filtrate) = prompt_field(field::vol_filtrate);
    data.at(field::vol_photo_probe) = prompt_field(field::vol_photo_probe);
    data.at(field::vol_photo_alch) = prompt_field(field::vol_photo_alch);
    data.at(field::d665) = prompt_field(field::d665);
    data.at(field::d649) = prompt_field(field::d649);
    std::print("\nЗберегти результати у CSV файл? (y/n): ");

    char choice{};

    if (std::cin >> choice && (choice == 'y' || choice == 'Y'))
    {
        _save_to_file = true;
    }

    return data;
}

// ============================================================
// command-line flags
// ============================================================

std::expected<ch_data, std::string> decree::parse_flags()
{
    ch_data data;
    std::array<bool, static_cast<int>(field::count)> set_flags{};

    enum class flag_type
    {
        file,
        json,
        value
    };

    struct flag_info
    {
        std::string_view name;
        flag_type type;
        field target;
    };

    // Unified description of all supported CLI flags
    //
    // For file/json, the target field is not used
    // For value, it specifies the ch_data field
    constexpr std::array flags{
        flag_info{"-df", flag_type::file, field::count},
        flag_info{"--file", flag_type::file, field::count},

        flag_info{"-j", flag_type::json, field::count},
        flag_info{"--json", flag_type::json, field::count},

        flag_info{"-w", flag_type::value, field::mass_of_probe},
        flag_info{"--weight", flag_type::value, field::mass_of_probe},

        flag_info{"-f", flag_type::value, field::vol_filtrate},
        flag_info{"--filt", flag_type::value, field::vol_filtrate},

        flag_info{"-p", flag_type::value, field::vol_photo_probe},
        flag_info{"--prob", flag_type::value, field::vol_photo_probe},

        flag_info{"-s", flag_type::value, field::vol_photo_alch},
        flag_info{"--solv", flag_type::value, field::vol_photo_alch},

        flag_info{"--d665", flag_type::value, field::d665},
        flag_info{"--d649", flag_type::value, field::d649}};

    for (std::size_t i = 0; i < _args.size(); ++i)
    {
        const auto arg = _args[i];
        const auto flag = std::find_if(flags.begin(), flags.end(), [arg](const flag_info &info) { return info.name == arg; });

        if (flag == flags.end())
        {
            continue;
        }

        switch (flag->type)
        {
        case flag_type::file:
            _save_to_file = true;
            continue;

        case flag_type::json:
            _json_output = true;
            continue;

        case flag_type::value:
            break;
        }

        // A flag of type 'value' must have a subsequent argument
        if (i + 1 >= _args.size())
        {
            return std::unexpected("Відсутнє значення для прапорця " + std::string(arg));
        }

        const auto value = parse_float(_args[++i]);

        if (!value)
        {
            return std::unexpected(std::string(arg) + ": " + value.error());
        }

        data.at(flag->target) = *value;
        set_flags[static_cast<int>(flag->target)] = true;
    }

    // All six fields are mandatory
    for (int i = 0; i < static_cast<int>(field::count); ++i)
    {
        if (set_flags[i])
        {
            continue;
        }

        const auto missing_field = static_cast<field>(i);
        return std::unexpected("Не вказано обов'язковий параметр: " + std::string(ch_data::label_of(missing_field)));
    }

    return data;
}

// ============================================================
// parsing
// ============================================================

std::expected<ch_data, std::string> decree::parsing()
{
    // No arguments or only --file passed:
    // start interactive mode
    if (_args.empty() || (_args.size() == 1 && (_args[0] == "-df" || _args[0] == "--file")))
    {
        if (!_args.empty())
        {
            _save_to_file = true;
        }

        return run_interactive_wizard();
    }

    // Special case for Node.js:
    // --json without arguments should not launch the wizard
    if (_args.size() == 1 && (_args[0] == "-j" || _args[0] == "--json"))
    {
        return std::unexpected(
            "Для JSON режиму необхідно вказати всі параметри "
            "розрахунку (-w, -f, -p, -s, --d665, --d649).");
    }

    auto result = parse_flags();

    if (!result)
    {
        return result;
    }

    const auto &data = *result;

    if (data.at(field::vol_photo_probe) == 0.0f || data.at(field::mass_of_probe) == 0.0f)
    {
        return std::unexpected(
            "Ділення на нуль! Маса зразка та об'єм проби "
            "мають бути більшими за 0.");
    }

    return result;
}

// ============================================================
// output
// ============================================================

void decree::counting(const ch_data &datas)
{
    if (_json_output)
    {
        print_info{new json_info}._print(datas);
        return;
    }

    if (_save_to_file)
    {
        print_info{new file_info}._print(datas);
        return;
    }

    print_info{new screen_info}._print(datas);
}
