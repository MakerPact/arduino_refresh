@echo off
echo Running all folder creation scripts...
echo.

echo Creating main folder structure...
powershell -ExecutionPolicy Bypass -File ".\create-main-folders.ps1"
echo.

echo Creating chronological folder structure...
powershell -ExecutionPolicy Bypass -File ".\create-chronological.ps1"
echo.

echo Creating Johnny Decimal folder structure...
powershell -ExecutionPolicy Bypass -File ".\create-johnny-decimal.ps1"
echo.

echo Creating PARA method folder structure...
powershell -ExecutionPolicy Bypass -File ".\create-para-method.ps1"
echo.

echo All folder structures created successfully!
pause