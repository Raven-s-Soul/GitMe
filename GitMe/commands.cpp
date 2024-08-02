#include "commands.h"

bool lfFile(std::set<std::string> *set)
{
    LOG("Looking for a file to read");

#ifdef __APPLE__
    std::string command = "ls";
    std::system(command.c_str());
#elif _WIN32
    ShellExecuteA(NULL, "ls", NULL, NULL, NULL, SW_SHOWNORMAL);
#else
    std::string command = "ls ";
    std::system(command.c_str());
#endif

    FILE *pipe = popen(command.c_str(), "r");
    if (pipe == NULL)
    {
        perror("popen failed");
        return 1;
    }

    // Read the output of the command line by line
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        try
        {
            std::string txt = buffer;
            if (txt.find(File_Extension) != std::string::npos)
            {
                LOG("FOUND - " << txt);
                //! Remove '\n'
                if (txt.find('\n') != std::string::npos)
                    txt.pop_back();
                fileRead(txt, set);
            }
        }
        catch (const std::exception &e)
        {
            LOG("Error reading " << buffer);
            std::cerr << e.what() << '\n';
        }
    }
    LOG("Done files");
    //  Close the pipe
    pclose(pipe);
    return 0;
}

void fileRead(std::string filename, std::set<std::string> *set)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Failed to open the file.");

    std::string text;
    while (file >> text)
    {
        set->insert(text);
    }
    file.close();
}

void cdTo(std::string directory)
{
    LOG("\n"
        << directory << " <----------")
#ifdef _WIN32
    if (_chdir(directory.c_out()) != 0)
        std::cerr << "Failed to change directory" << std::endl;
#else
    if (chdir(directory.c_str()) != 0)
    {
        throw std::runtime_error("Failed to change directory.");
    }
#endif
}

/*
    FILE *pipe = popen("ls", "r");
    if (pipe == NULL)
    {
        perror("popen failed");
    }

    // Read the output of the command line by line
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        // TODO fix AssertError ----------
        // TODO sh: line 0: cd: AssertError: No such file or directory
        // LOG(buffer)
        //  LOG("Element Found - " << buffer)
    }
    //  Close the pipe
    pclose(pipe);
    */