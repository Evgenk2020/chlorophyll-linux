#include "../include/output.h"

#include <iostream>
#include <fstream>
#include <locale>
#include <print>

general_info::~general_info() {}

void help_info::see_info()
{
       std::println(
           "*** Визначенні концентрації хлорофілів ***\n"
           "\n"
           "Для виводу в термінал:\n"
           "-d [наважка (г)] [фільтарт (мл)] [фотометрична проба (мл)] [фотометричний розчинник (мл)] [показник фотометра 665] [показник фотометра 649]\n"
           "\n"
           "Для виводу в файл:\n"
           "-df [наважка (г)] [фільтарт (мл)] [фотометрична проба (мл)] [фотометричний розчинник (мл)] [показник фотометра 665] [показник фотометра 649]\n"
           "\n"
           "Для виводу довідки:\n"
           "-h | --help\n"
           "\n"
           "Додаткова інформаці\n"
           "-i");
}

void inf_info::see_info()
{
       std::println(
           "Для розрахунку концентрації хлорофілів A і B в розчині визначають його оптичну густину за довжини хвилі,\n"
           "що відповідає максимумам спектра поглинання досліджуваних пігментів. Для хлорофілу A в 96% етанолі максимум\n"
           "поглинання λ = 665 нм, для хлорофілу B λ = 649 нм.\n"
           "\n"
           "Формули для розчинів хлорофілу в 96% етанолі:\n"
           "концентрація хлорофіла A (мг/л) = 13.7 * D665 - 5.76 * D649\n"
           "концентрація хлорофіла B (мг/л) = 25.8 * D649 - 7.6 * D665");
}

//--------------------------------------------------

data_info::~data_info() {}

void screen_info::see_info(ch_data *dat)
{
       chlor_allowance allow;

       enum class mesure
       {
              gram,
              mililiter,
              empty,
              mg_photo_probe,
              mg_leaf
       };

       auto line = [&](mesure type, const std::string_view &label, const auto &value) -> void
       {
              constexpr std::string_view gram = "{} {} г\n";
              constexpr std::string_view mililiter = "{} {} мл\n";
              constexpr std::string_view empty = "{} {}\n";
              constexpr std::string_view mg_photo_probe = "{} {} мг/л фотометричного зразка\n";
              constexpr std::string_view mg_leaf = "{} {} мг/100 г листка\n";

              switch (type)
              {
              case mesure::gram:
                     std::print(gram, label, value);
                     break;

              case mesure::mililiter:
                     std::print(mililiter, label, value);
                     break;

              case mesure::empty:
                     std::print(empty, label, value);
                     break;

              case mesure::mg_photo_probe:
                     std::print(mg_photo_probe, label, value);
                     break;

              case mesure::mg_leaf:
                     std::print(mg_leaf, label, value);
                     break;
              }
       };

       line(mesure::gram, "Маса зразка:", dat->mass_of_probe);
       line(mesure::mililiter, "Об'єм фільтрату:", dat->vol_filtrate);
       line(mesure::mililiter, "Об'єм фотометричної проби:", dat->vol_photo_probe);
       line(mesure::mililiter, "Об'єм розчинника для розведення:", dat->vol_photo_alch);
       line(mesure::empty, "Фотометричний показник D665:", dat->d665);
       line(mesure::empty, "Фотометричний показник D649:", dat->d649);
       std::print("\n");
       line(mesure::mg_photo_probe, "Концентрація хлорофілу А:", allow.chloro_data_get(chlor_data_type::chloro_a_allowance)->get_chloro(*dat));
       line(mesure::mg_photo_probe, "Концентрація хлорофілу B:", allow.chloro_data_get(chlor_data_type::chloro_b_allowance)->get_chloro(*dat));
       line(mesure::mg_leaf, "Вміст хлорофілу А:", allow.chloro_data_get(chlor_data_type::chloro_a_mg)->get_chloro(*dat));
       line(mesure::mg_leaf, "Вміст хлорофілу B:", allow.chloro_data_get(chlor_data_type::chloro_b_mg)->get_chloro(*dat));
       line(mesure::mg_leaf, "Сума хлорофілів А + B:", allow.chloro_data_get(chlor_data_type::chloro_sum)->get_chloro(*dat));
}

void file_info::see_info(ch_data *dat)
{
       std::ofstream writer("chlor-data.csv", std::ios::app);

       const char coma = ',';
       const char quo = '\"';

       std::locale m_loc("uk_UA.utf8");
       writer.imbue(m_loc);

       chlor_allowance allow;

       writer << quo << "Маса зразка:" << quo << coma << quo << dat->mass_of_probe << quo << coma << quo << "г" << quo << std::endl
              << quo << "Об'єм фільтрату:" << quo << coma << quo << dat->vol_filtrate << quo << coma << quo << "мл" << quo << std::endl
              << quo << "Об'єм фотометричної проби:" << quo << coma << quo << dat->vol_photo_probe << quo << coma << quo << "мл" << quo << std::endl
              << quo << "Об'єм розчинника для розведення:" << quo << coma << quo << dat->vol_photo_alch << quo << coma << quo << "мл" << quo << std::endl
              << quo << "Фотометричний показник D665:" << quo << coma << quo << dat->d665 << quo << std::endl
              << quo << "Фотометричний показник D649:" << quo << coma << quo << dat->d649 << quo << std::endl
              << std::endl;

       writer << quo << "Концентрація хлорофілу А:" << quo << coma
              << quo << allow.chloro_data_get(chlor_data_type::chloro_a_allowance)->get_chloro(*dat) << quo << coma << quo << "мг/л фотометричного зразка" << quo << std::endl;

       writer << quo << "Концентрація хлорофілу B:" << quo << coma
              << quo << allow.chloro_data_get(chlor_data_type::chloro_b_allowance)->get_chloro(*dat) << quo << coma << quo << "мг/л фотометричного зразка" << quo << std::endl;

       writer << quo << "Вміст хлорофілу А:" << quo << coma
              << quo << allow.chloro_data_get(chlor_data_type::chloro_a_mg)->get_chloro(*dat) << quo << coma << quo << "мг/100 г листка" << quo << std::endl;

       writer << quo << "Вміст хлорофілу B:" << quo << coma
              << quo << allow.chloro_data_get(chlor_data_type::chloro_b_mg)->get_chloro(*dat) << quo << coma << quo << "мг/100 г листка" << quo << std::endl;

       writer << quo << "Сума хлорофілів А + B:" << quo << coma
              << quo << allow.chloro_data_get(chlor_data_type::chloro_sum)->get_chloro(*dat) << quo << coma << quo << "мг/100 г листка" << quo << std::endl;
       writer << "" << std::endl;

       std::cout << "Дані додані у файл chlor-data.csv" << std::endl;
}

//--------------------------------------------------

print_info::print_info(general_info *temp) : g_info(temp) {}
print_info::print_info(data_info *temp) : d_info(temp) {}

void print_info::_print() { g_info->see_info(); }
void print_info::_print(ch_data temp) { d_info->see_info(&temp); }

print_info::~print_info()
{
       delete g_info;
       g_info = nullptr;

       delete d_info;
       d_info = nullptr;
}
