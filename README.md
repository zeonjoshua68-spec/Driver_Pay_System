# Driver_Pay_System
A simple console-based C++ application that calculates monthly and total pay for delivery/taxi drivers based on miles driven and rate per mile, including automatic UK-style income tax deductions.




**Description**

This program reads a list of drivers (ID, name, and rate per mile) from a text file, then reads how many miles each driver drove during January, February, and March from three separate monthly files. It matches the miles data to the correct driver by ID and calculates:

Gross pay (miles driven × rate per mile)
Tax deducted (based on an annualised tax-free allowance and a flat income tax rate)
Net pay (gross pay minus tax)

Users can then interactively search for a specific driver or view all drivers, and choose to see their pay for a single month or their total pay across all three months.

**Features**
Loads driver records and monthly mileage data from external text files
Case-insensitive driver ID matching
Monthly tax calculation using an annualised tax-free allowance (£12,570) and a flat 20% income tax rate
View pay for an individual month or totals across January–March
Search for a driver by ID or list pay details for every driver
Input validation for all menu selections and numeric entries
Currency values formatted to two decimal places
Graceful handling of missing files or unmatched driver IDs

**File Structure**
driver-pay-system/
├── main.cpp          # Source code
├── drivers.txt        # Driver ID, name, and rate per mile
├── jan26.txt           # January mileage data
├── feb26.txt           # February mileage data
├── mar26.txt            # March mileage data
└── README.md
**Input File Formats**

**drivers.txt — one driver per line: ID Name RatePerMile**

D001 JohnSmith 0.45
D002 JaneDoe 0.50

**jan26.txt / feb26.txt / mar26.txt — one entry per line: ID MilesDriven**

D001 1200
D002 950

Note: Since values are read with >>, driver names should not contain spaces (use a single word or an underscore, e.g. John_Smith).

**How to Build**

Using g++:

bash
g++ -std=c++11 -o driverpay main.cpp

**How to Run**

bash
./driverpay

Make sure drivers.txt, jan26.txt, feb26.txt, and mar26.txt are in the same directory as the executable.

**Example Usage**
Loaded 2 driver records from file.

===== Driver Pay Menu =====
1. Search for a driver
2. View all drivers
3. Exit
Enter your choice: 1
Enter driver ID to search for: D001

--- Pay details for JohnSmith (D001) ---
1. January
2. February
3. March
4. Total for all months
Enter your choice: 4

Driver ID: D001
Driver Name: JohnSmith
Rate per mile: $ 0.45
Total miles driven (Jan-Mar): 3600
Total pay before tax: $ 1620.00
Total tax deducted: $ 0.00
Total pay after tax: $ 1620.00

**Tax Calculation Logic**
Monthly gross pay is annualised (× 12) to check against the tax-free allowance:

If annual pay is at or below £12,570, no tax is deducted.
Otherwise, tax is charged at 20% on the amount above the allowance, then converted back to a monthly figure.
**Possible Improvements**
Support driver names containing spaces (e.g. using getline)
Validate mileage and rate values against negative numbers when read from file
Export pay reports to a file (CSV/TXT)
Support a configurable number of months instead of a fixed three
Add unit tests for tax and pay calculations

**Author**
Don Joshua Zeon

**License**
This project is open source and available for educational use.
