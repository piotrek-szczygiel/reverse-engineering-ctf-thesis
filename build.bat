@echo off
echo Building vm.exe...
g++ vm.cpp -o vm.exe -Wall || goto :error

echo Building program.bin...
nasm program.nasm -o program.bin || goto :error

echo Executing...
.\vm.exe program.bin || goto :error

goto :EOF

:error
echo Failed with exit code %errorlevel%
exit /b %errorlevel%
