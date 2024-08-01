#pragma once
#include <iostream>
#include <fstream>

// 	Debug Macro
//	1 - Active , 0 - Deactive
#define DEBUG_LOG 1

#if DEBUG_LOG
#define LOG(message) std::cout << message << std::endl;
#else
#define LOG(message)
#endif

bool FileReading()
{
    // std::string filename = "ExampleNames.txt";
    std::ifstream file("ExampleNames.txt");

    // FILE *F = fopen(filename.c_str(), "r"); // Lettura Binario

    // if (F == NULL)
    if (!file.is_open())
        return false;

    std::string text;
    // while (fscanf(F, "%s", text) != EOF)
    while (file >> text)
    {
        LOG(text)
    }

    // fclose(F);
    file.close();
    return true;
}

void commads()
{
    // popen();
}