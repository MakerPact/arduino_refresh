# PowerShell script to create the folder structure for The Ultimate Filing System

# This script creates a directory structure for organizing your files.
# It will create a main folder called "Filing Cabinet" in the current directory.

$folders = @(
    "Filing Cabinet/000_Inbox/009_TRASH",
    "Filing Cabinet/010_Projects/011_Website_Redesign",
    "Filing Cabinet/010_Projects/012_Vacation_Planning_2026",
    "Filing Cabinet/010_Projects/013_Home_Renovation",
    "Filing Cabinet/010_Projects/019_TRASH",
    "Filing Cabinet/020_Areas/021_Finances/Budget",
    "Filing Cabinet/020_Areas/021_Finances/Receipts",
    "Filing Cabinet/020_Areas/021_Finances/Taxes",
    "Filing Cabinet/020_Areas/022_Health_&_Fitness/Workout_Logs",
    "Filing Cabinet/020_Areas/022_Health_&_Fitness/Recipes",
    "Filing Cabinet/020_Areas/022_Health_&_Fitness/Medical_Records",
    "Filing Cabinet/020_Areas/023_Professional_Development/Courses",
    "Filing Cabinet/020_Areas/023_Professional_Development/Certifications",
    "Filing Cabinet/020_Areas/023_Professional_Development/Performance_Reviews",
    "Filing Cabinet/020_Areas/024_Household/Maintenance_Records",
    "Filing Cabinet/020_Areas/024_Household/Utilities",
    "Filing Cabinet/020_Areas/024_Household/Vehicle_Information",
    "Filing Cabinet/020_Areas/029_TRASH",
    "Filing Cabinet/030_Documents/031_Identification",
    "Filing Cabinet/030_Documents/032_Contracts",
    "Filing Cabinet/030_Documents/033_Warranties_&_Manuals",
    "Filing Cabinet/030_Documents/034_Educational_Transcripts",
    "Filing Cabinet/030_Documents/039_TRASH",
    "Filing Cabinet/040_Resources/041_Programming_Languages",
    "Filing Cabinet/040_Resources/042_Marketing_Strategies",
    "Filing Cabinet/040_Resources/043_Photography_Techniques",
    "Filing Cabinet/040_Resources/044_Interesting_Articles",
    "Filing Cabinet/040_Resources/049_TRASH",
    "Filing Cabinet/050_Media/051_Photos",
    "Filing Cabinet/050_Media/052_Videos",
    "Filing Cabinet/050_Media/053_Music",
    "Filing Cabinet/050_Media/059_TRASH",
    "Filing Cabinet/090_Archive/Archived_Projects",
    "Filing Cabinet/090_Archive/Old_Job_Search_Materials",
    "Filing Cabinet/090_Archive/099_TRASH"
)

foreach ($folder in $folders) {
    New-Item -ItemType Directory -Force -Path $folder
}

Write-Host "Filing Cabinet structure created successfully."
