#pragma once
// 	Debug Macro
//	1 - Active , 0 - Deactive
#define DEBUG_LOG 0

#if DEBUG_LOG
#define LOG(message) std::cout << message << std::endl;
#else
#define LOG(message) ;
#endif

// Feel free to edit if you plan to make another
// version for other cases then games save files
#define REPOSITORY_NAME "GameSaves"
#define File_Extension ".GitMe"