#include "commands.h"

bool lfFile(std::set<std::string> *set)
{
    LOG("Looking for a file to read");

#ifdef __APPLE__
    std::string command = "ls";
    std::system(command.c_str());
#elif _WIN32
    std::string command = "dir";
    ShellExecuteA(NULL, command.c_str(), NULL, NULL, NULL, SW_SHOWNORMAL);
#else
    std::string command = "ls ";
    std::system(command.c_str());
#endif

#ifdef _WIN32
    FILE *pipe = _popen(command.c_str(), "r");
    if (pipe == NULL)
    {
        perror("popen failed");
        return 1;
    }
#else
    FILE *pipe = popen(command.c_str(), "r");
    if (pipe == NULL)
    {
        perror("popen failed");
        return 1;
    }
#endif

    // Read the output of the command line by line
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        try
        {
            std::string txt = buffer;
            if (txt.find(File_Extension) != std::string::npos)
            {
                // LOG("FOUND - " << txt);
                std::cout << "Reading - " << txt;
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
#ifdef _WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif
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
    // LOG("\n"<< directory << " <----------")
    std::cout << "\n"
              << directory << std::endl;
#ifdef _WIN32
    if (_chdir(directory.c_str()) != 0)
        std::cerr << "Failed to change directory" << std::endl;
#else
    if (chdir(directory.c_str()) != 0)
    {
        throw std::runtime_error("Failed to change directory.");
    }
#endif

    //* Write .gitignore
    // std::ofstream file(".gitignore");
    // if (!file.is_open())
    //     throw std::runtime_error("Failed to write the file.");

    // std::string text = "GitMe";
    // file << text;
    // file.close();
}

//* Function to execute a command and get its output
std::string exec(const std::string &cmd)
{
    char buffer[128];
    std::string result;
#ifdef _WIN32
    FILE *pipe = _popen(cmd.c_str(), "r");
#else
    FILE *pipe = popen(cmd.c_str(), "r");
#endif

    if (!pipe)
        throw std::runtime_error("popen() failed!");
    try
    {
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        {
            result += buffer;
        }
    }
    catch (...)
    {
#ifdef _WIN32
        _pclose(pipe);
#else
        pclose(pipe);
#endif
        throw;
    }
#ifdef _WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif

    return result;
}