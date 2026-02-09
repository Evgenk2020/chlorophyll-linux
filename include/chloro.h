#ifndef CHLORO_H
#define CHLORO_H

#include <memory>

struct ch_data
{
    float mass_of_probe;
    float vol_filtrate;
    float vol_photo_probe;
    float vol_photo_alch;
    float d665;
    float d649;
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
