@echo off

set "a=%CD%"

mkdir day_%1
cd day_%1

type "%a%\runTemplate.txt" > run.bat
