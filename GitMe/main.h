#pragma once
#include "macro.h"
#include <iostream>
#include <fstream>
#include "commands.h"
#include <set>
#include <string>

static std::set<std::string> locations;

// Debug tool
void printlocals(std::set<std::string> array);

// git init -> git add . -> git commit -m "data" -> git push
void gitMe(std::string folder);

#define pull "git pull"
#define init "git init"
#define add "git add ."
#define commit "git commit -m update"
#define push "git push"

void gitCheckout(std::string folder);
void gitInit();
void gitPull();
void gitAdd();
void gitCommit();
void gitPush(std::string folder);

std::string githubLink(std::string folder);
std::string GameSavesLink();
std::string removeUntilLastSlash(std::string &input);
