#include <map>
#include <vector>
#include <string>
#include <charconv>
#include <expected>
#include <tuple>
#include <iostream>

struct ch_data
{
    float mass_of_probe;
    float vol_filtrate;
    float vol_photo_probe;
    float vol_photo_alch;
    float d665;
    float d649;
};

std::expected<float, std::string> to_float(std::string_view sv)
{
    float value{};
    auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);

    if (ec != std::errc())
        return std::unexpected("Invalid float: " + std::string(sv));

    return value;
}

std::expected<ch_data, std::string>
make_ch_data(const std::map<std::string, std::vector<std::string>>& args)
{
    auto it = args.find("-d");
    if (it == args.end())
        return std::unexpected("Key -d not found");

    const auto& values = it->second;

    ch_data data{};
    auto tied = std::tie(
        data.mass_of_probe,
        data.vol_filtrate,
        data.vol_photo_probe,
        data.vol_photo_alch,
        data.d665,
        data.d649
    );

    constexpr std::size_t field_count =
        std::tuple_size_v<decltype(tied)>;

    if (values.size() != field_count)
        return std::unexpected("Expected 6 numeric arguments after -d");

    std::size_t index = 0;

    auto result = std::apply(
        [&](auto&... fields) -> std::expected<void, std::string>
        {
            (([&] {
                auto parsed = to_float(values[index]);
                if (!parsed)
                    throw parsed.error(); // локально, перехватим ниже
                fields = *parsed;
                ++index;
            }()), ...);

            return {};
        },
        tied
    );

    return data;
}

