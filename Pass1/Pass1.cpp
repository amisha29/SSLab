#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<map>
#include<sstream>
using namespace std;

map<string,string> optab_map;
map<string,string> label_map;


void readOptab()
{
    ifstream optab;
    optab.open("optab.txt");
    string opcode, value;
    while(!optab.eof() )
    {
        optab>>opcode>>value;
        optab_map[opcode] = value;
    }
    optab.close();
}

void parseInput()
{
    ifstream inputFile;
    ofstream outputFile;
    inputFile.open("input.txt");
    outputFile.open("out.txt");
    string operand, label, opcode, line; 
    int locctr = 0, lineno = 0;
    while(getline(inputFile, line))
    {
        stringstream s(line);
        getline(s, label, '\t');
        getline(s, opcode, '\t');
        getline(s, operand, '\n');
        lineno++;
        if(line[0] == '.')
        {
            outputFile<<line<<endl;
            continue;
        }   
        if(opcode == "START")
        {
            stringstream s(operand);
			s>>hex>>locctr;
            outputFile<<hex<<locctr<<"\t"<<line<<endl;
            continue;   
        }
        else if(opcode == "END")
        {
            //cout<<"hurra"<<endl;
        }
        //check whether opcode is present in optab
     /*   else if (optab_map.find(opcode) == optab_map.end())
        {
            cout<<"error: opcode not valid at line "<<lineno<<endl;
        }*/

        // Writes line to output file with location
		outputFile <<hex<<locctr<<"\t"<< line<< endl;

        //check whether label is present
        if(label.size() != 0)
        {
            if(label_map.find(label) == label_map.end())
            {
                //not found, so insert
                stringstream s;
                s<<hex<<locctr;
                label_map[label] = s.str();
            }
            else
            {
                //cout<<"found\n";
                cout<<"\nError : Duplicate symbol at line "<<lineno<<endl;
                break;
            }
        }

        //If opcode present in optab, it's valid opcode'
        map<string,string>::iterator iter;
        if((iter = optab_map.find(opcode)) != optab_map.end())
        {
            //check whether variable is defined for BYTE,WORD,RESW,RESB opcodes
            if(iter->second == "*" && label.size() == 0)
            {
                cout<<"\nError: no variable specified at line "<<lineno<<endl;
                break;
            }
            else if(opcode == "WORD")
                locctr += 3;
            else if(opcode == "RESW")
            {
                stringstream s(operand);
				int no;
				s>>no;
                locctr += 3*no;
            }
            else if(opcode == "RESB")
            {
                stringstream s(operand);
				int n;
				s>>n;
                locctr += n;
            }  
            else if(opcode == "BYTE")
            {
                if(operand[0] == 'C')
                {   
                    //Subtract 3 for {C,','}
                    locctr += (operand.size()-3);
                }
                else if(operand[0] == 'X')
                {
                    int digits = operand.size()-3;
                    locctr += (digits%2 == 0 ? digits/2 : (digits+1)/2);
                }
                else
                {
                    cout<<"\nerror frtt";
                    break;
                }  
            }      
            else
                locctr += 3;
            //cout<<"locc "<<locctr<<endl;
        }
    }
    inputFile.close();
    outputFile.close();
}

void writeSymtab()
{
    ofstream symtab;
    symtab.open("symtab.txt", ios::app);
    //write to symtab
    map<string,string>::iterator iter;
    for(iter = label_map.begin(); iter != label_map.end(); iter++)
        symtab<<iter->first<<"\t"<<iter->second<<endl;
    symtab.close();
}

int main()
{
   readOptab();
   parseInput();
   writeSymtab();
   return 0;
}

