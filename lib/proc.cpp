#include "../include/proc.h"
#include <charconv>

void processing::going()
{
    if (_inp_var.size() == 1)
    {
        helping();
        return;
    }

    if (_inp_var.size() > 1)
    {
        converting();
        counting();
    }
}

decree::decree(inp_var _inp) { _inp_var = std::move(_inp); }

void decree::helping()
{
    const auto &key = _inp_var.at(1);

    if (key == keys::k_help_one || key == keys::k_help_two)
    {
        print_info{new help_info}._print();
    }

    else if (key == keys::k_info)
    {
        print_info{new inf_info}._print();
    }

    else
    {
        std::cout << "error... use -h or --help for details" << std::endl;
    }
}

void decree::converting()
{
    if (_inp_var.size() < 7)
    {
        std::cout << "error.. the number of data can not be less than seven" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // ----------------------------------------------------------------------------------

    if (_inp_var.size() == 7)
    {
        int counter{2};
        for (auto &a : datas.values)
        {
            auto it = _inp_var.find(counter);

            if (it == _inp_var.end())
            {
                std::cerr << "Missing input value\n";
                std::exit(EXIT_FAILURE);
            }

            const std::string &str = it->second;
            float val{};
            auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), val);

            if (ec != std::errc())
            {
                std::cerr << "Invalid numeric value\n";
                std::exit(EXIT_FAILURE);
            }

            a = val;
            counter++;
        }

        if (datas.at(field::vol_photo_probe) == 0 || datas.at(field::mass_of_probe) == 0)
        {
            std::cerr << "division by zero...\n";
            std::exit(EXIT_FAILURE);
        }
    }

    else
    {
        std::cout << "error.. the numbers are wrong " << std::endl;
    }
}

void decree::counting()
{
    if (_inp_var.at(1) == _keys.k_data)
    {

        print_info inf(new screen_info);
        inf._print(datas);
    }

    else if (_inp_var.at(1) == _keys.k_file)
    {
        print_info inf(new file_info);
        inf._print(datas);
    }

    else
    {
        std::cout << "incorrect key.. use [-d | -df] keys for results" << std::endl;
    }
}