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
    auto mulMatchBegin = sregex_iterator(corruptedText.begin(), corruptedText.end(), mul_regex);
    auto mulMatchEnd = sregex_iterator();

    for (auto it = mulMatchBegin; it != mulMatchEnd; it++)
    {
        smatch mul_match = *it;
        mul_sum += stoi(mul_match[1]) * stoi(mul_match[2]);
    }

    cout << mul_sum << endl;
    return 0;
}