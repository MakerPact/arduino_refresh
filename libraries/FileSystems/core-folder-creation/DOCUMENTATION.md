# Core Folder Creation System Documentation

This documentation explains how to use the core folder creation scripts to organize your files efficiently.

## Table of Contents
1. [Overview](#overview)
2. [Available Scripts](#available-scripts)
3. [Usage Instructions](#usage-instructions)
4. [Folder Structures](#folder-structures)
5. [Validation](#validation)
6. [Troubleshooting](#troubleshooting)

## Overview

The Core Folder Creation System provides PowerShell scripts to generate organized directory structures for personal and professional file organization. These scripts focus solely on folder creation without any website or documentation components.

## Available Scripts

1. **create-main-folders.ps1** - Creates a comprehensive filing cabinet with multiple organizational systems
2. **create-chronological.ps1** - Creates date-based folder structure organized by year and month
3. **create-johnny-decimal.ps1** - Implements the Johnny Decimal numerical organization system
4. **create-para-method.ps1** - Creates folders organized by Projects, Areas, Resources, and Archive
5. **create-area-based.ps1** - Creates folders organized by broad categories (new addition)
6. **verify-structure.ps1** - Validates that folder structures were created correctly
7. **run-all.bat** - Runs all creation scripts at once
8. **verify-all.bat** - Runs the verification script

## Usage Instructions

### Prerequisites
- Windows PowerShell 5.1 or later
- Appropriate permissions to create directories in the target location

### Running Individual Scripts
To run any individual script, use PowerShell with the bypass execution policy:

```powershell
powershell -ExecutionPolicy Bypass -File ".\script-name.ps1"
```

### Running All Scripts
To run all creation scripts at once, execute the batch file:

```cmd
run-all.bat
```

### Verifying Folder Structures
To verify that folder structures were created correctly:

```cmd
verify-all.bat
```

Or directly with PowerShell:

```powershell
powershell -ExecutionPolicy Bypass -File ".\verify-structure.ps1"
```

## Folder Structures

### Main Filing Cabinet Structure
The main structure creates these top-level folders:
- Inbox (with TRASH subfolder)
- Projects (with various project folders and TRASH)
- Areas (Finances, Health & Fitness, Professional Development, Household, each with subfolders)
- Documents (Identification, Contracts, Warranties & Manuals, Educational Transcripts, each with TRASH)
- Resources (Programming Languages, Marketing Strategies, Photography Techniques, Interesting Articles, each with TRASH)
- Media (Photos, Videos, Music, each with TRASH)
- Archive (Archived Projects, Old Job Search Materials, with TRASH)

### Chronological Structure
Creates a time-based structure under "Chronological Filing System":
- Year folder (current year)
- Month folders (01_January through 12_December)

### Johnny Decimal System
Creates a numerical organization system with these main categories:
- 00-09 INBOX
- 10-19 Personal (Finances, Health)
- 20-29 Work (Projects, Admin)
- 30-39 Hobbies (Photography, Music)
- 40-49 Archives

### PARA Method
Organizes folders by:
- 1. Projects (Example Project A, Example Project B)
- 2. Areas (Personal and Work with subcategories)
- 3. Resources (Topics and Assets with subcategories)
- 4. Archive (Old Projects, Reference Material)

### Area-Based System (New Addition)
Organizes folders by broad categories:
- Finances (Bank Statements, Investments, Taxes, Receipts)
- Health (Medical Records, Insurance, Workout Logs, Nutrition)
- Work (Projects, Clients, Meetings, Training)
- Personal (Identities, Vehicles, Housing, Travel)
- Media (Photos, Videos, Music, Documents)
- Resources (Books, Articles, Templates, Tools)

## Validation

The verification script checks for the existence of key folders in each structure to ensure they were created correctly. It provides color-coded output indicating which folders are present (green checkmark) and which are missing (red X).

## Troubleshooting

### Issue: Scripts Fail on Windows
**Solution**: Ensure you're using the `.ps1` scripts with PowerShell and running with appropriate execution policy:
```cmd
powershell -ExecutionPolicy Bypass -File ".\script-name.ps1"
```

### Issue: Files Are Hard to Find
**Solution**:
- Use Windows Search to locate files by name
- Consider creating shortcuts or symbolic links to frequently accessed folders

### Issue: Permission Denied Errors
**Solution**:
- Run PowerShell as Administrator
- Ensure you have write permissions in the target directory

### Issue: Folders Already Exist
**Solution**: The scripts use the `-Force` parameter, which means they will not fail if folders already exist. Existing folders will be left untouched.

## Customization

You can customize any of the scripts by editing them directly:
1. Open the `.ps1` file in a text editor
2. Modify the folder names and structure as needed
3. Save the file and run it again

Each script is designed to be easily modified for your specific organizational needs.