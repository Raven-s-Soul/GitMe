cmake_minimum_required(VERSION 3.8)

# Needed for tests
set(CMAKE_CXX_COMPILER g++)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# set(CMAKE_CXX_EXTENSIONS NO)

# set(CMAKE_CXX_COMPILER cl) # Using windows

# Abilita Ricaricamento rapido per i compilatori MSVC, se supportato.
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("GitMe")

# Includere i sottoprogetti.
add_subdirectory("GitMe")
