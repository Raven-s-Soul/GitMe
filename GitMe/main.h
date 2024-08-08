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

#if __has_include(<filesystem>)
#include <filesystem>
#define ISAREPOSITORY 1
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
#define ISAREPOSITORY 1
#else
#error "Neither <filesystem> nor <experimental/filesystem> is available."
#define ISAREPOSITORY 0
#endif
// Tecnicaly using ls -a i can check if there is .git file in the folder
// Check if in the folder there is a .git file
bool isRepo(std::string path);
// git clone --branch feature-branch --single-branch https://github.com/user/repository.git .
bool gitClone(std::string folder);
void gitCheckout(std::string folder);
void gitInit();
void gitPull();
void gitAdd();
void gitCommit();
void gitPush(std::string folder);

std::string githubLink(std::string folder);
std::string GameSavesLink();
std::string removeUntilLastSlash(std::string &input);
