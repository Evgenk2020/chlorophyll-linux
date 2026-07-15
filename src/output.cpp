#include "../include/output.h"

#include <iostream>
#include <fstream>
#include <locale>
#include <print>
#include <filesystem>
#include <format>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

void help_info::see_info()
{
       std::println(
           "*** Визначення концентрації хлорофілів ***\n"
           "\n"
           "Ви можете запускати програму в двох режимах:\n"
           "\n"
           "1. ІНТЕРАКТИВНИЙ РЕЖИМ (Рекомендовано для ручного введення):\n"
           "   Просто запустіть програму без параметрів:\n"
           "   ./chloro\n"
           "   Програма покроково запитає всі необхідні дані українською мовою.\n"
           "\n"
           "2. РЕЖИМ ПРАПОРЦІВ (Рекомендовано для скриптів та автоматизації):\n"
           "   Вкажіть параметри за допомогою іменованих ключів (порядок введення довільний):\n"
           "   -w  | --weight [наважка (г)]\n"
           "   -f  | --filt   [фільтрат (мл)]\n"
           "   -p  | --prob   [фотометрична проба (мл)]\n"
           "   -s  | --solv   [фотометричний розчинник (мл)]\n"
           "   --d665         [показник фотометра 665]\n"
           "   --d649         [показник фотометра 649]\n"
           "\n"
           "   Додайте прапорець '-df' або '--file' у будь-яке місце, щоб зберегти результат у файл:\n"
           "   Приклад: ./chloro -w 1.3 -f 25 -p 3 -s 5 --d665 1.25 --d649 0.45 -df\n"
           "\n"
           "ДОВІДКА ТА ІНФОРМАЦІЯ:\n"
           "   -h | --help  Показати це вікно довідки\n"
           "   -i           Теоретичні відомості та формули розрахунку\n"
           "   -j | --json  Вивести результат у форматі JSON для автоматизації");
}

void inf_info::see_info()
{
       std::println(
           "Для розрахунку концентрації хлорофілів A і B в розчині визначають його оптичну густину за довжини хвилі,\n"
           "що відповідє максимумам спектра поглинання досліджуваних пігментів. Для хлорофілу A в 96% етанолі максимум\n"
           "поглинання λ = 665 нм, для хлорофілу B λ = 649 нм.\n"
           "\n"
           "Формули для розчинів хлорофілу в 96% етанолі:\n"
           "концентрація хлорофіла A (мг/л) = 13.7 * D665 - 5.76 * D649\n"
           "концентрація хлорофіла B (мг/л) = 25.8 * D649 - 7.6 * D665");
}

//--------------------------------------------------

