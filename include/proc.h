#ifndef PROC_H
#define PROC_H

#include "../include/output.h"
#include <iostream>
#include <map>

typedef std::map<int, std::string> inp_var;

struct keys
{
    static constexpr std::string_view k_help_one{"-h"};
    static constexpr std::string_view k_help_two{"--help"};
    static constexpr std::string_view k_info{"-i"};
    static constexpr std::string_view k_data{"-d"};
    static constexpr std::string_view k_file{"-df"};
};

class processing
{
protected:
    keys _keys;
    inp_var _inp_var;
    virtual void helping() = 0;
    virtual void converting() = 0;
    virtual void counting() = 0;

public:
    virtual ~processing() = default;
    void going();
};

class decree : public processing
{
private:
    ch_data datas;

public:
    ~decree() override = default;
    decree(inp_var _inp);
    void helping() override;
    void converting() override;
    void counting() override;
};

#endif // PROC_H