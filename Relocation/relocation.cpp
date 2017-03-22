#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<bitset>
#include<stdlib.h>
using namespace std;

void parseInput()
{
    ifstream inputFile;
    ofstream outputFile;
    string binary_mask;
    string start_addr, line, temp_addr, bitmask, first_char;
    string text_record_addr, object_code;
    int temp_loc, start_loc, reloc, new_loc, text_loc;
    int loc, ob_code;
    inputFile.open("load_input.txt");
    outputFile.open("reloc_output.txt", ios::app);
    cout<<"\nEnter actual starting address : ";
    cin>>start_addr;
    stringstream ss(start_addr);
    ss>>hex>>start_loc;
    while(getline(inputFile,line))
    {
        stringstream s(line);
        getline(s, first_char, ' ');
        if(first_char == "H")
        {
            //Skip the name of program
            getline(s, temp_addr, ' ');
            getline(s, temp_addr, ' ');
            stringstream ss(temp_addr);
            ss>>hex>>temp_loc;
            //temp_loc = strtol(temp_addr.c_str(), NULL, 16);
           
            //Calculate reloc(hex)
            reloc = start_loc - temp_loc;
            continue;
        }
            
        else if(first_char == "E")
            break;

        else if(first_char == "T")
        {
            cout<<"\nText record";
            getline(s, text_record_addr, ' ');
            stringstream ss(text_record_addr);
            ss>>hex>>text_loc;
            //loc has actual location for the text record
            loc = text_loc + reloc;

            //get bitmask and convert it to binary
            getline(s, bitmask, ' ');
            int bm;
            stringstream ss2(bitmask);
            ss2>>hex>>bm;
            binary_mask = bitset<12>(bm).to_string();
            cout<<"\nbinary "<<binary_mask;

            //bit mask has 12 bits
            for(int i = 0; i < 12; i++)
            {
                //char x[10];
                //store the object code of previous instuction in temp
                string temp = object_code;
                getline(s, object_code, ' ');
                //When no more object codes to read, object code will have the prev obj code value
                if(object_code == temp)
                   break;
                stringstream ss(object_code);
                ss>>hex>>ob_code;
                //relocate it if mask is 1
                if(binary_mask[i] == '1')
                {
                    ob_code = ob_code + reloc;
                }
               
                //write to file
                outputFile<<hex<<loc<<"\t"<<hex<<ob_code<<endl;
                loc += 3;
            }
        }
    }
}

int main()
{
    parseInput();
    return 0;
}