add_executable(GitMe main.h main.cpp commands.h commands.cpp macro.h)

if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GitMe PROPERTY CXX_STANDARD 20)
endif()
