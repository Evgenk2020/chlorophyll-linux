#include "../include/proc.h"
#include <iostream>

int main(int argc, char *argv[])
{
    inp_var _inp_var;

    if (argc == 1)
    {
        std::cout << "error.. data is empty" << std::endl;
    }

    else
    {
        for (int i = 1; i < argc; i++)
        {
            _inp_var.insert(std::pair(i, (std::string)argv[i]));
        }
    }

    processing *_processing = nullptr;
    decree _decree(_inp_var);

    _processing = &_decree;
    _processing->going();

    return 0;
}