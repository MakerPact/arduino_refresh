# Simplified script for area-based folder structure
# Creates folders organized by broad categories

$baseDir = "Filing Cabinet\Area-Based System"

# Main categories
New-Item -ItemType Directory -Path "$baseDir\Finances" -Force
New-Item -ItemType Directory -Path "$baseDir\Health" -Force
New-Item -ItemType Directory -Path "$baseDir\Work" -Force
New-Item -ItemType Directory -Path "$baseDir\Personal" -Force
New-Item -ItemType Directory -Path "$baseDir\Media" -Force
New-Item -ItemType Directory -Path "$baseDir\Resources" -Force

# Subcategories for Finances
New-Item -ItemType Directory -Path "$baseDir\Finances\Bank Statements" -Force
New-Item -ItemType Directory -Path "$baseDir\Finances\Investments" -Force
New-Item -ItemType Directory -Path "$baseDir\Finances\Taxes" -Force
New-Item -ItemType Directory -Path "$baseDir\Finances\Receipts" -Force

# Subcategories for Health
New-Item -ItemType Directory -Path "$baseDir\Health\Medical Records" -Force
New-Item -ItemType Directory -Path "$baseDir\Health\Insurance" -Force
New-Item -ItemType Directory -Path "$baseDir\Health\Workout Logs" -Force
New-Item -ItemType Directory -Path "$baseDir\Health\Nutrition" -Force

# Subcategories for Work
New-Item -ItemType Directory -Path "$baseDir\Work\Projects" -Force
New-Item -ItemType Directory -Path "$baseDir\Work\Clients" -Force
New-Item -ItemType Directory -Path "$baseDir\Work\Meetings" -Force
New-Item -ItemType Directory -Path "$baseDir\Work\Training" -Force

# Subcategories for Personal
New-Item -ItemType Directory -Path "$baseDir\Personal\Identities" -Force
New-Item -ItemType Directory -Path "$baseDir\Personal\Vehicles" -Force
New-Item -ItemType Directory -Path "$baseDir\Personal\Housing" -Force
New-Item -ItemType Directory -Path "$baseDir\Personal\Travel" -Force

# Subcategories for Media
New-Item -ItemType Directory -Path "$baseDir\Media\Photos" -Force
New-Item -ItemType Directory -Path "$baseDir\Media\Videos" -Force
New-Item -ItemType Directory -Path "$baseDir\Media\Music" -Force
New-Item -ItemType Directory -Path "$baseDir\Media\Documents" -Force

# Subcategories for Resources
New-Item -ItemType Directory -Path "$baseDir\Resources\Books" -Force
New-Item -ItemType Directory -Path "$baseDir\Resources\Articles" -Force
New-Item -ItemType Directory -Path "$baseDir\Resources\Templates" -Force
New-Item -ItemType Directory -Path "$baseDir\Resources\Tools" -Force

Write-Host "Area-Based folder structure created successfully in '$baseDir'."