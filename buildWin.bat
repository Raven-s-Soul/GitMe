mkdir out
cd .\out\
cmake ..
cd ..
cmake --build .\out\

:: for VisualStudio use this
::cd out\build\x64-Debug\GitMe\

:: for other
cd out\GitMe\Debug
.\GitMe.exe -h
.\GitMe.exe ..\..\..\Test

@REM cd ..\..\..\Test
@REM .\GitMe.exe