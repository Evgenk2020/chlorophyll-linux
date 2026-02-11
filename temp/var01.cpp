#include <map>
#include <vector>
#include <string>
#include <charconv>
#include <expected>
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
    auto result = std::from_chars(sv.data(), sv.data() + sv.size(), value);

    if (result.ec != std::errc())
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

    if (values.size() != 6)
        return std::unexpected("Expected 6 numeric arguments after -d");

    ch_data data{};

    float* fields[] = {
        &data.mass_of_probe,
        &data.vol_filtrate,
        &data.vol_photo_probe,
        &data.vol_photo_alch,
        &data.d665,
        &data.d649
    };

    for (size_t i = 0; i < 6; ++i)
    {
        auto parsed = to_float(values[i]);
        if (!parsed)
            return std::unexpected(parsed.error());

        *fields[i] = *parsed;
    }

    return data;
}

