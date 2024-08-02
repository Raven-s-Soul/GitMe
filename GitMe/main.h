#pragma once
#include "macro.h"
#include <iostream>
#include <fstream>
#include "commands.h"
#include <set>
#include <string>

#define File_Extension ".txt"

static std::set<std::string> locations;

// Debug tool
void printlocals(std::set<std::string> array);

// git init -> git add . -> git commit -m "data" -> git push
void gitMe();

#define init "git init"
#define add "git add ."
#define commit "git commit -m update"
#define push "git push"
