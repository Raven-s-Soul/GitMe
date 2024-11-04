#include "main.h"

int main(int argc, char *argv[])
{
    std::set<std::string> locations;

    if (argc == 1)
    {
        LOG("No Console Input")
        if (lfFile(&locations))
            return 1;
    }
    else
    {
        int i = 1;
        LOG("Console Input found")
        std::string arg = argv[i];
        if (arg.find(help) != std::string::npos)
        {
            std::cout << "Automaticly git things on your " << REPOSITORY_NAME << " repository on GitHub \n@Args <- are folder paths \nGitMe @Arg1 @Arg2... \nGitMe // Look for .GitMe file \nMore on https://github.com/Raven-s-Soul/GitMe" << std::endl;
            return 2;
            // i++;
        }
        // Other tools

        for (; i < argc; i++)
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
            // Remove last "\" or "/"
            removeLastSlash(a);
            replaceSpaces(a);
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

void gitMe(std::string folder)
{
    std::system("git config --global --add --bool push.autoSetupRemote true");
    if (!isRepo(folder.c_str()))
    {
        std::cout << "Not a repository" << std::endl;
        gitClone(folder);
        // return;
        gitInit();
        gitCheckout(folder);
    }
    gitPull();
    gitAdd();
    gitCommit();
    gitPush(folder);
}

void gitCheckout(std::string folder)
{
    // std::string url = "git clone " + GameSavesLink() + "";
    std::string url = "git remote add origin " + GameSavesLink();
    // LOG(url)
    std::cout << url << std::endl;
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
    std::cout << command << std::endl;
    std::system(command.c_str());
}
bool gitClone(std::string folder)
{
    // git ls-remote --heads https://github.com/Raven-s-Soul/GameSaves.git Test
    int result;
    std::string command = "git ls-remote --heads " + GameSavesLink() + " " + removeUntilLastSlash(folder);
    std::cout << command << std::endl;

    std::string risposta = exec(command);
    // result = std::system(command.c_str());
    //  LOG(result)
    // if (result == 0)
    std::string toFind = "refs/heads/" + removeUntilLastSlash(folder);
    if (risposta.find(toFind.c_str()) != std::string::npos)
    {
        std::cout << "Found online branch" << std::endl;
        //! Not forced
        cdTo("..");
        std::cout << "For download last version use (Y/y) or (S/s) for delete the folder and files." << std::endl;
#ifdef _WIN32
        command = "rmdir /s " + removeUntilLastSlash(folder);
#else
        command = "rm -r -i " + removeUntilLastSlash(folder); //* Fix
#endif
        result = std::system(command.c_str());
        // LOG(result)

        // Delete
        std::cout << "Successivo al tentativo di cancellazione" << std::endl;

        command = "git clone --branch " + removeUntilLastSlash(folder) + " --single-branch " + GameSavesLink() + " " + removeUntilLastSlash(folder);
        // command = "git clone --branch " + removeUntilLastSlash(folder) + " --single-branch " + GameSavesLink() + " .";

        std::cout << command << std::endl;

        result = std::system(command.c_str());
        // LOG(result)
        cdTo(removeUntilLastSlash(folder));
        //! End not forced

        //* Force Deletetion
        if (CloneForceDelete && result != 0) // TODO
        {
            cdTo("..");
#ifdef _WIN32
            command = "rmdir /s /q " + removeUntilLastSlash(folder);
#else
            command = "rm -rf " + removeUntilLastSlash(folder);
#endif
            std::system(command.c_str());
            command = "git clone --branch " + removeUntilLastSlash(folder) + " --single-branch " + GameSavesLink() + " " + removeUntilLastSlash(folder);
            std::cout << command << std::endl;
            result = std::system(command.c_str());
            // LOG(result)
            cdTo(removeUntilLastSlash(folder));
        }

        return true;
    }
    else
    {
        LOG("Branch non trovato online")
        return false;
    }
}
void gitInit()
{
    std::string command = init;
    std::cout << command << std::endl;
    int result = std::system(command.c_str());
    if (result != 0)
    {
        throw std::runtime_error("ERROR init");
    }
}
void gitPull()
{
    std::string command = pull;
    std::cout << command << std::endl;
    int result = std::system(command.c_str());
}
void gitAdd()
{
    std::string command = add;
    std::cout << command << std::endl;
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
    std::cout << command << std::endl;
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
    std::cout << command << std::endl;
    int result = std::system(command.c_str());
    if (result != 0)
    {
        // throw std::runtime_error("ERROR push");
        LOG("ERROR push " << result << ", not found upstream.\n\n");
    }
    if (result == 256)
    {
        LOG("ERROR push - Autofix\n\n");
        // git branch --set-upstream-to=origin/main Test
        command = "git branch --set-upstream-to=origin/" + removeUntilLastSlash(folder) + " " + removeUntilLastSlash(folder);
        result = std::system(command.c_str());
        LOG(result)
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

void removeLastSlash(std::string &str)
{
    if (!str.empty() && (str.back() == '/' || str.back() == '\\'))
    {
        str.pop_back();
    }
}

void replaceSpaces(std::string &str)
{
    if (!str.empty())
    {
        std::replace(str.begin(), str.end(), ' ', '-');
    }
}
