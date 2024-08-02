#include "main.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        LOG("No Console Input")
        if (lfFile(&locations))
            return 1;
    }
    else
    {
        LOG("Console Input found")
        for (int i = 1; i < argc; i++)
        {
            // std::cout << "Argument " << (i + 1) << ": " << argv[i]<<std::endl;
            // LOG(argv[i]);
            locations.insert(argv[i]);
        }
    }

    //? Debug
    // printlocals(locations);
    //  TODO

    //*  free memory
    locations.clear();
    LOG("Free Memory - End Program \n")
    return 0;
}

//! Actualy if not using the input locations is gonna lose scope...
void printlocals(std::set<std::string> array)
{

    for (auto a : array)
    {
        std::cout << a << std::endl;
    }
}