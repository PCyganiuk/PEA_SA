//
// Created by pcyga on 06.12.2023.
//

#include "TSP.h"

TSP::TSP() {
    n = 0;
}

void TSP::readFromFile(const string& filename) {
    fstream p;
    int a;
    p.open(filename,ios::in);
    if(p.good()){
        p>>n;
        graph.clear();
        graph.resize(n,vector<int>(n,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                p>>a;
                graph[i][j]=a;
            }
        }
        p.close();
    }
    else
        cout<<"blad";
}

void TSP::displayMatrix() {
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<graph[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void TSP::shuffleSol(int begin, int end,vector<int>& sol) {

}

int TSP::sa() {
    random_device rd;
    mt19937 g(rd());
    int shtsPath = INT_MAX;
    vector<int> solRand(graph.size());
    float iniTemp = 100.0;
    float coolRate = 0.5;
    for(int i = 1 ; i < graph.size();i++){
        solRand[i - 1] = i;
    }
    solRand[graph.size() - 1]=0;
    shuffle(solRand.begin(),solRand.end()-1,g);

    return shtsPath;
}

