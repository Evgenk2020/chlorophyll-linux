#ifndef CHLORO_H
#define CHLORO_H

#include <memory>
#include <array>
#include <string_view>

enum class field
{
    mass_of_probe,
    vol_filtrate,
    vol_photo_probe,
    vol_photo_alch,
    d665,
    d649,
    count
};

struct ch_data
{
    std::array<float, static_cast<int>(field::count)> values{};

    float &at(field f)
    {
        return values[static_cast<int>(f)];
    }

    const float &at(field f) const
    {
        return values[static_cast<int>(f)];
    }

    // Helper method for getting Ukrainian field names in interactive mode
    static std::string_view label_of(field f)
    {
        switch (f)
        {
        case field::mass_of_probe:
            return "Наважка (г)";
        case field::vol_filtrate:
            return "Об'єм фільтрату (мл)";
        case field::vol_photo_probe:
            return "Фотометрична проба (мл)";
        case field::vol_photo_alch:
            return "Фотометричний розчинник (мл)";
        case field::d665:
            return "Показник фотометра D665";
        case field::d649:
            return "Показник фотометра D649";
        default:
            return "Невідоме поле";
        }
    }
};

enum class chlor_data_type
{
    chloro_a_allowance,
    chloro_b_allowance,
    chloro_a_mg,
    chloro_b_mg,
    chloro_sum
};

class chloro_data
{
public:
    virtual float get_chloro(ch_data dat) const = 0;
    virtual ~chloro_data() = default;
};

class chlor_allowance
{
public:
    static std::unique_ptr<chloro_data> chloro_data_get(chlor_data_type types);
    ~chlor_allowance() = default;
};

#endif // CHLORO_H