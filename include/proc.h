#ifndef PROC_H
#define PROC_H

#include "output.h"
#include <vector>
#include <string_view>
#include <expected>

class processing
{
protected:
    std::vector<std::string_view> _args;
    bool _save_to_file = false;
    bool _json_output = false;

    virtual void helping() = 0;
    virtual std::expected<ch_data, std::string> parsing() = 0;
    virtual void counting(const ch_data &datas) = 0;

public:
    virtual ~processing() = default;
    void going();
};

class decree : public processing
{
private:
    std::expected<ch_data, std::string> parse_flags();
    ch_data run_interactive_wizard();

public:
    ~decree() override = default;
    decree(int argc, char **argv);

    void helping() override;
    std::expected<ch_data, std::string> parsing() override;
    void counting(const ch_data &datas) override;
};

#endif // PROC_H