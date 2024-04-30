@echo off
setlocal

if "%1" == "clean" (
  del /q hext_debug.exe 2> nul
  del /q hext_debug.exp 2> nul
  del /q hext_debug.lib 2> nul
  del /q hext_debug.pdb 2> nul

  del /q hext.exe 2> nul
  exit /b 0
)

REM Flags Common Between Debug And Release Mode
set turned_off_warnings=-Wno-gnu-zero-variadic-macro-arguments
set clang_common=-I./src -std=c11 -fuse-ld=lld

if "%1" == "release" (
  echo Compiling LLVM [Release] Build..
  clang.exe src/build.c %clang_common% -O3 -flto -o hext.exe
) else (
  echo Compiling LLVM [Debug] Build..
  clang.exe src/build.c %clang_common% -g3 -Wall -Wextra -Werror -pedantic -Wfatal-errors %turned_off_warnings% -fsanitize=address,undefined -DDEBUG -o hext_debug.exe
)

echo.
if errorlevel 1 (
  echo LLVM Build Failed
  exit /b 1
)

echo LLVM Build Finished Successfully
exit /b 0
