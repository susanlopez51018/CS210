//Susan Lopez
//Project 2 

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class InvestmentCalculator {
private:
    double initialInvestment;
    double monthlyDeposit;
    double annualInterestRate;
    int numYears;

    struct YearlyReport {
        int year;
        double yearEndBalance;
        double yearEndInterest;
    };

    vector<YearlyReport> reportWithoutDeposits;
    vector<YearlyReport> reportWithDeposits;

public:
    // Constructor
    InvestmentCalculator(double initial, double monthly, double interest, int years)
        : initialInvestment(initial), monthlyDeposit(monthly), annualInterestRate(interest), numYears(years) {
    }

    // Generate reports
    void generateReports() {
        calculateWithoutDeposits();
        calculateWithDeposits();
    }

    // Display results
    void displayReports() {
        cout << "\nBalance and Interest Without Additional Monthly Deposits\n";
        cout << "========================================================\n";
        cout << setw(10) << "Year" << setw(20) << "Year-End Balance" << setw(20) << "Year-End Interest\n";
        cout << "--------------------------------------------------------\n";
        for (const auto& report : reportWithoutDeposits) {
            cout << setw(10) << report.year << setw(20) << fixed << setprecision(2) << report.yearEndBalance
                << setw(20) << report.yearEndInterest << endl;
        }

        cout << "\nBalance and Interest With Additional Monthly Deposits\n";
        cout << "=====================================================\n";
        cout << setw(10) << "Year" << setw(20) << "Year-End Balance" << setw(20) << "Year-End Interest\n";
        cout << "-----------------------------------------------------\n";
        for (const auto& report : reportWithDeposits) {
            cout << setw(10) << report.year << setw(20) << fixed << setprecision(2) << report.yearEndBalance
                << setw(20) << report.yearEndInterest << endl;
        }
    }

private:
    // Calculate without monthly deposits
    void calculateWithoutDeposits() {
        double balance = initialInvestment;
        for (int year = 1; year <= numYears; ++year) {
            double interest = balance * (annualInterestRate / 100);
            balance += interest;
            reportWithoutDeposits.push_back({ year, balance, interest });
        }
    }

    // Calculate with monthly deposits
    void calculateWithDeposits() {
        double balance = initialInvestment;
        for (int year = 1; year <= numYears; ++year) {
            double totalInterest = 0.0;
            for (int month = 1; month <= 12; ++month) {
                balance += monthlyDeposit;
                double monthlyInterest = balance * ((annualInterestRate / 100) / 12);
                totalInterest += monthlyInterest;
                balance += monthlyInterest;
            }
            reportWithDeposits.push_back({ year, balance, totalInterest });
        }
    }
};

int main() {
    double initialInvestment, monthlyDeposit, annualInterestRate;
    int numYears;

    // Input
    cout << "==================== Investment Calculator ====================\n";
    cout << "Enter Initial Investment Amount: $";
    cin >> initialInvestment;
    cout << "Enter Monthly Deposit: $";
    cin >> monthlyDeposit;
    cout << "Enter Annual Interest Rate (in %): ";
    cin >> annualInterestRate;
    cout << "Enter Number of Years: ";
    cin >> numYears;

    // Validate inputs
    if (initialInvestment <= 0 || monthlyDeposit < 0 || annualInterestRate <= 0 || numYears <= 0) {
        cerr << "Error: All inputs must be positive values.\n";
        return 1;
    }

    // Create calculator object
    InvestmentCalculator calculator(initialInvestment, monthlyDeposit, annualInterestRate, numYears);

    // Generate and display reports
    calculator.generateReports();
    calculator.displayReports();

    return 0;
}
