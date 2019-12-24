#include <bits/stdc++.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
long long unsigned int Calculate_Hashcode(string &Pattern) 
{
    long long unsigned int Hashcode = 0;
    int i = Pattern.length() - 1;
    int k = 0;
    while (i > -1) 
    {
        Hashcode += Pattern[i] * pow(256, k);
        k++;
        i--;
    }
    return Hashcode % (long long unsigned int)pow(2, 61);
}

int Rabin_Karp_Algorithm(string &Data, string &Pattern, int Start = 0) 
{
    long long unsigned int Hashcode_Of_Pattern = Calculate_Hashcode(Pattern);
    string Sliding_Window = "";
    int i = Start, k = 0;
    int Length = Pattern.length() + Start;
    while (i < Length) 
    {
        Sliding_Window += Data[i];
        i++;
    }
    
    long long unsigned int Hashcode_Of_Sliding_Window = Calculate_Hashcode(Sliding_Window);
    while (i < Data.length() + 1) 
    {
        if (Hashcode_Of_Pattern == Hashcode_Of_Sliding_Window) 
        {
            int j = k, l = 0;
            while (j < Sliding_Window.length()) 
            {
                if (Sliding_Window[j] != Pattern[l]) 
                {
                    break;
                }
                j++;
                l++;
            }
            if (j == Sliding_Window.length()) 
            {
                return k + Start;
            }
        } 
        else 
        {
            Hashcode_Of_Sliding_Window -= Sliding_Window[k] * pow(256, Pattern.length() - 1);
            k++;
            Hashcode_Of_Sliding_Window *= 256;
            Hashcode_Of_Sliding_Window += Data[i];
            Sliding_Window += Data[i];
        }
        i++;
    }
    return -1;
}

void Generate_Pi_Table(string &Pattern, int Pi_Table[]) 
{
    int Counter = 0;
    int j = 1;
    while (j < Pattern.length()) 
    {
        if (Pattern[j] == Pattern[Counter]) 
        {
            Counter++;
            Pi_Table[j] = Counter;
            j++;
        } 
        else 
        {
            if (Counter != 0) 
            {
                Counter = Pi_Table[Counter - 1];
            }
            else 
            {
                Pi_Table[j] = 0;
                j++;
            }
        }
    }
}

int Knuth_Morris_Algorithm(string &Data, string &Pattern, int Start = 0) 
{
    int Pi_Table[Pattern.length()] = {0};
    Generate_Pi_Table(Pattern, Pi_Table);
    int i = Start;
    int j = 0;
    while (i < Data.length()) 
    {
        if (Pattern[j] == Data[i]) 
        {
            j++;
            i++;
        }
        if (j == Pattern.length()) 
        {
            return i - j;
        } 
        else if (i < Data.length() && Pattern[j] != Data[i]) 
        {
            if (j != 0) 
            {
                j = Pi_Table[j - 1];
            } 
            else 
            {
                ++i;
            }
        }
    }
    return -1;
}

void searchFromFileRK(string __searchQuery) 
{
    ifstream inputFile;
    ofstream outputFile;
    inputFile.open("../doc/input.txt");
    outputFile.open("../doc/rabinOutput.txt");
    string input;
    int i = 0;

    cout << "\n\nSEARCHING USING RABIN KARP ALGORITHM\n\n";

    while (inputFile >> input) 
    {
        string original = input;
        transform(input.begin(), input.end(), input.begin(), ::toupper);

        while (i < input.length()) 
        {
            i = Rabin_Karp_Algorithm(input, __searchQuery, i);
            if (i != -1) 
            {
                cout << "Pattern match in " << original << " start: " << i << " end: " << i + __searchQuery.length() - 1 << '\n';
                outputFile << "Pattern match in " << original << " start: " << i << " end: " << i + __searchQuery.length() - 1 << '\n';
            } 
            else 
            {
                i = input.length();
            }
            i++;
        }
        i = 0;
    }
    outputFile.close();
}

void searchFromFileKM(string __searchQuery) 
{
    ifstream inputFile;
    ofstream outputFile;
    inputFile.open("../doc/input.txt");
    outputFile.open("../doc/kmpOutput.txt");
    string input;
    int i = 0;

    cout << "\n\nSEARCHING USING KNUTTH MORRIS ALGORITHM\n\n";

    while (inputFile >> input) 
    {
        string original = input;
        transform(input.begin(), input.end(), input.begin(), ::toupper);

        while (i < input.length()) 
        {
            i = Knuth_Morris_Algorithm(input, __searchQuery, i);
            if (i != -1) 
            {
                cout << "Pattern match in " << original << " start: " << i << " end: " << i + __searchQuery.length() - 1 << '\n';
                outputFile << "Pattern match in " << original << " start: " << i << " end: " << i + __searchQuery.length() - 1 << '\n';
            } 
            else 
            {
                i = input.length();
            }
            i++;
        }
        i = 0;
    }
    outputFile.close();
}

void testFromFile() 
{
    ifstream inputFile;
    inputFile.open("../doc/testCase.txt");
    string input;
    inputFile >> input;

    clock_t start;
    start = clock();
    searchFromFileKM(input);
    start = clock() - start;
    cout << "Time taken for searching in KNUTTH MORRIS: " << (float)start / CLOCKS_PER_SEC << " seconds\n";

    start = clock();
    searchFromFileRK(input);
    start = clock() - start;
    cout << "Time taken for searching in RABIN KARP: " << (float)start / CLOCKS_PER_SEC << " seconds\n";
}
