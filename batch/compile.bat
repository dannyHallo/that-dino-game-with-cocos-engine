@echo off

set PROJECT_NAME=HelloWorld
set BUILD_TYPE=Debug

echo:
@echo *************************** cmake ****************************
echo:

mkdir build
cd build
cmake .. -D PROJ_NAME=%PROJECT_NAME% -A win32
cd ..

echo:
@echo ************************** msbuild ***************************
echo:

MSBuild build/%PROJECT_NAME%.sln -p:Configuration=%BUILD_TYPE%

echo:
@echo **************************** run *****************************
echo:

start /d "./build/bin/%PROJECT_NAME%/%BUILD_TYPE%" %PROJECT_NAME%.exe