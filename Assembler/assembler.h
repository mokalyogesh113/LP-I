#include <iostream>
#include <fstream>
using namespace std;

class Pass1
{
    struct MOT
    {
        string opCode;
        int opNo, opLen;
    };

    struct POT
    {
        string opCode;
        int opNo;
    };

    struct Reg_T
    {
        string regName;
        int regNo;
    };

    struct Sym_T
    {
        string symName;
        int symNo, symAdd;
    };

    struct Li_T
    {
        string litName;
        string litNo;
        string litAdd;
    };

    struct Pool_T
    {
        int poolNo;
        int litNo;
    };

    int S_count, L_count, P_count;

public:
    MOT mot[11] = {{"stop", 0, 1},
                   {"add", 1, 1},
                   {"sub", 2, 1},
                   {"mult", 3, 1},
                   {"mover", 4, 1},
                   {"movem", 5, 1},
                   {"comp", 6, 1},
                   {"bc", 7, 1},
                   {"div", 8, 1},
                   {"read", 9, 1},
                   {"print", 10, 1}};

    POT pot[7] = {{"start", 1},
                  {"end", 2},
                  {"origin", 3},
                  {"equ", 4},
                  {"ltorg", 5},
                  {"dc", 6},
                  {"ds", 7}};

    Reg_T reg[4] = {{"areg,", 1},
                    {"breg,", 2},
                    {"creg,", 3},
                    {"dreg,", 4}};

    fstream fr, fw;

    Pass1();
    void printMOT();
    void printPOT();
    void printRegisterTable();
    void printSymbolTable();
    void printLiteralTable();
    void genereateIntermidiateCode();
};

Pass1::Pass1()
{
    S_count = L_count = P_count = 0;
    fr.open("input.asm", fstream::in);
    fw.open("output.dat", fstream::out);
    cout << "File Opened....." << endl;
    printMOT();
    printPOT();
    printRegisterTable();
}

void Pass1::printMOT()
{
    cout << "-------------------------------" << endl;
    cout << "Mneumonic Opcode Table..... " << endl;
    cout << "\nopno \topcode \t      length" << endl;
    for (int i = 0; i < 11; i++)
    {
        cout << " " << mot[i].opNo << "\t" << mot[i].opCode << "\t\t" << mot[i].opLen << endl;
    }
    cout << "-------------------------------" << endl;
    cout << endl;
}

void Pass1::printPOT()
{
    cout << "-----------------------------" << endl;
    cout << "Pseudo Opcode Table..... " << endl;
    cout << "\nopno \topcode " << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << " " << pot[i].opNo << "\t" << pot[i].opCode << endl;
    }
    cout << "-----------------------------" << endl;
    cout << endl;
}

void Pass1::printRegisterTable()
{
    cout << "----------------------" << endl;
    cout << "Register Table..... " << endl;
    cout << "\nregno \tregname " << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << " " << reg[i].regNo << "\t" << reg[i].regName << endl;
    }
    cout << "----------------------" << endl;
    cout << endl;
}

void Pass1::genereateIntermidiateCode()
{

    string buffer;

    while (!fr.eof())
    {
        fr >> buffer;

        // Check for Asembler Directive
        for (int i = 0; i < 7; i++)
        {
            if (buffer == pot[i].opCode)
            {
                fw << "(AD,0" << pot[i].opNo << ") ";
                if(i==1)
                {
                    fr>>buffer;
                    fw<<"(C,"<<buffer<<")"<<endl;
                }
            }
        }

        // Check for Imperative Statement

        //
    }
}