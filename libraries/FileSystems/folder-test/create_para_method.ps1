# This script creates a directory structure for the PARA method filing system.
# It will create the folders inside "Filing Cabinet\PARA Method".

$baseDir = "Filing Cabinet\PARA Method"

New-Item -ItemType Directory -Path "$baseDir\1. Projects\Example Project A" -Force
New-Item -ItemType Directory -Path "$baseDir\1. Projects\Example Project B" -Force
New-Item -ItemType Directory -Path "$baseDir\2. Areas\01 Personal\Finances" -Force
New-Item -ItemType Directory -Path "$baseDir\2. Areas\01 Personal\Health" -Force
New-Item -ItemType Directory -Path "$baseDir\2. Areas\02 Work\Admin" -Force
New-Item -ItemType Directory -Path "$baseDir\2. Areas\02 Work\Marketing" -Force
New-Item -ItemType Directory -Path "$baseDir\3. Resources\01 Topics\Productivity" -Force
New-Item -ItemType Directory -Path "$baseDir\3. Resources\01 Topics\Web Design" -Force
New-Item -ItemType Directory -Path "$baseDir\3. Resources\02 Assets\Templates" -Force
New-Item -ItemType Directory -Path "$baseDir\3. Resources\02 Assets\Stock Photos" -Force
New-Item -ItemType Directory -Path "$baseDir\4. Archive\Old Projects" -Force
New-Item -ItemType Directory -Path "$baseDir\4. Archive\Reference Material" -Force

Write-Host "PARA Method folder structure created successfully in '$baseDir'."