void screen_info::see_info(ch_data *dat)
{
       chlor_allowance allow;

       enum class measure
       {
              gram,
              mililiter,
              empty,
              mg_photo_probe,
              mg_leaf
       };

       auto line = [&](measure type, const std::string_view &label, const auto &value) -> void
       {
              constexpr std::string_view gram = "{} {} г\n";
              constexpr std::string_view mililiter = "{} {} мл\n";
              constexpr std::string_view empty = "{} {}\n";
              constexpr std::string_view mg_photo_probe = "{} {} мг/л фотометричного зразка\n";
              constexpr std::string_view mg_leaf = "{} {} мг/100 г листка\n";

              switch (type)
              {
              case measure::gram:
                     std::print(gram, label, value);
                     break;

              case measure::mililiter:
                     std::print(mililiter, label, value);
                     break;

              case measure::empty:
                     std::print(empty, label, value);
                     break;

              case measure::mg_photo_probe:
                     std::print(mg_photo_probe, label, value);
                     break;

              case measure::mg_leaf:
                     std::print(mg_leaf, label, value);
                     break;
              }
       };

       line(measure::gram, "Маса зразка:", dat->at(field::mass_of_probe));
       line(measure::mililiter, "Об'єм фільтрату:", dat->at(field::vol_filtrate));
       line(measure::mililiter, "Об'єм фотометричної проби:", dat->at(field::vol_photo_probe));
       line(measure::mililiter, "Об'єм розчинника для розведення:", dat->at(field::vol_photo_alch));
       line(measure::empty, "Фотометричний показник D665:", dat->at(field::d665));
       line(measure::empty, "Фотометричний показник D649:", dat->at(field::d649));
       std::print("\n");
       line(measure::mg_photo_probe, "Концентрація хлорофілу А:", allow.chloro_data_get(chlor_data_type::chloro_a_allowance)->get_chloro(*dat));
       line(measure::mg_photo_probe, "Концентрація хлорофілу B:", allow.chloro_data_get(chlor_data_type::chloro_b_allowance)->get_chloro(*dat));
       line(measure::mg_leaf, "Вміст хлорофілу А:", allow.chloro_data_get(chlor_data_type::chloro_a_mg)->get_chloro(*dat));
       line(measure::mg_leaf, "Вміст хлорофілу B:", allow.chloro_data_get(chlor_data_type::chloro_b_mg)->get_chloro(*dat));
       line(measure::mg_leaf, "Сума хлорофілів А + B:", allow.chloro_data_get(chlor_data_type::chloro_sum)->get_chloro(*dat));
}

void file_info::see_info(ch_data *dat)
{
       namespace file_system = std::filesystem;

       const file_system::path file{"chlor-data.csv"};
       bool need_bom = !file_system::exists(file) || file_system::file_size(file) == 0;
       std::ofstream csv(file, std::ios::app | std::ios::binary);

       if (need_bom)
       {
              const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
              csv.write(reinterpret_cast<const char *>(bom), 3);
       }

       auto loc = std::locale{"uk_UA.utf8"};
       chlor_allowance allow;

       auto write = [&](std::string_view label, const auto &value) -> void
       {
              constexpr std::string_view formatter = "\"{}\";\"{:L}\"\n";
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
       csv << '\n';

       std::print("Дані додані у файл {}\n", file.string());
}

void json_info::see_info(ch_data *dat)
{
       chlor_allowance allow;

       // Create a RapidJSON DOM document
       rapidjson::Document doc;
       doc.SetObject();
       auto &allocator = doc.GetAllocator();

       // Write the input parameters
       doc.AddMember("mass_of_probe", dat->at(field::mass_of_probe), allocator);
       doc.AddMember("vol_filtrate", dat->at(field::vol_filtrate), allocator);
       doc.AddMember("vol_photo_probe", dat->at(field::vol_photo_probe), allocator);
       doc.AddMember("vol_photo_alch", dat->at(field::vol_photo_alch), allocator);
       doc.AddMember("d665", dat->at(field::d665), allocator);
       doc.AddMember("d649", dat->at(field::d649), allocator);

       // Perform calculations and record the results
       doc.AddMember("conc_chloro_a", allow.chloro_data_get(chlor_data_type::chloro_a_allowance)->get_chloro(*dat), allocator);
       doc.AddMember("conc_chloro_b", allow.chloro_data_get(chlor_data_type::chloro_b_allowance)->get_chloro(*dat), allocator);
       doc.AddMember("content_chloro_a", allow.chloro_data_get(chlor_data_type::chloro_a_mg)->get_chloro(*dat), allocator);
       doc.AddMember("content_chloro_b", allow.chloro_data_get(chlor_data_type::chloro_b_mg)->get_chloro(*dat), allocator);
       doc.AddMember("total_chlorophylls", allow.chloro_data_get(chlor_data_type::chloro_sum)->get_chloro(*dat), allocator);

       // Style and collect into a buffer string
       rapidjson::StringBuffer buffer;
       rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
       doc.Accept(writer);

       // Output ONLY the pure JSON string to stdout
       std::println("{}", buffer.GetString());
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