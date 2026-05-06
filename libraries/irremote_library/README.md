# IRremote Library - Arduino Refresh

This directory contains the IRremote library with fixes and improvements for the Arduino Refresh project.

## Directory Structure

- `original/` - Original IRremote library files (unmodified)
- `examples/` - Fixed and improved examples
- `src/` - Fixed source files
- `hermes/` - Hermes-generated analysis, testing, and documentation (Git ignored)

## Fixes Implemented

1. **ReceiveDemo Fix** - Compilation bug when DEBUG_BUTTON_PIN undefined
2. **8-bit Overflow Fix** - Buffer length overflow when RAW_BUFFER_LENGTH > 254
3. **Arduino Standards Compliance** - Code style and best practices
4. **RC5 Toggle Bit Fix** - Main focus of this refresh

## Branches

- `feature/irremote-receivedemo-fix` - ReceiveDemo compilation fix
- `feature/irremote-overflow-fix` - 8-bit overflow fix  
- `feature/irremote-standards-compliance` - Standards compliance improvements
- `feature/irremote-test-suite` - Comprehensive test suite
- `feature/irremote-rc5-toggle-fix` - RC5 toggle bit fix (main branch)

## Development Workflow

1. Work on specific fix branches
2. Test thoroughly in hermes/testing/
3. Document in hermes/documentation/
4. Merge to main when ready

## Hermes Folders

All files in `hermes/` are automatically excluded from Git tracking via .gitignore.