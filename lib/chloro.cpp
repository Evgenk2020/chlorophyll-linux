#include "../include/chloro.h"

class cl_a_allowance : public chloro_data
{
public:
    virtual float get_chloro(ch_data dat) const;
};

class cl_b_allowance : public chloro_data
{
public:
    virtual float get_chloro(ch_data dat) const;
};

class final_a : public chloro_data
{
private:
    cl_a_allowance _all;

public:
    virtual float get_chloro(ch_data dat) const;
};

class final_b : public chloro_data
{
private:
    cl_b_allowance _all;

public:
    virtual float get_chloro(ch_data dat) const;
};

class cl_sum : public chloro_data
{
private:
    final_a fin_a;
    final_b fin_b;

public:
    virtual float get_chloro(ch_data dat) const;
};

//-------------------------------------------------------

std::unique_ptr<chloro_data> chlor_allowance::chloro_data_get(chlor_data_type types)
{
    switch (types)
    {
    case chlor_data_type::chloro_a_allowance:
    {
        return std::make_unique<cl_a_allowance>();
    }

    case chlor_data_type::chloro_b_allowance:
    {
        return std::make_unique<cl_b_allowance>();
    }

    case chlor_data_type::chloro_a_mg:
    {
        return std::make_unique<final_a>();
    }

    case chlor_data_type::chloro_b_mg:
    {
        return std::make_unique<final_b>();
    }

    case chlor_data_type::chloro_sum:
    {
        return std::make_unique<cl_sum>();
    }

    default:
    {
        throw "error.. data are absent";
    }
    }
}

float cl_a_allowance::get_chloro(ch_data dat) const { return static_cast<float>(13.7 * dat.at(field::d665) - 5.76 * dat.at(field::d649)); }
float cl_b_allowance::get_chloro(ch_data dat) const { return static_cast<float>(25.8 * dat.at(field::d649) - 7.6 * dat.at(field::d665)); }
float final_a::get_chloro(ch_data dat) const { return static_cast<float>(dat.at(field::vol_filtrate) * 0.1 * ((dat.at(field::vol_photo_probe) + dat.at(field::vol_photo_alch)) / dat.at(field::vol_photo_probe)) * _all.get_chloro(dat) / dat.at(field::mass_of_probe)); }
float final_b::get_chloro(ch_data dat) const { return static_cast<float>(dat.at(field::vol_filtrate) * 0.1 * ((dat.at(field::vol_photo_probe) + dat.at(field::vol_photo_alch)) / dat.at(field::vol_photo_probe)) * _all.get_chloro(dat) / dat.at(field::mass_of_probe)); }
float cl_sum::get_chloro(ch_data dat) const { return static_cast<float>(fin_a.get_chloro(dat) + fin_b.get_chloro(dat)); }