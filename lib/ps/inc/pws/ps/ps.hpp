#pragma once

#include <sys/types.h>


struct psinfo
{
    pid_t   pid;
};


void get_ps_info(pid_t pid, psinfo &pi);
