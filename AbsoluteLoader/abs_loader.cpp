#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
using namespace std;

void parseInput()
{
    ifstream inputFile;
    ofstream outputFile;
    string start_addr, line;
    inputFile.open("load_input.txt");
    outputFile.open("load_output.txt");
    while(getline(inputFile, line))
    {
        //cout<<line<<endl;
        if(line[0] == 'H')
            continue;
        else if(line[0] == 'E')
            break;
        else if(line[0] == 'T')
        {
            cout<<"\nText record";
            start_addr = line.substr(1, 6);
            cout<<"\nstart addr : "<<start_addr<<endl;
            stringstream ss(start_addr);
            //ss<<start_addr;
            int start_addr_hex;
            ss>>hex>>start_addr_hex;
            cout<<"start_addr_hex "<<hex<<start_addr_hex<<endl;
            
            for(int i = 9; i < line.size(); i = i+2)
            {
                string temp = line.substr(i,2);
                outputFile<<hex<<start_addr_hex<<"\t"<<temp<<endl;
                start_addr_hex++;
            }
            cout<<endl;
        }
    }
}

int main()
{
    parseInput();
}