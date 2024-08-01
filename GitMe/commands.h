#pragma once
#include "main.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

/*
void ex(const char *url)
{
#ifdef __APPLE__
    std::string command = "open ";
    command += url;
    std::system(command.c_str());
#elif _WIN32
    ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
#else
    std::string command = "xdg-open ";
    command += url;
    std::system(command.c_str());
#endif
}
*/