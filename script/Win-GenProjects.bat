@echo off
IF EXIST %~dp0\..\.vs  rd /s /q %~dp0\..\.vs
IF EXIST %~dp0\..\bin  rd /s /q %~dp0\..\bin
IF EXIST %~dp0\..\bin-int  rd /s /q %~dp0\..\bin-int
IF EXIST %~dp0\..\Imter.sln  del /f /s /q %~dp0\..\Imter.sln
IF EXIST %~dp0\..\Imter\Imter.vcxproj  del /f /s /q %~dp0\..\Imter\Imter.vcxproj
IF EXIST %~dp0\..\Imter.vcxproj.filters  del /f /s /q %~dp0\..\Imter\Imter.vcxproj.filters
IF EXIST %~dp0\..\Imter.vcxproj.user  del /f /s /q %~dp0\..\Imter\Imter.vcxproj.user
pushd %~dp0\..\
call script\premake5.exe vs2022
popd
PAUSE
