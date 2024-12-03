#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main()
{
    string corruptedText, corruptedLine;
    ifstream inputFile("input.txt");
    while (getline(inputFile, corruptedLine))
    {
        corruptedText += corruptedLine;
    }
    inputFile.close();

    long int mul_sum = 0;

    regex mul_regex(R"(mul\((\d+),(\d+)\))");
    regex do_regex(R"(do\(\))");
    regex dont_regex(R"(don't\(\))");

    regex allCombined(R"(mul\(\d+,\d+\)|do\(\)|don't\(\))");

    auto matchBegin = sregex_iterator(corruptedText.begin(), corruptedText.end(), allCombined);
    auto matchEnd = sregex_iterator();

    bool Do = true;

    for (auto it = matchBegin; it != matchEnd; ++it)
    {
        smatch match = *it;
        string token = match.str();

        if (regex_match(token, do_regex))
        {
            Do = true;
        }
        else if (regex_match(token, dont_regex))
        {
            Do = false;
        }
        else if (regex_match(token, mul_regex) && Do)
        {
            smatch mulMatch;
            if (regex_match(token, mulMatch, mul_regex))
            {
                int num1 = stoi(mulMatch[1].str());
                int num2 = stoi(mulMatch[2].str());
                mul_sum += num1 * num2;
            }
        }
    }

    cout << mul_sum << endl;
    return 0;
}