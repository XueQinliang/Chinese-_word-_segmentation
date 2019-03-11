#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "file.h"
#include "sentence.h"
using namespace std;
int main()
{
    file fp;
    fp.test_map_insert();
    cout<<"please choose 1. one pure sentence segmentation; 2. one article segmentation.\n";
    int num;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0a);
    cin>>num;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
    if(num==1)
    while(1){
        string look;
        cout<<"please input a string only in Chinese character:\n";
        cout<<"if you want to quit, you can input 'qt'.\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0a);
        while(look.empty())
            getline(cin,look,'\n');
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
        if(look == "qt") break;
        Sentence s(look);
        s.devide(fp,false);
        cout<<endl;
    }
    else if(num==2){
        cout<<"please input a file name:";
        string name;
        Sentence s;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0a);
        cin>>name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
        ifstream in(name);
        if (! in.is_open()){
            cout << "Error opening file";
            exit (1);
        }
        s.input(in,fp);
    }
    cout<<"END";
    return 0;
}
