@echo off
setlocal

if "%1" == "clean" (
  del /q hext_debug.exe 2> nul
  del /q hext_debug.pdb 2> nul

  del /q build.obj 2> nul

  del /q *.nativecodeanalysis.xml 2> nul

  del /q hext.exe 2> nul
  exit /b 0
)

REM Flags Common Between Debug And Release Mode
set cl_common=/nologo /I\src\ /TC /MP /FC /WL /std:c11 /diagnostics:caret
set link_common=/incremental:no

if "%1" == "release" (
  echo Compiling MSVC [Release] Build..
  cl.exe %cl_common% /O2 /GS- /Fe"hext.exe" src/build.c /link %link_common% /opt:ref /opt:icf 
) else (
  echo Compiling MSVC [Debug] Build..
  cl.exe %cl_common% /Z7 /RTCcsu /Qspectre /Wall /WX /W4 /DDEBUG /external:W0 /sdl /analyze /Fe"hext_debug.exe" src/build.c /link %link_common% /WX
)

echo.
if errorlevel 1 (
  echo MSVC Build Failed
  exit /b 1
)

echo MSVC Build Finished Successfully
exit /b 0
