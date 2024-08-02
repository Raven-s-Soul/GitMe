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

    //? using pwd?
    //? Debug
    // printlocals(locations);

    for (std::string a : locations)
    {
        cdTo(a);
        gitMe();
    }

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

void gitMe()
{
#ifdef __APPLE__
    std::string command = "git -v";
    std::system(command.c_str());
#elif _WIN32
    ShellExecuteA(NULL, "git -v", NULL, NULL, NULL, SW_SHOWNORMAL);
#else
    std::string command = "git -v";
    std::system(command.c_str());
#endif

    FILE *pipe = popen((command).c_str(), "r");
    if (pipe == NULL)
    {
        perror("popen failed");
    }

    // Read the output of the command line by line
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        // TODO
    }
    //  Close the pipe
    pclose(pipe);
}