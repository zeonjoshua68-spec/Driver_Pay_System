//Student name: Don Joshua Zeon
//G num:G21407231
//date: 06/06/2024
// Module: Programming 
//Driver pay system
//Expected Band:62-68

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;



const int    decimalPlaces = 2;               // pay is shown to 2 decimal places
const double minimumMiles = 0.0;             // miles driven cannot be negative
const double minimumRate = 0.0;             // rate per mile cannot be negative
const string driversFileName = "drivers.txt"; // file containing driver ID, name and rate

const double taxFreeAllowance = 12570.0;      // annual pay below this is not taxed
const double incomeTaxRate = 0.20;            // 20% income tax
const int    monthsPerYear = 12;              // used to convert monthly pay to/from annual pay

 
const int    numberOfMonths = 3;
const string monthFileNames[numberOfMonths] = { "jan26.txt", "feb26.txt", "mar26.txt" };
const string monthNames[numberOfMonths] = { "January", "February", "March" };


// Struct: Driver
struct Driver
{
    string id;
    string name;
    double ratePerMile;
    double milesDriven[numberOfMonths] = { 0.0, 0.0, 0.0 };
};


// Struct: PayDetails

struct PayDetails
{
    double grossPay;
    double tax;
    double netPay;
};


// Function: readDriverDetails

vector<Driver> readDriverDetails(const string& fileName)
{
    vector<Driver> drivers;          // will hold all the drivers from the file
    ifstream driversFile(fileName);

    if (!driversFile.is_open())
    {
        cerr << "Failed to open file: " << fileName << endl;
        return drivers;               // return an empty vector on failure
    }

    string driverId;                 // temporary variables to hold one driver's
    string driverName;                // details at a time before they are
    double driverRate;                 // stored in the vector

    while (driversFile >> driverId >> driverName >> driverRate)
    {
        Driver newDriver;
        newDriver.id = driverId;
        newDriver.name = driverName;
        newDriver.ratePerMile = driverRate;

        drivers.push_back(newDriver);
    }

    driversFile.close();
    return drivers;
}


// Function: getValidNumber

double getValidNumber(const string& prompt, double minimumValue)
{
    double userValue;

    cout << prompt;
    cin >> userValue;

    while (cin.fail() || userValue < minimumValue)
    {
        cin.clear();              // clear the input error flag
        cin.ignore(1000, '\n');   // throw away the bad input left in the buffer

        cout << "Invalid entry. Please enter a number of "
            << minimumValue << " or greater: ";
        cin >> userValue;
    }

    return userValue;
}


// Function: getValidChoice
int getValidChoice(const string& prompt, int minimumChoice, int maximumChoice)
{
    int userChoice;

    cout << prompt;
    cin >> userChoice;

    while (cin.fail() || userChoice < minimumChoice || userChoice > maximumChoice)
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid entry. Please enter a number between "
            << minimumChoice << " and " << maximumChoice << ": ";
        cin >> userChoice;
    }

    return userChoice;
}


// Function: toUpperCase

string toUpperCase(const string& text)
{
    string upperText = text;

    for (int i = 0; i < (int)upperText.length(); i++)
    {
        upperText[i] = toupper(upperText[i]);
    }

    return upperText;
}


// Function: formatToTwoDecimalPlaces

string formatToTwoDecimalPlaces(double amount)
{
    // Build the multiplier (10, 100, 1000...) from decimalPlaces
    // instead of hardcoding 100 as a magic number.
    long multiplier = 1;
    for (int i = 0; i < decimalPlaces; i++)//this 
    {
        multiplier *= 10;
    }

    // Shift the decimal point, then round to the nearest
    // whole number (adding 0.5 before truncating is a simple
    // rounding trick for non-negative numbers).
    long  totalUnits = (long)(amount * multiplier + 0.5);

    long wholePart = totalUnits / multiplier;
    long fractionPart = totalUnits % multiplier;

    string fractionText = to_string(fractionPart);

    // Pad the fraction with leading zeros if it is too short,
    // e.g. 5 pence should be shown as "05", not "5".
    while ((int)fractionText.length() < decimalPlaces)
    {
        fractionText = "0" + fractionText;
    }

    return to_string(wholePart) + "." + fractionText;
}


