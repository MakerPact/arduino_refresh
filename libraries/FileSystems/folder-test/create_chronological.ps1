# This script creates a chronological folder structure for the current year.

$year = Get-Date -Format "yyyy"
$baseDir = "Filing Cabinet\Chronological Filing System"

$months = @(
    "01_January",
    "02_February",
    "03_March",
    "04_April",
    "05_May",
    "06_June",
    "07_July",
    "08_August",
    "09_September",
    "10_October",
    "11_November",
    "12_December"
)

foreach ($month in $months) {
    New-Item -ItemType Directory -Path "$baseDir\$year\$month" -Force
}

Write-Host "Chronological folder structure for $year created successfully in '$baseDir'."