#include "../include/proc.h"
#include "../include/probe_data.h"
#include <regex>

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
        exit(1);
    }

    // ----------------------------------------------------------------------------------

    if (_inp_var.size() == 7)
    {
        try
        {
            datas.at(field::mass_of_probe) = std::stof(_inp_var.find(probe_data::_prob_mass)->second);
            datas.at(field::vol_filtrate) = std::stof(_inp_var.find(probe_data::_filtrate_vol)->second);
            datas.at(field::vol_photo_probe) = std::stof(_inp_var.find(probe_data::_photo_probe)->second);
            datas.at(field::vol_photo_alch) = std::stof(_inp_var.find(probe_data::_photo_alch)->second);
            datas.at(field::d665) = std::stof(_inp_var.find(probe_data::_d665)->second);
            datas.at(field::d649) = std::stof(_inp_var.find(probe_data::_d649)->second);
        }

        catch (const std::exception &e)
        {
            std::cout << "error.. use correct data values" << std::endl;
            exit(1);
        }

        try
        {
            if (datas.at(field::vol_photo_probe) == 0 || datas.at(field::mass_of_probe) == 0)
            {
                throw std::runtime_error("division by zero...");
            }
        }

        catch (const std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
            exit(1);
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