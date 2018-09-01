@echo off
@COLOR 0F

pushd %CD%
cd Source\Sharpmake
call GenerateProjects.bat

if %errorlevel% neq 0 GOTO :error

goto :end

:end
popd
exit /b 0

:error
popd
@COLOR 4F
pause
exit /b 1