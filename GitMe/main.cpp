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

    for (std::string a : locations)
    {
        bool skip = false;
        try
        {
            cdTo(a);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            skip = true;
        }
        if (!skip)
        {
            try
            {
                gitMe(a);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }

    //*  free memory
    locations.clear();
    // LOG("Free Memory - End Program \n")
    std::cout << "\nFree Memory - End Program \n\n";
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

void gitMe(std::string folder)
{
    std::system("git config --global --add --bool push.autoSetupRemote true");
    gitInit();
    gitCheckout(folder);
    gitPull();
    gitAdd();
    gitCommit();
    gitPush(folder);
}

void gitCheckout(std::string folder)
{
    // std::string url = "git clone " + GameSavesLink() + "";
    std::string url = "git remote add origin " + GameSavesLink();
    LOG(url)
    int res = std::system(url.c_str());
    // if (res != 0)
    // {
    //     LOG("add origin code:")
    //     LOG(res)
    //     // throw std::runtime_error("ERROR add origin");
    // }
    std::string branchName = removeUntilLastSlash(folder);
    // LOG(branchName)
    std::string command = "git checkout -b " + branchName;
    std::system(command.c_str());
}

void gitInit()
{
    std::string command = init;
    int result = std::system(command.c_str());
    if (result != 0)
    {
        throw std::runtime_error("ERROR init");
    }
}
void gitPull()
{
    std::string command = pull;
    int result = std::system(command.c_str());
}
void gitAdd()
{
    std::string command = add;
    int result = std::system(command.c_str());
    // if (result != 0)
    // {
    //     // throw std::runtime_error("ERROR add");
    //     // LOG("ERROR add");
    // }
}
void gitCommit()
{
    std::string command = commit;
    int result = std::system(command.c_str());
    // if (result != 0)
    // {
    //     // throw std::runtime_error("ERROR commit");
    //     LOG("ERROR commit");
    // }
}

void gitPush(std::string folder)
{
    std::string command = push;
    int result = std::system(command.c_str());
    if (result != 0)
    {
        // throw std::runtime_error("ERROR push");
        LOG("ERROR push " << result << ", not found upstream.\n\n");
    }
    if (result == 32768)
    {
        // command = "git remote add origin " + githubLink(folder);
        command = "git remote add origin " + GameSavesLink();
        result = std::system(command.c_str());
        if (result != 0)
        {
            throw std::runtime_error("ERROR adding remote");
            LOG(result)
        }
    }
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
    // Find the position of the last occurrence of '/'
    size_t pos = input.find_last_of('/');

    // Check if '/' was found
    if (pos != std::string::npos)
    {
        // Return the substring after the last '/'
        return input.substr(pos + 1);
    }

    // If '/' is not found, return the original string
    return input;
}