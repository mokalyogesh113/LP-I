#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class pass_I
{   
    struct MNT
    {
        int MNTC;
        string macroName;
        int MDTC;
    };
    
    struct MDT
    {
        int MDTC;
        string statement;
    };
    
    MNT mnt[3];
    MDT mdt[20];
    int mnt_c = 0 , mdt_c = 0;
    
       
  public:
    void printMNT();
    void printMDT();
    
    void generatePassIOutput();
};

void pass_I::generatePassIOutput()
{
    fstream fr , fw;
    fr.open("input.asm" , fstream::in);
    fw.open("output.asm" , fstream::out);
    
    string buffer;
    bool isMacroDefinition = false;
    while(!fr.eof())
    {
        fr>>buffer;
        // cout<<buffer<<endl;
        if(!isMacroDefinition)
        {
            if(buffer == "macro")
            {
                isMacroDefinition = 1;
                fr>>buffer;
                // cout<<buffer<<endl;
                mnt[mnt_c].MNTC = mnt_c;
                mnt[mnt_c].macroName = buffer;
                mnt[mnt_c].MDTC = mdt_c;
                mnt_c++;
                
            }
            else if(buffer == "start")
            {
                fw<<buffer<<" ";
                fr>>buffer;
                // cout<<buffer<<endl;
                fw<<buffer<<"\n";
            }
            else if(buffer == "end")
            {
                fw<<buffer<<endl;
                break;
            }
            else
            {
                bool isMacroName = false;
                for(int i=0;i<mnt_c;i++)
                {
                    if(buffer==mnt[i].macroName)
                    {
                        fw<<buffer<<endl;
                        isMacroName = true;
                    }
                }
                
                if(!isMacroName)
                {
                    fw<<buffer<<" ";
                    fr>>buffer;
                    // cout<<buffer<<endl;
                    fw<<buffer<<" ";
                    fr>>buffer;
                    // cout<<buffer<<endl;
                    fw<<buffer<<"\n";
                }
                
            }
        }
        
        //Macro Definition
        else
        {
            
            if(buffer=="mend")
            {
                isMacroDefinition = 0;
                mdt[mdt_c].MDTC = mdt_c;
                mdt[mdt_c].statement = buffer;
                mdt_c++;
            }
            else    
            {
                string stmt = buffer;
                stmt+=" ";
                fr>>buffer;
                stmt+=buffer;
                stmt+=" ";
                fr>>buffer;
                stmt+=buffer;
                
                mdt[mdt_c].MDTC = mdt_c;
                mdt[mdt_c].statement = stmt;
                mdt_c++;
            }
            
        }
    }
    
    fr.close();
    fw.close();
}

void pass_I::printMNT()
{
    cout<<endl;
    cout<<"Macro Name Table:- \n";
    cout<<"-------------------------------------------"<<endl;
    cout<<"MNTC \tMacro Name \tMDTC \n";
    for(int i=0;i<mnt_c;i++)
    {
        cout<<mnt[i].MNTC<<"\t"<<mnt[i].macroName<<"\t"<<mnt[i].MDTC<<endl;
    }
}

void pass_I::printMDT()
{
    cout<<endl;
    cout<<"Macro Definition Table:- \n";
    cout<<"-------------------------------------------"<<endl;
    cout<<"MDTC \tMacro Definition  \n";
    for(int i=0;i<mdt_c;i++)
    {
        cout<<mdt[i].MDTC<<"\t"<<mdt[i].statement<<endl;
    }
}


int main()
{
    pass_I obj;
    obj.generatePassIOutput();
    obj.printMNT();
    obj.printMDT();
}