#pragma once
#include "main.h"
#include "macro.h"
#include <set>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

// looking for File to read
bool lfFile(std::set<std::string> *set);

// read inside the file
void fileRead(std::string filename, std::set<std::string> *set);