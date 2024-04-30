@echo off
setlocal

call build/win32/msvc.bat %*
call build/win32/llvm.bat %*
call build/win32/mingw.bat %*

exit /b 0
