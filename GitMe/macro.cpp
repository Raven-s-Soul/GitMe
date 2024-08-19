#include "macro.h"

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

std::string githubLink(std::string RepoName)
{
    // std::string foldeName = removeUntilLastSlash(RepoName);
    //  Retrieve the Git username
    std::string username = exec("git config user.name");
    // Trim newline characters
    if (!username.empty() && username.back() == '\n')
    {
        username.pop_back();
    }
    std::replace(username.begin(), username.end(), ' ', '-');
    // LOG(username)
    // LOG(folder)
    return "https://github.com/" + username + "/" + RepoName + ".git";
}

// Make a url like this https://github.com/Raven-s-Soul/GameSaves.git
std::string GameSavesLink()
{
    // std::string str = "GameSaves";
    // std::string str = "GameSavesDev";
    return githubLink(REPOSITORY_NAME);
    // return "https://github.com/Raven-s-Soul/GameSaves.git";
}

std::string removeUntilLastSlash(std::string &input)
{

#ifdef _WIN32
    size_t pos = input.find_last_of('\\');

    // Check if '\' was found
    if (pos != std::string::npos)
    {
        // Return the substring after the last '\'
        return input.substr(pos + 1);
    }

#else
    // Find the position of the last occurrence of '/'
    size_t pos = input.find_last_of('/');

    // Check if '/' was found
    if (pos != std::string::npos)
    {
        // Return the substring after the last '/'
        return input.substr(pos + 1);
    }

#endif

    // If '/' is not found, return the original string
    return input;
}

bool isRepo(std::string path)
{
#ifdef _WIN32
    std::string risposta = exec("dir /a"); // dir -h // dir .git
#else
    std::string risposta = exec("ls -a");
#endif
    if (risposta.find(".git") != std::string::npos)
    {
        return true;
    }
    return false;
}

void printlocals(std::set<std::string> array)
{
    for (auto a : array)
    {
        std::cout << a << std::endl;
    }
}