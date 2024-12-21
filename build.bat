@echo off

setlocal 

cd  %CD%

if "%Platform%" neq "x64" (
    echo ERROR: Platform is not "x64" - please run this from the MSVC x64 native tools command prompt.
    goto end
)


if "%1"=="" goto invalid_arguments
if not exist %1 goto no_such_file

set "size= %~z1"

if not exist build mkdir build
cd build

cl ../main.c /Od /Zo /Z7 /nologo /link /incremental:no /opt:ref /subsystem:console && main ../%1 %size%

goto end

:invalid_arguments
echo Invalid arguments^. Usage: build input_file
goto end

:no_such_file
echo No such file: %1

:end
endlocal