// Function: calculateMonthlyTax

double calculateMonthlyTax(double monthlyPay)
{
    double annualPay = monthlyPay * monthsPerYear;

    if (annualPay <= taxFreeAllowance)
    {
        return 0.0;               // no tax owed below the tax free allowance
    }

    double taxableIncome = annualPay - taxFreeAllowance;
    double annualTax = taxableIncome * incomeTaxRate;
    double monthlyTax = annualTax / monthsPerYear;

    return monthlyTax;
}


// Function: calculateMonthlyPay

PayDetails calculateMonthlyPay(const Driver& driver, int monthIndex)
{
    PayDetails pay;

    pay.grossPay = driver.milesDriven[monthIndex] * driver.ratePerMile;
    pay.tax = calculateMonthlyTax(pay.grossPay);
    pay.netPay = pay.grossPay - pay.tax;

    return pay;
}


// Function: calculateTotalPay

PayDetails calculateTotalPay(const Driver& driver)
{
    PayDetails total;
    total.grossPay = 0.0;
    total.tax = 0.0;
    total.netPay = 0.0;

    for (int month = 0; month < numberOfMonths; month++)
    {
        PayDetails monthlyPay = calculateMonthlyPay(driver, month);

        total.grossPay += monthlyPay.grossPay;
        total.tax += monthlyPay.tax;
        total.netPay += monthlyPay.netPay;
    }

    return total;
}


// Function: displayMonthlyPay

void displayMonthlyPay(const Driver& driver, int monthIndex)
{
    PayDetails pay = calculateMonthlyPay(driver, monthIndex);

    cout << "\nDriver ID: " << driver.id << endl;
    cout << "Driver Name: " << driver.name << endl;
    cout << "Month: " << monthNames[monthIndex] << endl;
    cout << "Rate per mile: $ "
        << formatToTwoDecimalPlaces(driver.ratePerMile) << endl;
    cout << "Miles driven: " << driver.milesDriven[monthIndex] << endl;
    cout << "Monthly pay before tax: $ "
        << formatToTwoDecimalPlaces(pay.grossPay) << endl;
    cout << "Monthly tax deducted: $ "
        << formatToTwoDecimalPlaces(pay.tax) << endl;
    cout << "Monthly pay after tax: $ "
        << formatToTwoDecimalPlaces(pay.netPay) << endl;
}


// Function: displayTotalPay

void displayTotalPay(const Driver& driver)
{
    PayDetails total = calculateTotalPay(driver);

    double totalMiles = 0.0;
    for (int month = 0; month < numberOfMonths; month++)
    {
        totalMiles += driver.milesDriven[month];
    }

    cout << "\nDriver ID: " << driver.id << endl;
    cout << "Driver Name: " << driver.name << endl;
    cout << "Rate per mile: $ "
        << formatToTwoDecimalPlaces(driver.ratePerMile) << endl;
    cout << "Total miles driven (Jan-Mar): " << totalMiles << endl;
    cout << "Total pay before tax: $ "
        << formatToTwoDecimalPlaces(total.grossPay) << endl;
    cout << "Total tax deducted: $ "
        << formatToTwoDecimalPlaces(total.tax) << endl;
    cout << "Total pay after tax: $ "
        << formatToTwoDecimalPlaces(total.netPay) << endl;
}


// Function: readMonthlyMiles

