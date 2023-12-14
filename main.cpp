#include <iostream>
#include<Windows.h>
#include<string>
#include "TSP.h"

using namespace std;
LARGE_INTEGER sTime,eTime, freq,pcFreq,diffTime;

struct fileIn{
    string name;
    int times;
    int optCost;
};

int main() {
    list<fileIn> fileNames;
    string name;
    fstream p1,p2;
    string ex;
    int x;
    float opt_float;
    p1.open("sa_tsp.ini",ios::in);
    if(p1.good()){
        while(!p1.eof()){
            fileIn file;
            p1>> name;
            if(p1.peek() == EOF){
                ex = name;
                break;
            }
            file.name = name;
            p1>> x;
            file.times = x;
            p1>> x;
            file.optCost = x;
            fileNames.push_back(file);
            if(!p1.peek())
                p1>> ex;
        }
    }
    else
        cout<<"blad ini";
    p2.open(ex,ios::out);
    while(!fileNames.empty()) {
        int path;
        p2<<fileNames.front().name<<" "<<fileNames.front().optCost;
        cout<<fileNames.front().name<<" ";
        p2<<endl;
        cout<<endl;
        QueryPerformanceFrequency(&freq);
        pcFreq.QuadPart = freq.QuadPart / 1000000;//microseconds
        TSP Graph;
        Graph.readFromFile(fileNames.front().name);
        //Graph.displayMatrix();
        for (int j = 0; j < fileNames.front().times; j++) {
            QueryPerformanceCounter(&sTime);
            path = Graph.sa();
            QueryPerformanceCounter(&eTime);
            diffTime.QuadPart = (eTime.QuadPart - sTime.QuadPart) / pcFreq.QuadPart;
            opt_float = fileNames.front().optCost;
            float delta = (((float)path - opt_float)/opt_float)*100;
            cout<<"weight: "<<path<<" "<< delta<<"%"<<endl;
            p2 << diffTime.QuadPart << " " <<path<<" "<< delta<<"%"<<endl;
        }
        p2 << endl;
        fileNames.pop_front();
    }
    p2.close();
    p1.close();
    return 0;
}

