#ifndef OUTPUT_H
#define OUTPUT_H

#include "../include/chloro.h"

class general_info
{
public:
    virtual void see_info() = 0;
    virtual ~general_info() = default;
};

class help_info : public general_info
{
public:
    void see_info() override;
};

class inf_info : public general_info
{
public:
    void see_info() override;
};

//--------------------------------------------------

class data_info
{
public:
    virtual void see_info(ch_data *dat) = 0;
    virtual ~data_info() = default;
};

class screen_info : public data_info
{
public:
    void see_info(ch_data *dat) override;
};

class file_info : public data_info
{
public:
    void see_info(ch_data *dat) override; 
};

//--------------------------------------------------

class print_info
{
private:
    general_info *g_info = nullptr;
    data_info *d_info = nullptr;

public:
    print_info(general_info *temp);
    print_info(data_info *temp);
    void _print();
    void _print(ch_data temp);
    ~print_info();
};

#endif // OUTPUT_H