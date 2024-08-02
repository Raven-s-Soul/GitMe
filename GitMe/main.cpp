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
    gitInit();
    gitCheckout(folder);
    gitPull();
    gitAdd();
    gitCommit();
    gitPush(folder);
}

void gitCheckout(std::string folder)
{
    std::system("git config --global --add --bool push.autoSetupRemote true");
    // std::string url = "git clone " + GameSavesLink() + "";
    std::string url = "git remote add origin " + GameSavesLink();
    int res = std::system(url.c_str());
    if (res != 0)
    {
        LOG(res)
        // throw std::runtime_error("ERROR add origin");
    }
    std::string command = "git checkout -b " + foldName(folder);
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
    if (result != 0)
    {
        // throw std::runtime_error("ERROR add");
        LOG("ERROR add");
    }
}
void gitCommit()
{
    std::string command = commit;
    int result = std::system(command.c_str());
    if (result != 0)
    {
        // throw std::runtime_error("ERROR commit");
        LOG("ERROR commit");
    }
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

// https://github.com/Raven-s-Soul/GitMe.git
std::string githubLink(std::string folder)
{
    std::string foldeName = foldName(folder);
    // Retrieve the Git username
    std::string username = exec("git config user.name");
    // Trim newline characters
    if (!username.empty() && username.back() == '\n')
    {
        username.pop_back();
    }
    std::replace(username.begin(), username.end(), ' ', '-');
    // LOG(username)
    // LOG(folder)
    return "https://github.com/" + username + "/" + folder + ".git";
}

// Make a url like this https://github.com/Raven-s-Soul/GameSaves.git
std::string GameSavesLink()
{
    std::string str = "GameSaves";
    return githubLink(str);
    // return "https://github.com/Raven-s-Soul/GameSaves.git";
}

std::string foldName(std::string folder)
{
    size_t pos = folder.find('/');
    if (pos != std::string::npos)
    {
        folder.erase(0, pos + 1);
    }
    return folder;
}