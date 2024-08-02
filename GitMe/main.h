#pragma once
#include "macro.h"
#include <iostream>
#include <fstream>
#include "commands.h"
#include <set>
#include <string>

#define File_Extension ".txt"

static std::set<std::string> locations;

void printlocals(std::set<std::string> array);