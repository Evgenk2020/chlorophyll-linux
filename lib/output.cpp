#include "../include/output.h"

#include <iostream>
#include <fstream>
#include <locale>
#include <print>
#include <filesystem>

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

       line(mesure::gram, "Маса зразка:", dat->at(field::mass_of_probe));
       line(mesure::mililiter, "Об'єм фільтрату:", dat->at(field::vol_filtrate));
       line(mesure::mililiter, "Об'єм фотометричної проби:", dat->at(field::vol_photo_probe));
       line(mesure::mililiter, "Об'єм розчинника для розведення:", dat->at(field::vol_photo_alch));
       line(mesure::empty, "Фотометричний показник D665:", dat->at(field::d665));
       line(mesure::empty, "Фотометричний показник D649:", dat->at(field::d649));
       std::print("\n");
       line(mesure::mg_photo_probe, "Концентрація хлорофілу А:", allow.chloro_data_get(chlor_data_type::chloro_a_allowance)->get_chloro(*dat));
       line(mesure::mg_photo_probe, "Концентрація хлорофілу B:", allow.chloro_data_get(chlor_data_type::chloro_b_allowance)->get_chloro(*dat));
       line(mesure::mg_leaf, "Вміст хлорофілу А:", allow.chloro_data_get(chlor_data_type::chloro_a_mg)->get_chloro(*dat));
       line(mesure::mg_leaf, "Вміст хлорофілу B:", allow.chloro_data_get(chlor_data_type::chloro_b_mg)->get_chloro(*dat));
       line(mesure::mg_leaf, "Сума хлорофілів А + B:", allow.chloro_data_get(chlor_data_type::chloro_sum)->get_chloro(*dat));
}

void file_info::see_info(ch_data *dat)
{
       namespace file_system = std::filesystem;
       namespace range_views = std::ranges::views;

       const file_system::path file{"chlor-data.csv"};
       std::ofstream csv(file, std::ios::app);

       auto loc = std::locale{"uk_UA.utf8"};
       chlor_allowance allow;

       auto write = [&](std::string_view label, const auto &value) -> void
       {
              constexpr std::string_view formatter = "\"{}\",\"{:L}\"\n";
              csv << std::format(loc, formatter, label, value);
       };

       write("Маса зразка (г):", dat->at(field::mass_of_probe));
       write("Об'єм фільтрату (мл):", dat->at(field::vol_filtrate));
       write("Об'єм фотометричної проби (мл):", dat->at(field::vol_photo_probe));
       write("Об'єм розчинника для розведення (мл):", dat->at(field::vol_photo_alch));
       write("Фотометричний показник D665:", dat->at(field::d665));
       write("Фотометричний показник D649:", dat->at(field::d649));
       csv << '\n';
       write("Концентрація хлорофілу А (мг/л фотометричного зразка):", allow.chloro_data_get(chlor_data_type::chloro_a_allowance)->get_chloro(*dat));
       write("Концентрація хлорофілу B (мг/л фотометричного зразка):", allow.chloro_data_get(chlor_data_type::chloro_b_allowance)->get_chloro(*dat));
       write("Вміст хлорофілу А (мг/100 г листка):", allow.chloro_data_get(chlor_data_type::chloro_a_mg)->get_chloro(*dat));
       write("Вміст хлорофілу B (мг/100 г листка):", allow.chloro_data_get(chlor_data_type::chloro_b_mg)->get_chloro(*dat));
       write("Сума хлорофілів А + B (мг/100 г листка):", allow.chloro_data_get(chlor_data_type::chloro_sum)->get_chloro(*dat));
       std::print("Дані додані у файл {}\n", file.string());
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
