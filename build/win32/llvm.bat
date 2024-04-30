@echo off
setlocal

if "%1" == "clean" (
  del /q llvm_main.exe 2> nul
  del /q llvm_main.exp 2> nul
  del /q llvm_main.lib 2> nul
  del /q llvm_main.pdb 2> nul

  del /q llvm_main_release.exe 2> nul
  exit /b 0
)

REM Flags Common Between Debug And Release Mode
set turned_off_warnings=-Wno-gnu-zero-variadic-macro-arguments
set clang_common=-I./src -std=c11 -fuse-ld=lld

if "%1" == "release" (
  echo Compiling LLVM [Release] Build..
  clang.exe src/build.c %clang_common% -O3 -flto -o llvm_main_release.exe
) else (
  echo Compiling LLVM [Debug] Build..
  clang.exe src/build.c %clang_common% -g3 -Wall -Wextra -Werror -pedantic -Wfatal-errors %turned_off_warnings% -fsanitize=address,undefined -DDEBUG -o llvm_main.exe
)

echo.
if errorlevel 1 (
  echo LLVM Build Failed
  exit /b 1
)

echo LLVM Build Finished Successfully
exit /b 0
