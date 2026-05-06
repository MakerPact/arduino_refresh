@echo off
echo Verifying all folder structures...
echo.

powershell -ExecutionPolicy Bypass -File ".\verify-structure.ps1"
echo.

pause