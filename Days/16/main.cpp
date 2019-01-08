// aoc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//
//  main.cpp
//  aoc1
//
//  Created by Gabriel on 01/12/2018.
//  Copyright � 2018 Gabriel. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <regex>
#include <set>
#include <algorithm>
#include <queue>
#include <deque>
#include <stack>
#include <numeric>
#include <list>
#include <tgmath.h>
#include <assert.h>

using namespace std;

struct Point
{
    int x{ 0 }, y{ 0 };
    
    Point() {}
    
    Point(int x, int y) { this->x = x; this->y = y; }
    
    Point(const Point & p) { x = p.x; y = p.y; }
    
    Point & operator =(const Point & p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }
    
    bool operator ==(const Point & other) const
    {
        return x == other.x && y == other.y;
    }
    
    bool operator !=(const Point & other) const
    {
        return !operator==(other);
    }
    
    bool operator < (const Point & other) const
    {
        if (y < other.y) return true;
        if (y == other.y && x < other.x)
            return true;
        return false;
    }
    
    int ManhattanDist(const Point & p) const
    {
        return abs(x - p.x) + abs(y - p.y);
    }
    
    
    bool IsInGrid(int width, int height) const
    {
        return x >= 0 && y >= 0 && x < width && y < height;
    }
};

enum class InstructionType
{
    addr = 10,
    addi = 6,
    mulr = 9,
    muli = 0,
    banr = 14,
    bani = 2,
    borr = 11,
    bori = 12,
    setr = 15,
    seti = 1,
    gtir = 7,
    gtri = 3,
    gtrr = 4,
    eqir = 8,
    eqri = 13,
    eqrr = 5
};

void ExecuteInstruction(vector<int> & registers, int regA, int regB, int regC,
                       InstructionType instr)
{
    if (instr == InstructionType::addr)
    {
        registers[regC] = registers[regA] + registers[regB];
    }
    else if (instr == InstructionType::addi)
    {
        registers[regC] = registers[regA] + regB;
    }
    else if (instr == InstructionType::mulr)
    {
        registers[regC] = registers[regA] * registers[regB];
    }
    else if (instr == InstructionType::muli)
    {
        registers[regC] = registers[regA] * regB;
    }
    else if (instr == InstructionType::banr)
    {
        registers[regC] = registers[regA] & registers[regB];
    }
    else if (instr == InstructionType::bani)
    {
        registers[regC] = registers[regA] & regB;
    }
    else if (instr == InstructionType::borr)
    {
        registers[regC] = registers[regA] | registers[regB];
    }
    else if (instr == InstructionType::bori)
    {
        registers[regC] = registers[regA] | regB;
    }
    else if (instr == InstructionType::setr)
    {
        registers[regC] = registers[regA];
    }
    else if (instr == InstructionType::seti)
    {
        registers[regC] = regA;
    }
    else if (instr == InstructionType::gtir)
    {
        registers[regC] = regA > registers[regB] ? 1 : 0;
    }
    else if (instr == InstructionType::gtri)
    {
        registers[regC] = registers[regA] > regB ? 1 : 0;
    }
    else if (instr == InstructionType::gtrr)
    {
        registers[regC] = registers[regA] > registers[regB] ? 1 : 0;
    }
    else if (instr == InstructionType::eqir)
    {
        registers[regC] = regA == registers[regB] ? 1 : 0;
    }
    else if (instr == InstructionType::eqri)
    {
        registers[regC] = registers[regA] == regB ? 1 : 0;
    }
    else if (instr == InstructionType::eqrr)
    {
        registers[regC] = registers[regA] == registers[regB] ? 1 : 0;
    }
    else
        assert(!"Unsupported");
}

struct Instruction
{
    string opcode;
    int registerA;
    int registerB;
    int registerC;
    
    vector<int> registers;
};

vector<string> regexMatch(string s, string regex)
{
    std::regex re2(regex);
    std::smatch match2;
    std::regex_search(s, match2, re2);
    vector<string> ret;
    for (int i = 1; i <= match2.size(); ++i)
        ret.push_back(match2.str(i));
    return ret;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream f;
    f.open("day16r2.txt");
    
    string line;
    
    vector<int> registers = { 0, 0, 0, 0};
    int crtLine = 1;
    
    int opcode = 0, regA = 0, regB = 0, regC = 0;
    
    int count = 0;
    
    map<InstructionType, int> mapping;
    map<InstructionType, set<int>> reverseCandidates;
    
    
    while (getline(f, line))
    {
        vector<string> instructionStr =
        regexMatch(line, R"((\d+) (\d+) (\d+) (\d+))");
        opcode = stoi(instructionStr[0]);
        regA = stoi(instructionStr[1]);
        regB = stoi(instructionStr[2]);
        regC = stoi(instructionStr[3]);
        ExecuteInstruction(registers, regA, regB, regC, (InstructionType)opcode);
    }
    
    cout << "count : " << count << endl;
    
    return 0;
}