void readMonthlyMiles(const string& fileName, vector<Driver>& drivers, int monthIndex)
{
    ifstream milesFile(fileName);

    if (!milesFile.is_open())
    {
        cerr << "Failed to open file: " << fileName << endl;
        return; // return on failure
    }

    string driverId;
    double milesDriven;

    while (milesFile >> driverId >> milesDriven)
    {
        string upperFileId = toUpperCase(driverId);
        bool matchFound = false;

        for (Driver& driver : drivers) 
        {
            if (toUpperCase(driver.id) == upperFileId)
            {
                driver.milesDriven[monthIndex] = milesDriven;
                matchFound = true;
                break;
            }
        }

        if (!matchFound)
        {
            cout << "Error: driver ID " << driverId
                << " in file " << fileName
                << " does not match any known driver." << endl;
        }
    }

    milesFile.close();
}


// Function: searchDriverById

int searchDriverById(const vector<Driver>& drivers, const string& searchId)
{
    string upperSearchId = toUpperCase(searchId);

    for (int index = 0; index < (int)drivers.size(); index++)
    {
        if (toUpperCase(drivers[index].id) == upperSearchId)
        {
            return index;
        }
    }

    return -1;   // no driver found with this ID
}

// Function: chooseMonthOrTotal

int chooseMonthOrTotal()
{
    cout << "\n1. January" << endl;
    cout << "2. February" << endl;
    cout << "3. March" << endl;
    cout << "4. Total for all months" << endl;

    int choice = getValidChoice("Enter your choice: ", 1, numberOfMonths + 1);

    return choice - 1;   // convert menu choice into an array index (or numberOfMonths for "total")
}


// Function: displayDriverPayMenu

void displayDriverPayMenu(const Driver& driver)
{
    cout << "\n--- Pay details for " << driver.name
        << " (" << driver.id << ") ---" << endl;

    int monthChoice = chooseMonthOrTotal();

    if (monthChoice == numberOfMonths)
    {
        displayTotalPay(driver);
    }
    else
    {
        displayMonthlyPay(driver, monthChoice);
    }
}

// Function: displayAllDriversPayMenu

void displayAllDriversPayMenu(const vector<Driver>& drivers)
{
    cout << "\n--- Pay details for all drivers ---" << endl;

    int monthChoice = chooseMonthOrTotal();

    for (int index = 0; index < (int)drivers.size(); index++)
    {
        if (monthChoice == numberOfMonths)
        {
            displayTotalPay(drivers[index]);
        }
        else
        {
            displayMonthlyPay(drivers[index], monthChoice);
        }
    }
}

// Function: runMenu

void runMenu(const vector<Driver>& drivers)
{
    const int searchOption = 1;
    const int viewAllOption = 2;
    const int exitOption = 3;

    bool keepRunning = true;

    while (keepRunning)
    {
        cout << "\n===== Driver Pay Menu =====" << endl;
        cout << "1. Search for a driver" << endl;
        cout << "2. View all drivers" << endl;
        cout << "3. Exit" << endl;

        int mainChoice = getValidChoice("Enter your choice: ", searchOption, exitOption);

        if (mainChoice == searchOption)
        {
            cout << "Enter driver ID to search for: ";
            string searchId;
            cin >> searchId;

            int foundIndex = searchDriverById(drivers, searchId);

            if (foundIndex == -1)
            {
                cout << "No driver found with ID " << searchId << endl;
            }
            else
            {
                displayDriverPayMenu(drivers[foundIndex]);
            }
        }
        else if (mainChoice == viewAllOption)
        {
            displayAllDriversPayMenu(drivers);
        }
        else
        {
            keepRunning = false;
        }
    }
}


// Main function

int main()
{
    vector<Driver> drivers = readDriverDetails(driversFileName);

    if (drivers.empty())
    {
        cout << "No driver details were loaded. Ending program." << endl;
        return 1;
    }

    cout << "Loaded " << drivers.size()
        << " driver records from file." << endl;

    for (int month = 0; month < numberOfMonths; month++)
    {
        readMonthlyMiles(monthFileNames[month], drivers, month);
    }

    runMenu(drivers);

    return 0;
}


