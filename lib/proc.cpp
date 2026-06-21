#include "../include/proc.h"
#include <charconv>
#include <print>
#include <limits>
#include <iostream>

decree::decree(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        _args.push_back(std::string_view(argv[i]));
    }
}

void processing::going()
{
    if (!_args.empty() && (_args[0] == "-h" || _args[0] == "--help" || _args[0] == "-i"))
    {
        helping();
        return;
    }

    auto parse_result = parsing();

    if (!parse_result)
    {
        std::println(stderr, "Помилка: {}", parse_result.error());
        std::println(stderr, "Спробуйте знову або використовуйте -h для довідки.");
        std::exit(EXIT_FAILURE);
    }

    counting(*parse_result);
}

void decree::helping()
{
    if (_args[0] == "-h" || _args[0] == "--help")
    {
        print_info{new help_info}._print();
    }

    else if (_args[0] == "-i")
    {
        print_info{new inf_info}._print();
    }
}

static std::expected<float, std::string> parse_float(std::string_view str)
{
    float val{};
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), val);

    if (ec != std::errc())
    {
        return std::unexpected("Некоректне числове значення '" + std::string(str) + "'");
    }

    if (val < 0.0f)
    {
        return std::unexpected("Значення не може бути від'ємним");
    }

    return val;
}

ch_data decree::run_interactive_wizard()
{
    std::println("\n=== Інтерактивний режим введення даних ===");
    ch_data data;

    auto prompt_field = [](field f) -> float
    {
        while (true)
        {
            std::print("{}: ", ch_data::label_of(f));
            std::string input;

            if (!(std::cin >> input))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            auto res = parse_float(input);

            if (res)
            {
                return *res;
            }

            std::println(stderr, " -> Помилка: {}", res.error());
        }
    };

    data.at(field::mass_of_probe) = prompt_field(field::mass_of_probe);
    data.at(field::vol_filtrate) = prompt_field(field::vol_filtrate);
    data.at(field::vol_photo_probe) = prompt_field(field::vol_photo_probe);
    data.at(field::vol_photo_alch) = prompt_field(field::vol_photo_alch);
    data.at(field::d665) = prompt_field(field::d665);
    data.at(field::d649) = prompt_field(field::d649);

    std::print("\nЗберегти результати у CSV файл? (y/n): ");
    char choice;
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        _save_to_file = true;
    }

    return data;
}

std::expected<ch_data, std::string> decree::parse_flags()
{
    ch_data data;
    std::array<bool, static_cast<int>(field::count)> set_flags{};

    for (size_t i = 0; i < _args.size(); ++i)
    {
        std::string_view arg = _args[i];

        if (arg == "-df" || arg == "--file")
        {
            _save_to_file = true;
            continue;
        }

        if (arg == "-j" || arg == "--json")
        {
            _json_output = true;
            continue;
        }

        field target_field;
        bool found = false;

        if (arg == "-w" || arg == "--weight")
        {
            target_field = field::mass_of_probe;
            found = true;
        }

        else if (arg == "-f" || arg == "--filt")
        {
            target_field = field::vol_filtrate;
            found = true;
        }

        else if (arg == "-p" || arg == "--prob")
        {
            target_field = field::vol_photo_probe;
            found = true;
        }

        else if (arg == "-s" || arg == "--solv")
        {
            target_field = field::vol_photo_alch;
            found = true;
        }

        else if (arg == "--d665")
        {
            target_field = field::d665;
            found = true;
        }

        else if (arg == "--d649")
        {
            target_field = field::d649;
            found = true;
        }

        if (found)
        {
            if (i + 1 >= _args.size())
            {
                return std::unexpected("Відсутнє значення для прапорця " + std::string(arg));
            }

            auto val_res = parse_float(_args[++i]);

            if (!val_res)
            {
                return std::unexpected(std::string(arg) + ": " + val_res.error());
            }

            data.at(target_field) = *val_res;
            set_flags[static_cast<int>(target_field)] = true;
        }
    }

    for (int i = 0; i < static_cast<int>(field::count); ++i)
    {
        if (!set_flags[i])
        {
            return std::unexpected("Не вказано обов'язковий параметр: " + std::string(ch_data::label_of(static_cast<field>(i))));
        }
    }

    return data;
}

std::expected<ch_data, std::string> decree::parsing()
{
    if (_args.empty() || (_args.size() == 1 && (_args[0] == "-df" || _args[0] == "--file")))
    {
        if (!_args.empty())
        {
            _save_to_file = true;
        }

        return run_interactive_wizard();
    }

    // Protection for Node.js: if ONLY the --json flag is passed without parameters,
    // we do not switch to interactive mode, but return an error.
    if (_args.size() == 1 && (_args[0] == "-j" || _args[0] == "--json"))
    {
        return std::unexpected("Для JSON режиму необхідно вказати всі параметри розрахунку (-w, -f, -p, -s, --d665, --d649).");
    }

    auto res = parse_flags();
    if (!res)
    {
        return res;
    }

    if (res->at(field::vol_photo_probe) == 0.0f || res->at(field::mass_of_probe) == 0.0f)
    {
        return std::unexpected("Ділення на нуль! Маса зразка та об'єм проби мають бути більшими за 0.");
    }

    return res;
}

void decree::counting(const ch_data &datas)
{
    if (_json_output)
    {
        print_info inf(new json_info);
        inf._print(datas);
    }
    else if (_save_to_file)
    {
        print_info inf(new file_info);
        inf._print(datas);
    }
    else
    {
        print_info inf(new screen_info);
        inf._print(datas);
    }
}