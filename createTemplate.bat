@echo off

SET USERNAME=__AUSERNAME__
SET SEASONAL=0

SETLOCAL

call SourceFileList.bat

SET PATH=%PATH%;C:\emsdk\upstream\emscripten
SET PATH=%PATH%;C:\emsdk
SET PATH=%PATH%;C:\emsdk\node\12.18.1_64bit\bin
SET PATH=%PATH%;C:\emsdk\python\3.7.4-pywin32_64bit\
SET PATH=%PATH%;C:\emsdk\java\8.152_64bit\bin


call emsdk construct_env %*

if not exist "build\" mkdir build
if not exist "dist\"  mkdir dist

call create.bat
ENDLOCAL