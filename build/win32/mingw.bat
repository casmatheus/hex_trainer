@echo off
setlocal

if "%1" == "clean" (
  del /q hext_debug.exe 2> nul
  del /q hext.exe 2> nul
  exit /b 0
)

REM Flags Common Between Debug And Release Mode
set gcc_common=-I./src -std=gnu11
if "%1" == "release" (
  echo Compiling Mingw [Release] Build..
  gcc.exe src/build.c %gcc_common% -O3 -o hext.exe
) else (
  echo Compiling Mingw [Debug] Build..
  gcc.exe src/build.c %gcc_common% -Wall -Wextra -Werror -pedantic -Wfatal-errors -g3 -fsanitize-trap=all -DDEBUG -o hext_debug.exe
)

echo.
if errorlevel 1 (
  echo Mingw Build Failed
  exit /b 1
)

echo Mingw Build Finished Successfully
exit /b 0
