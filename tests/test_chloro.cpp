#include <gtest/gtest.h>
#include "../include/chloro.h"

// Test chlorophyll A allowance calculation
TEST(ChlorophyllTest, ChloroAAllowance)
{
    chlor_allowance allow;
    ch_data data;
    data.at(field::d665) = 1.25f;
    data.at(field::d649) = 0.45f;

    // Formula: 13.7 * D665 - 5.76 * D649
    float expected = 13.7f * 1.25f - 5.76f * 0.45f;
    float result = allow.chloro_data_get(chlor_data_type::chloro_a_allowance)->get_chloro(data);

    EXPECT_FLOAT_EQ(result, expected);
}

// Test chlorophyll B allowance calculation
TEST(ChlorophyllTest, ChloroBAllowance)
{
    chlor_allowance allow;
    ch_data data;
    data.at(field::d665) = 1.25f;
    data.at(field::d649) = 0.45f;

    // Formula: 25.8 * D649 - 7.6 * D665
    float expected = 25.8f * 0.45f - 7.6f * 1.25f;
    float result = allow.chloro_data_get(chlor_data_type::chloro_b_allowance)->get_chloro(data);

    EXPECT_FLOAT_EQ(result, expected);
}

// Test chlorophyll A content in mg per 100g leaf
TEST(ChlorophyllTest, ChloroAContent)
{
    chlor_allowance allow;
    ch_data data;
    data.at(field::mass_of_probe) = 1.3f;
    data.at(field::vol_filtrate) = 25.0f;
    data.at(field::vol_photo_probe) = 3.0f;
    data.at(field::vol_photo_alch) = 5.0f;
    data.at(field::d665) = 1.25f;
    data.at(field::d649) = 0.45f;

    float conc_a = 13.7f * 1.25f - 5.76f * 0.45f;
    float expected = 25.0f * 0.1f * ((3.0f + 5.0f) / 3.0f) * conc_a / 1.3f;
    float result = allow.chloro_data_get(chlor_data_type::chloro_a_mg)->get_chloro(data);

    EXPECT_FLOAT_EQ(result, expected);
}

// Test chlorophyll B content in mg per 100g leaf
TEST(ChlorophyllTest, ChloroBContent)
{
    chlor_allowance allow;
    ch_data data;
    data.at(field::mass_of_probe) = 1.3f;
    data.at(field::vol_filtrate) = 25.0f;
    data.at(field::vol_photo_probe) = 3.0f;
    data.at(field::vol_photo_alch) = 5.0f;
    data.at(field::d665) = 1.25f;
    data.at(field::d649) = 0.45f;

    float conc_b = 25.8f * 0.45f - 7.6f * 1.25f;
    float expected = 25.0f * 0.1f * ((3.0f + 5.0f) / 3.0f) * conc_b / 1.3f;
    float result = allow.chloro_data_get(chlor_data_type::chloro_b_mg)->get_chloro(data);

    EXPECT_FLOAT_EQ(result, expected);
}

// Test total chlorophyll sum
TEST(ChlorophyllTest, ChloroSum)
{
    chlor_allowance allow;
    ch_data data;
    data.at(field::mass_of_probe) = 1.3f;
    data.at(field::vol_filtrate) = 25.0f;
    data.at(field::vol_photo_probe) = 3.0f;
    data.at(field::vol_photo_alch) = 5.0f;
    data.at(field::d665) = 1.25f;
    data.at(field::d649) = 0.45f;

    float a = allow.chloro_data_get(chlor_data_type::chloro_a_mg)->get_chloro(data);
    float b = allow.chloro_data_get(chlor_data_type::chloro_b_mg)->get_chloro(data);
    float expected = a + b;
    float result = allow.chloro_data_get(chlor_data_type::chloro_sum)->get_chloro(data);

    EXPECT_FLOAT_EQ(result, expected);
}

// Test division by zero protection for mass_of_probe
TEST(ChlorophyllTest, DivisionByZeroMassOfProbe)
{
    chlor_allowance allow;
    ch_data data;
    data.at(field::mass_of_probe) = 0.0f;
    data.at(field::vol_filtrate) = 25.0f;
    data.at(field::vol_photo_probe) = 3.0f;
    data.at(field::vol_photo_alch) = 5.0f;
    data.at(field::d665) = 1.25f;
    data.at(field::d649) = 0.45f;

    EXPECT_THROW(allow.chloro_data_get(chlor_data_type::chloro_a_mg)->get_chloro(data), std::runtime_error);
    EXPECT_THROW(allow.chloro_data_get(chlor_data_type::chloro_b_mg)->get_chloro(data), std::runtime_error);
}

// Test division by zero protection for vol_photo_probe
TEST(ChlorophyllTest, DivisionByZeroVolPhotoProbe)
{
    chlor_allowance allow;
    ch_data data;
    data.at(field::mass_of_probe) = 1.3f;
    data.at(field::vol_filtrate) = 25.0f;
    data.at(field::vol_photo_probe) = 0.0f;
    data.at(field::vol_photo_alch) = 5.0f;
    data.at(field::d665) = 1.25f;
    data.at(field::d649) = 0.45f;

    EXPECT_THROW(allow.chloro_data_get(chlor_data_type::chloro_a_mg)->get_chloro(data), std::runtime_error);
    EXPECT_THROW(allow.chloro_data_get(chlor_data_type::chloro_b_mg)->get_chloro(data), std::runtime_error);
}

// Test ch_data field access
TEST(ChlorophyllTest, ChDataFieldAccess)
{
    ch_data data;
    data.at(field::mass_of_probe) = 1.0f;
    data.at(field::vol_filtrate) = 2.0f;
    data.at(field::vol_photo_probe) = 3.0f;
    data.at(field::vol_photo_alch) = 4.0f;
    data.at(field::d665) = 5.0f;
    data.at(field::d649) = 6.0f;

    EXPECT_FLOAT_EQ(data.at(field::mass_of_probe), 1.0f);
    EXPECT_FLOAT_EQ(data.at(field::vol_filtrate), 2.0f);
    EXPECT_FLOAT_EQ(data.at(field::vol_photo_probe), 3.0f);
    EXPECT_FLOAT_EQ(data.at(field::vol_photo_alch), 4.0f);
    EXPECT_FLOAT_EQ(data.at(field::d665), 5.0f);
    EXPECT_FLOAT_EQ(data.at(field::d649), 6.0f);
}

// Test factory returns correct types
TEST(ChlorophyllTest, FactoryReturnsCorrectTypes)
{
    chlor_allowance allow;

    EXPECT_NE(allow.chloro_data_get(chlor_data_type::chloro_a_allowance), nullptr);
    EXPECT_NE(allow.chloro_data_get(chlor_data_type::chloro_b_allowance), nullptr);
    EXPECT_NE(allow.chloro_data_get(chlor_data_type::chloro_a_mg), nullptr);
    EXPECT_NE(allow.chloro_data_get(chlor_data_type::chloro_b_mg), nullptr);
    EXPECT_NE(allow.chloro_data_get(chlor_data_type::chloro_sum), nullptr);
}
