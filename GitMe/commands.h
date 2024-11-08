#pragma once
#include "macro.h"
// #include "main.h"

#ifdef _WIN32
#include <windows.h>
#include <direct.h> // For _chdir on Windows
#else
#include <cstdlib>
#include <unistd.h>
#endif

// looking for File to read
bool lfFile(std::set<std::string> *set);

// read inside the file
void fileRead(std::string filename, std::set<std::string> *set);

// command cd to a directory
void cdTo(std::string directory);