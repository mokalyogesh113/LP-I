#include <iostream>
#include<bits/stdc++.h>
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
        int litNo;
        int litAdd;
    };

    struct Pool_T
    {
        int poolNo;
        int litNo;
    };

    int S_count, L_count, P_count, LC = 0;

public:
    MOT mot[11] = {
        {"stop", 0, 1},
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

    POT pot[7] = {
        {"start", 1},
        {"end", 2},
        {"origin", 3},
        {"equ", 4},
        {"ltorg", 5},
        {"dc", 6},
        {"ds", 7}};

    Reg_T reg[4] = {
        {"areg,", 1},
        {"breg,", 2},
        {"creg,", 3},
        {"dreg,", 4}};

    Li_T litTab[10];
    Sym_T SymTab[10];
    Pool_T pTab[10];

    fstream fr, fw;

    Pass1();
    ~Pass1();
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
    genereateIntermidiateCode();
    printLiteralTable();
    printSymbolTable();
}

Pass1::~Pass1()
{
    fr.close();
    fw.close();
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

void Pass1::printLiteralTable()
{
    cout << "-------------------------------" << endl;
    cout << "Literal Table..... " << endl;
    cout << "\nlitno \tlitname \taddress" << endl;
    for (int i = 0; i < L_count; i++)
    {
        cout << " " << litTab[i].litNo << "\t" << litTab[i].litName << "\t\t" << litTab[i].litAdd << endl;
    }

    cout << "-------------------------------" << endl;
    cout << endl;
    
}

void Pass1::printSymbolTable()
{
    cout << "-------------------------------" << endl;
    cout << "Symbol Table..... " << endl;
    cout << "\nsymno \tsymname \taddress" << endl;
    for (int i = 0; i < S_count; i++)
    {
        cout << " " << SymTab[i].symNo << "\t" << SymTab[i].symName << "\t\t" << SymTab[i].symAdd << endl;
    }

    cout << "-------------------------------" << endl;
    cout << endl;
}

void Pass1::genereateIntermidiateCode()
{
    string buffer;
    fw << "    ";
    while (!fr.eof())
    {
        bool isAD = false;
        bool isIS = false;
        fr >> buffer;

        // Check for Asembler Directive
        for (int i = 0; i < 7; i++)
        {
            if (buffer == pot[i].opCode)
            {
                fw << "(AD,0" << pot[i].opNo << ") ";
                if (i == 0)
                {
                    fr >> buffer;
                    fw << "(C," << buffer << ")";
                    LC = stoi(buffer);
                }
                // if(i==1)
                // {
                //     goto jump_exit;
                // }

                isAD = true;
            }
        }

        // Check for Imperative Statement
        if (!isAD)
        {
            for (int i = 0; i < 11; i++)
            {
                if (buffer == mot[i].opCode)
                {
                    fw << "(IS,0" << mot[i].opNo << ") ";

                    // Check Register
                    fr >> buffer;
                    for (int j = 0; j < 4; j++)
                    {
                        if (buffer == reg[j].regName)
                        {
                            fw << reg[j].regNo << " ";
                            break;
                        }
                    }

                    // check symbol or literal or constant and add it to SymTab or litTab

                    fr >> buffer;
                    if (buffer[0] == '=') // Literal
                    {
                        buffer = buffer.substr(2, buffer.length() - 3);
                        // Check if literal is already in the litTab
                        bool flag = false;
                        for (int j = 0; j < L_count; j++)
                        {
                            if (buffer == litTab[j].litName)
                            {
                                fw << "(L,0" << litTab[j].litNo << ") ";
                                flag = true;
                                break;
                            }
                        }

                        if (!flag)
                        {
                            litTab[L_count].litName = buffer;
                            litTab[L_count].litNo = L_count + 1;
                            fw << "(L,0" << litTab[L_count].litNo << ") ";

                            L_count++;
                        }
                    }
                    else if (buffer[0] == '\'') // Constant
                    {
                        buffer = buffer.substr(1, buffer.length() - 2);
                        cout << "(C," << buffer;
                    }
                    else // Symbol
                    {
                        bool flag = false;
                        for (int j = 0; j < S_count; j++)
                        {
                            if (buffer == SymTab[j].symName)
                            {
                                fw << "(S,0" << SymTab[j].symNo << ") ";
                                flag = true;
                                break;
                            }
                        }

                        if (!flag)
                        {
                            SymTab[S_count].symName = buffer;
                            SymTab[S_count].symNo = S_count + 1;
                            fw << "(S,0" << SymTab[S_count].symNo << ") ";

                            S_count++;
                        }
                    }

                    isIS = true;
                }
            } // Is
        }

        if (!isAD && !isIS)
        {
            // check for DL Statements
            bool flag = false;
            for (int i = 0; i < S_count; i++)
            {
                if (SymTab[i].symName == buffer)
                {
                    fw << "(S,0" << SymTab[i].symNo << ") ";
                    SymTab[i].symAdd = LC-1;
                    flag = true;
                    break;
                }
            }

            if (!flag)
            {
                SymTab[S_count].symName = buffer;
                SymTab[S_count].symNo = S_count + 1;
                fw << "(S,0" << SymTab[S_count].symNo << ") ";
                SymTab[S_count].symAdd = LC-1;

                S_count++;
            }

            string symbol = buffer;
            fr >> buffer;
            if (buffer == "ds")
            {
                fw << "(DL,01) ";
                fr >> buffer;
                fw << "(C," << buffer << ")";
                LC += (stoi(buffer) - 1);
            }
            else if (buffer == "dc")
            {
                fw << "(DL,02) ";
                fr >> buffer;
                fw << "(C," << buffer << ")";
            }
        }

        if (buffer == "end")
        {
            break;
        }
        fw << endl;
        fw << LC << " ";
        LC++;
    }
    for(int i=0;i<L_count;i++)
    {
        litTab[i].litAdd = LC;
        LC++;
    }
} // genereateIntermidiateCode()


int main()
{
    Pass1 p1;
    return 0;
}
