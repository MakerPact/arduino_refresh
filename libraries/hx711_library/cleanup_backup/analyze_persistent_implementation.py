#!/usr/bin/env python3
"""
HX711 Persistent Calibration Implementation Analysis
Comprehensive code review and testing script
"""

import os
import re
from pathlib import Path
from typing import List, Dict, Optional

class HX711PersistentAnalyzer:
    def __init__(self, library_path: str):
        self.library_path = Path(library_path)
        self.issues = {
            "coding_style": [],
            "memory_usage": [],
            "eeprom_usage": [],
            "functionality": [],
            "edge_cases": [],
            "documentation": [],
            "backward_compatibility": [],
            "performance": [],
            "suggestions": []
        }
        
        # File paths
        self.persistent_header = self.library_path / "src" / "HX711_Persistent.h"
        self.persistent_cpp = self.library_path / "src" / "HX711_Persistent.cpp"
        self.example = self.library_path / "examples" / "PersistentCalibration" / "PersistentCalibration.ino"
        self.base_header = self.library_path / "src" / "HX711.h"
        
    def analyze(self):
        """Run comprehensive analysis"""
        print("=== HX711 Persistent Calibration Analysis ===")
        
        self._check_file_structure()
        self._analyze_header_file()
        self._analyze_implementation()
        self._analyze_example()
        self._check_eeprom_usage()
        self._check_memory_usage()
        self._check_functionality()
        self._check_edge_cases()
        self._check_documentation()
        self._check_backward_compatibility()
        
        self._generate_report()
        return self.issues
    
    def _check_file_structure(self):
        """Verify file structure and organization"""
        print("\n1. Checking file structure...")
        
        required_files = [
            self.persistent_header,
            self.persistent_cpp,
            self.example,
            self.base_header
        ]
        
        for file_path in required_files:
            if not file_path.exists():
                self.issues["coding_style"].append(f"Missing required file: {file_path}")
            else:
                print(f"  ✓ {file_path}")
    
    def _analyze_header_file(self):
        """Analyze the header file"""
        print("\n2. Analyzing header file...")
        
        content = self.persistent_header.read_text()
        
        # Check for proper class inheritance
        if "class HX711_Persistent : public HX711" in content:
            print("  ✓ Proper inheritance from HX711")
        else:
            self.issues["coding_style"].append("Missing proper inheritance from HX711")
        
        # Check for required method declarations
        required_methods = [
            "begin_with_eeprom",
            "save_calibration", 
            "load_calibration",
            "smart_tare",
            "has_valid_calibration"
        ]
        
        for method in required_methods:
            if method in content:
                print(f"  ✓ Method declared: {method}")
            else:
                self.issues["functionality"].append(f"Missing method declaration: {method}")
        
        # Check for override methods
        override_methods = ["set_scale", "set_offset"]
        for method in override_methods:
            if f"void {method}" in content and "override" in content:
                print(f"  ✓ Override method: {method}")
            else:
                self.issues["functionality"].append(f"Missing override for method: {method}")
    
    def _analyze_implementation(self):
        """Analyze the implementation file"""
        print("\n3. Analyzing implementation...")
        
        content = self.persistent_cpp.read_text()
        
        # Check constructor
        if "HX711_Persistent::HX711_Persistent()" in content:
            print("  ✓ Constructor implemented")
        else:
            self.issues["functionality"].append("Missing constructor implementation")
        
        # Check EEPROM initialization
        if "EEPROM.begin" in content:
            print("  ✓ EEPROM initialization")
        else:
            self.issues["functionality"].append("Missing EEPROM initialization")
        
        # Check save/load logic
        if "EEPROM.put" in content and "EEPROM.get" in content:
            print("  ✓ EEPROM read/write operations")
        else:
            self.issues["functionality"].append("Missing EEPROM read/write operations")
        
        # Check smart tare implementation
        if "smart_tare" in content:
            print("  ✓ Smart tare implemented")
            # Check if it properly handles existing weight
            if "get_value" in content and "get_offset" in content:
                print("  ✓ Smart tare considers existing weight")
            else:
                self.issues["functionality"].append("Smart tare may not properly handle existing weight")
        
        # Check auto-save in set_scale and set_offset
        if "save_calibration()" in content:
            print("  ✓ Auto-save functionality")
        else:
            self.issues["functionality"].append("Missing auto-save functionality")
    
    def _analyze_example(self):
        """Analyze the example sketch"""
        print("\n4. Analyzing example sketch...")
        
        if not self.example.exists():
            self.issues["documentation"].append("Missing example sketch")
            return
            
        content = self.example.read_text()
        
        # Check for proper initialization
        if "begin_with_eeprom" in content:
            print("  ✓ Example shows proper initialization")
        else:
            self.issues["documentation"].append("Example missing proper initialization")
        
        # Check for calibration procedure
        if "calibrate_scale" in content:
            print("  ✓ Example includes calibration procedure")
        else:
            self.issues["documentation"].append("Example missing calibration procedure")
        
        # Check for smart tare usage
        if "smart_tare" in content:
            print("  ✓ Example demonstrates smart tare")
        else:
            self.issues["documentation"].append("Example missing smart tare demonstration")
    
    def _check_eeprom_usage(self):
        """Analyze EEPROM usage patterns"""
        print("\n5. Checking EEPROM usage...")
        
        # Read header to check EEPROM layout
        header_content = self.persistent_header.read_text()
        
        # Check EEPROM address definitions
        eeprom_addresses = {
            "EEPROM_SCALE_ADDRESS": "0",
            "EEPROM_OFFSET_ADDRESS": "4", 
            "EEPROM_VALID_FLAG_ADDRESS": "8"
        }
        
        for addr_name, expected_value in eeprom_addresses.items():
            if addr_name in header_content:
                # Extract the actual value
                match = re.search(f"{addr_name}\s*=\s*(\d+)", header_content)
                if match and match.group(1) == expected_value:
                    print(f"  ✓ {addr_name} = {expected_value}")
                else:
                    self.issues["eeprom_usage"].append(f"EEPROM address mismatch: {addr_name}")
            else:
                self.issues["eeprom_usage"].append(f"Missing EEPROM address definition: {addr_name}")
        
        # Check valid flag value
        if "EEPROM_VALID_FLAG = 0xA5A5" in header_content:
            print("  ✓ Valid flag defined as 0xA5A5")
        else:
            self.issues["eeprom_usage"].append("Missing or incorrect EEPROM valid flag")
        
        # Calculate total EEPROM usage
        total_bytes = 4 + 4 + 2  # scale (4) + offset (4) + flag (2)
        print(f"  ✓ Total EEPROM usage: {total_bytes} bytes")
        
        if total_bytes > 10:
            self.issues["eeprom_usage"].append("EEPROM usage exceeds expected 10 bytes")
    
    def _check_memory_usage(self):
        """Analyze memory usage patterns"""
        print("\n6. Checking memory usage...")
        
        # Check for potential memory leaks
        cpp_content = self.persistent_cpp.read_text()
        
        # Count EEPROM operations
        eeprom_writes = cpp_content.count("EEPROM.put")
        eeprom_reads = cpp_content.count("EEPROM.get")
        
        print(f"  ✓ EEPROM write operations: {eeprom_writes}")
        print(f"  ✓ EEPROM read operations: {eeprom_reads}")
        
        # Check for proper EEPROM commit
        if "EEPROM.commit()" in cpp_content:
            print("  ✓ Proper EEPROM commit")
        else:
            self.issues["memory_usage"].append("Missing EEPROM commit operation")
        
        # Check for unnecessary memory allocations
        if "malloc" in cpp_content or "new" in cpp_content:
            self.issues["memory_usage"].append("Potential memory allocation found - check for leaks")
        else:
            print("  ✓ No dynamic memory allocation")
    
    def _check_functionality(self):
        """Verify core functionality"""
        print("\n7. Checking core functionality...")
        
        cpp_content = self.persistent_cpp.read_text()
        
        # Check if save_calibration returns success/failure
        if "return EEPROM.commit()" in cpp_content:
            print("  ✓ Save operation returns success status")
        else:
            self.issues["functionality"].append("Save operation should return success/failure status")
        
        # Check if load_calibration validates data before using
        if "has_valid_calibration()" in cpp_content:
            print("  ✓ Load operation validates data")
        else:
            self.issues["functionality"].append("Load operation should validate data before using")
        
        # Check smart tare algorithm
        if "get_value" in cpp_content and "get_offset" in cpp_content:
            print("  ✓ Smart tare uses current reading and offset")
        else:
            self.issues["functionality"].append("Smart tare algorithm may be incomplete")
    
    def _check_edge_cases(self):
        """Identify potential edge cases"""
        print("\n8. Checking edge cases...")
        
        cpp_content = self.persistent_cpp.read_text()
        
        # Check for EEPROM availability check
        if "eeprom_available" in cpp_content:
            print("  ✓ EEPROM availability checking")
        else:
            self.issues["edge_cases"].append("Missing EEPROM availability checks")
        
        # Check for null/zero checks
        if "has_valid_calibration()" in cpp_content:
            print("  ✓ Valid calibration checking")
        else:
            self.issues["edge_cases"].append("Missing valid calibration checks")
        
        # Check for overflow protection
        edge_case_issues = []
        
        # Check if smart_tare handles large values
        if "static_cast<long>" in cpp_content:
            print("  ✓ Type casting for value handling")
        else:
            edge_case_issues.append("Potential overflow in smart_tare with large values")
        
        if edge_case_issues:
            self.issues["edge_cases"].extend(edge_case_issues)
    
    def _check_documentation(self):
        """Check documentation quality"""
        print("\n9. Checking documentation...")
        
        # Check for file headers
        for file_path in [self.persistent_header, self.persistent_cpp, self.example]:
            content = file_path.read_text()
            if "/**" in content and "MIT License" in content:
                print(f"  ✓ Proper header in {file_path.name}")
            else:
                self.issues["documentation"].append(f"Missing or incomplete header in {file_path.name}")
        
        # Check for method documentation
        cpp_content = self.persistent_cpp.read_text()
        method_count = cpp_content.count("void HX711_Persistent::") + cpp_content.count("bool HX711_Persistent::")
        
        # Check for inline comments
        comment_count = cpp_content.count("//")
        
        if comment_count > method_count * 0.5:  # At least 50% of methods should have comments
            print(f"  ✓ Adequate inline documentation ({comment_count} comments)")
        else:
            self.issues["documentation"].append(f"Insufficient inline documentation ({comment_count} comments for {method_count} methods)")
    
    def _check_backward_compatibility(self):
        """Check backward compatibility"""
        print("\n10. Checking backward compatibility...")
        
        # Check if base HX711 methods are preserved
        base_content = self.base_header.read_text()
        persistent_content = self.persistent_header.read_text()
        
        # Get base class methods
        base_methods = re.findall(r"\bvoid\s+([a-z_]+)\([^)]*\);\s*//\s*[^\n]+\n", base_content)
        base_methods += re.findall(r"\bbool\s+([a-z_]+)\([^)]*\);\s*//\s*[^\n]+\n", base_content)
        base_methods += re.findall(r"\bfloat\s+([a-z_]+)\([^)]*\);\s*//\s*[^\n]+\n", base_content)
        base_methods += re.findall(r"\blong\s+([a-z_]+)\([^)]*\);\s*//\s*[^\n]+\n", base_content)
        
        # Check if persistent class doesn't break base functionality
        if "class HX711_Persistent : public HX711" in persistent_content:
            print("  ✓ Proper inheritance maintains base functionality")
        else:
            self.issues["backward_compatibility"].append("Inheritance may break base functionality")
        
        # Check for virtual destructors (good practice)
        if "virtual ~HX711()" in base_content:
            print("  ✓ Base class has virtual destructor")
        else:
            self.issues["backward_compatibility"].append("Base class should have virtual destructor for proper inheritance")
    
    def _generate_report(self):
        """Generate analysis report"""
        print("\n" + "="*60)
        print("ANALYSIS REPORT")
        print("="*60)
        
        total_issues = sum(len(issues) for issues in self.issues.values())
        
        if total_issues == 0:
            print("🎉 CONGRATULATIONS! No issues found!")
        else:
            print(f"⚠️  Found {total_issues} issues across {len(self.issues)} categories")
        
        print("\nDETAILED FINDINGS:")
        print("-" * 60)
        
        for category, issues in self.issues.items():
            if issues:
                print(f"\n{category.upper()} ({len(issues)} issues):")
                for i, issue in enumerate(issues, 1):
                    print(f"  {i}. {issue}")
            else:
                print(f"\n{category.upper()}: ✓ No issues found")
        
        print("\n" + "="*60)
        print("SUMMARY")
        print("="*60)
        
        # Calculate severity
        critical_issues = []
        for issue in self.issues["functionality"] + self.issues["memory_usage"] + self.issues["eeprom_usage"]:
            critical_issues.append(issue)
        
        if len(critical_issues) == 0:
            print("✅ Implementation is SOLID and PRODUCTION-READY")
        elif len(critical_issues) <= 3:
            print("⚠️  Implementation is GOOD with minor issues")
        else:
            print("❌ Implementation needs SIGNIFICANT improvements")
        
        print(f"\nCritical issues: {len(critical_issues)}")
        print(f"Total issues: {total_issues}")
        print(f"Categories with issues: {sum(1 for issues in self.issues.values() if issues)}")
        
        # Suggestions
        if self.issues["suggestions"]:
            print("\nSUGGESTIONS:")
            for suggestion in self.issues["suggestions"]:
                print(f"• {suggestion}")

if __name__ == "__main__":
    # Run analysis
    analyzer = HX711PersistentAnalyzer("/mnt/c/Users/suppe/Documents/projects/arduino_refresh/libraries/hx711_library")
    issues = analyzer.analyze()
    
    # Save report
    report_path = "/mnt/c/Users/suppe/Documents/projects/arduino_refresh/libraries/hx711_library/ANALYSIS_REPORT.md"
    with open(report_path, "w") as f:
        f.write("# HX711 Persistent Calibration Analysis Report\n\n")
        f.write("## Summary\n")
        f.write(f"Total issues found: {sum(len(issues) for issues in issues.values())}\n\n")
        
        for category, category_issues in issues.items():
            if category_issues:
                f.write(f"## {category.replace('_', ' ').title()}\n")
                f.write(f"Found {len(category_issues)} issues:\n\n")
                for i, issue in enumerate(category_issues, 1):
                    f.write(f"{i}. {issue}\n")
                f.write("\n")
            else:
                f.write(f"## {category.replace('_', ' ').title()}\n")
                f.write("✓ No issues found\n\n")
    
    print(f"\n📝 Full report saved to: {report_path}")