#ifndef CHLORO_H
#define CHLORO_H

#include <memory>
#include <array>

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
    ~chloro_data() = default;
};

class chlor_allowance
{
public:
    static std::unique_ptr<chloro_data> chloro_data_get(chlor_data_type types);
    ~chlor_allowance() = default;
};

#endif // CHLORO_H
