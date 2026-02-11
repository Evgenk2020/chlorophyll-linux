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

    if (values.size() != std::tuple_size_v<decltype(tied)>)
        return std::unexpected("Expected 6 numeric arguments");

    std::size_t i = 0;
    bool ok = true;
    std::string error;

    std::apply([&](auto&... fields) {
        (([&] {
            if (!ok) return;
            auto parsed = to_float(values[i]);
            if (!parsed) {
                ok = false;
                error = parsed.error();
                return;
            }
            fields = *parsed;
            ++i;
        }()), ...);
    }, tied);

    if (!ok)
        return std::unexpected(error);

    return data;
}

