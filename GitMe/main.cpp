#include "main.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        LOG("ERRORE")
        LOG("File Reading")

        if (FileReading())
            LOG("File Completed")

        return 0;
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            // std::cout << "Argument " << (i + 1) << ": " << argv[i]<<std::endl;
            LOG(argv[i]);
        }
    }

    return 1;
}