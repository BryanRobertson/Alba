@echo off

@COLOR 0F

set ERRORLEVEL_BACKUP=0

pushd %CD%

set SHARPMAKE_EXECUTABLE=.\SharpmakeExe\Sharpmake.Application.exe

if not exist %SHARPMAKE_EXECUTABLE% echo Cannot find sharpmake executable in %~dp0%~1\%~2 & pause & goto error 

echo Using executable %SHARPMAKE_EXECUTABLE%
call %SHARPMAKE_EXECUTABLE%  /sources(@"Alba.Solution.sharpmake.cs")

set ERRORLEVEL_BACKUP=%ERRORLEVEL%
if %errorlevel% neq 0 GOTO :error

:: restore caller current directory
popd
goto :end

:end
exit /b 0

:error
@COLOR 4F
pause
exit /b 1