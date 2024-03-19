#ifndef FILE_RECORD_H
#define FILE_RECORD_H

#include <iostream>
#include <iomanip>
#include <string.h>
//#include <cstring>
#include <vector>
#include "utilities.h"

using namespace std;

class FileRecord{
public:
    //when you construct a FileRecord, it's either empty or it
    //  contains a word
    FileRecord(){
        for(int i=0; i< MAX; i++)
        {
            _record[i][0]='\0';
        }
        recno = -1;
        size=0;
        //['\0'|  | G | a | r | b | a   |  g  |  e |    ]
    }

    FileRecord(vector<string> v)
    {
        for(int i=0; i<v.size(); i++)
        {
            size++;
            strncpy(_record[i],v[i].c_str(),MAX);
        }
       _record[v.size()][0]='\0';
    }
    FileRecord(char str[]){
        size++;
        strncpy(_record[0], str, MAX);
    }
    
    FileRecord(string s){
        size++;
        strncpy(_record[0], s.c_str(), MAX);
    }

    long write(fstream& outs);              //returns the record number
    long read(fstream& ins, long recno);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file

    vector<string> vectorstr();
    friend ostream& operator<<(ostream& outs, const FileRecord& r);

private:
    static const int MAX = 100;
    static const int ROW=100;
    int recno;
    int size;
    char _record[ROW+1][MAX+1]; //NULL char
};

#endif //FILE_RECORD_H