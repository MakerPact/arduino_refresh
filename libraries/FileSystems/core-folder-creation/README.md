# Core Folder Creation Scripts

This directory contains simplified PowerShell scripts for creating organized folder structures. These scripts focus solely on the core functionality of creating directories without any website or documentation components.

## Scripts

1. **create-main-folders.ps1** - Creates a comprehensive filing cabinet structure with:
   - Inbox folders
   - Project-based folders
   - Area-based folders (Finances, Health, Professional Development, Household)
   - Document categories
   - Resource folders
   - Media folders
   - Archive folders

2. **create-chronological.ps1** - Creates a date-based folder structure organized by year and month

3. **create-johnny-decimal.ps1** - Creates folders organized by the Johnny Decimal system (numerical organization)

4. **create-para-method.ps1** - Creates folders organized by Projects, Areas, Resources, and Archive

## Usage

To run any of these scripts, use PowerShell with the bypass execution policy:

```powershell
powershell -ExecutionPolicy Bypass -File ".\script-name.ps1"
```

## Requirements

- Windows PowerShell 5.1 or later
- Appropriate permissions to create directories in the target location

These scripts will create all necessary parent directories automatically and will not fail if directories already exist.