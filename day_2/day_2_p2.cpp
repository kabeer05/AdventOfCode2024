#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

bool isSafe(const vector<int> &report)
{
    bool increasing = true, decreasing = true;
    for (int i = 1; i < report.size(); i++)
    {
        int diff = report[i] - report[i - 1];

        // Check if absolute value of difference is between 1 & 3 (inclusive)
        if (abs(diff) < 1 || abs(diff) > 3)
            return false;

        if (diff < 0)
            increasing = false;
        if (diff > 0)
            decreasing = false;
    }
    return increasing || decreasing;
}

bool isSafeWithDampener(const vector<int> &report)
{
    if (isSafe(report)) // If it is safe then fine
        return true;

    for (int i = 0; i < report.size(); i++)
    {
        vector<int> modifiedReport = report;
        modifiedReport.erase(modifiedReport.begin() + i); // Try erasing each element and check if modified report is safe

        if (isSafe(modifiedReport))
        {
            return true;
        }
    }
    return false; // Report is unsafe altogether
}

int main()
{
    vector<vector<int>> reports; // 2D Reports vector based on file input.txt

    ifstream inputFile("input.txt");

    string reportLine;
    while (getline(inputFile, reportLine))
    {
        vector<int> reportRow;
        stringstream levelString(reportLine);
        int level;

        while (levelString >> level)
        {
            reportRow.push_back(level);
        }
        reports.push_back(reportRow);
    }
    inputFile.close();

    int safeCount = 0;
    for (auto &report : reports)
    {
        // Check if a report is safe with dampener then increase safeCount by 1
        if (isSafeWithDampener(report))
        {
            safeCount++;
        }
    }

    cout << safeCount << endl;

    return 0;
}
