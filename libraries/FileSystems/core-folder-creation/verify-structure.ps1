# PowerShell script to verify that the folder structures were created correctly

Write-Host "Verifying folder structures..."
Write-Host ""

# Check main filing cabinet structure
Write-Host "Checking Main Filing Cabinet structure:"
if (Test-Path "Filing Cabinet\000_Inbox\009_TRASH" -PathType Container) { 
    Write-Host "[OK] Filing Cabinet\000_Inbox\009_TRASH" 
} else { 
    Write-Host "[MISSING] Filing Cabinet\000_Inbox\009_TRASH" 
}

if (Test-Path "Filing Cabinet\010_Projects\011_Website_Redesign" -PathType Container) { 
    Write-Host "[OK] Filing Cabinet\010_Projects\011_Website_Redesign" 
} else { 
    Write-Host "[MISSING] Filing Cabinet\010_Projects\011_Website_Redesign" 
}

Write-Host ""

# Check chronological structure
Write-Host "Checking Chronological structure:"
if (Test-Path "Filing Cabinet\Chronological Filing System\2026\01_January" -PathType Container) { 
    Write-Host "[OK] Filing Cabinet\Chronological Filing System\2026\01_January" 
} else { 
    Write-Host "[MISSING] Filing Cabinet\Chronological Filing System\2026\01_January" 
}

Write-Host ""

# Check Johnny Decimal structure
Write-Host "Checking Johnny Decimal structure:"
if (Test-Path "Filing Cabinet\Johnny Decimal Filing System\00-09 INBOX" -PathType Container) { 
    Write-Host "[OK] Filing Cabinet\Johnny Decimal Filing System\00-09 INBOX" 
} else { 
    Write-Host "[MISSING] Filing Cabinet\Johnny Decimal Filing System\00-09 INBOX" 
}

Write-Host ""

# Check PARA Method structure
Write-Host "Checking PARA Method structure:"
if (Test-Path "Filing Cabinet\PARA Method\1. Projects\Example Project A" -PathType Container) { 
    Write-Host "[OK] Filing Cabinet\PARA Method\1. Projects\Example Project A" 
} else { 
    Write-Host "[MISSING] Filing Cabinet\PARA Method\1. Projects\Example Project A" 
}

Write-Host ""

# Check Area-Based structure
Write-Host "Checking Area-Based structure:"
if (Test-Path "Filing Cabinet\Area-Based System\Finances\Bank Statements" -PathType Container) { 
    Write-Host "[OK] Filing Cabinet\Area-Based System\Finances\Bank Statements" 
} else { 
    Write-Host "[MISSING] Filing Cabinet\Area-Based System\Finances\Bank Statements" 
}

Write-Host ""
Write-Host "Verification complete!"