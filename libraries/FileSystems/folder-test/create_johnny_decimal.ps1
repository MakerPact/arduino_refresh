# This script creates a directory structure for the Johnny Decimal filing system.
# It will create a main folder called "Johnny Decimal Filing System" inside "Filing Cabinet".

$baseDir = "Filing Cabinet\Johnny Decimal Filing System"

New-Item -ItemType Directory -Path "$baseDir\00-09 INBOX" -Force
New-Item -ItemType Directory -Path "$baseDir\10-19 Personal\11 Finances\11.01 Banking" -Force
New-Item -ItemType Directory -Path "$baseDir\10-19 Personal\11 Finances\11.02 Taxes" -Force
New-Item -ItemType Directory -Path "$baseDir\10-19 Personal\12 Health\12.01 Medical Records" -Force
New-Item -ItemType Directory -Path "$baseDir\10-19 Personal\12 Health\12.02 Fitness" -Force
New-Item -ItemType Directory -Path "$baseDir\20-29 Work\21 Projects\21.01 Project A" -Force
New-Item -ItemType Directory -Path "$baseDir\20-29 Work\21 Projects\21.02 Project B" -Force
New-Item -ItemType Directory -Path "$baseDir\20-29 Work\22 Admin\22.01 Reports" -Force
New-Item -ItemType Directory -Path "$baseDir\20-29 Work\22 Admin\22.02 Presentations" -Force
New-Item -ItemType Directory -Path "$baseDir\30-39 Hobbies\31 Photography\31.01 Camera Gear" -Force
New-Item -ItemType Directory -Path "$baseDir\30-39 Hobbies\31 Photography\31.02 Photos" -Force
New-Item -ItemType Directory -Path "$baseDir\30-39 Hobbies\32 Music\32.01 Guitar Tabs" -Force
New-Item -ItemType Directory -Path "$baseDir\30-39 Hobbies\32 Music\32.02 Production" -Force
New-Item -ItemType Directory -Path "$baseDir\40-49 Archives" -Force

Write-Host "Johnny Decimal Filing System structure created successfully in '$baseDir'."