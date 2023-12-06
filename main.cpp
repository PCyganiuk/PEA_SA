#include <iostream>
#include<Windows.h>
#include<string>
#include "TSP.h"

using namespace std;
LARGE_INTEGER sTime,eTime, freq,pcFreq,diffTime;
int main() {
    /*
    int ins = 9;
    string files[ins];
    fstream p1,p2;
    string ex;
    int x,times;
    vector<vector<int>> optPath;
    optPath.resize(ins);
    p1.open("sa.ini",ios::in);
    for(int i=0;i<ins;i++) {
        string name;
        p1 >> files[i];
        p1>>times;
        do {
            p1 >> x;
            optPath[i].push_back(x);
        } while (x!=0);
    }
    p1>>ex;
    p2.open(ex,ios::out);
    for(int i=0;i<ins;i++) {
        int path;
        p2<<files[i]<<" ";
        cout<<files[i]<<" ";
        for(int k : optPath[i]){
            p2<<k<<" ";
            cout<<k<<" ";
        }
        p2<<endl;
        cout<<endl;
        QueryPerformanceFrequency(&freq);
        pcFreq.QuadPart = freq.QuadPart / 1000000;//microseconds
        TSP Graph;
        Graph.readFromFile(files[i]);
        Graph.displayMatrix();
        for (int j = 0; j < times; j++) {
            QueryPerformanceCounter(&sTime);
            //path = Graph.heldKarp();
            QueryPerformanceCounter(&eTime);
            diffTime.QuadPart = (eTime.QuadPart - sTime.QuadPart) / pcFreq.QuadPart;
            p2 << diffTime.QuadPart << endl;
            cout << "Optimal Tour Path: ";
            while (!Graph.path.empty()) {
                cout << Graph.path.top() << " ";
                Graph.path.pop();
            }
            cout<<"weight: "<<path<<endl;
        }
    }
    p2.close();
    p1.close();
    */
    TSP Graph;
    Graph.readFromFile("tsp_10.txt");
    Graph.displayMatrix();
    int optPath = 212;
    int vert[10] = {3, 4, 2, 8, 7, 6, 9, 1, 5, 0};
    int path = Graph.sa();
    return 0;
}

