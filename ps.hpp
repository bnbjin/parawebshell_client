#pragma once


#include <string>
#include <vector>

#include <sys/types.h>


namespace pws {

typedef pid_t ps_id_t;

struct process_info
{
    ps_id_t         id;
    std::string     executive_path;
    std::string     command_line_args;
    std::vector<std::string> dynamic_link_libraries;
};


void list_all_process(std::vector<process_info> &process_info_list);

}
