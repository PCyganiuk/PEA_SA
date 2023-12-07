//
// Created by pcyga on 06.12.2023.
//

#include "TSP.h"

TSP::TSP() {
    n = 0;
}
TSP::~TSP() = default;

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
    random_device rd;
    mt19937 g(rd());
    shuffle(sol.begin()+begin,sol.end()-end-1,g);
}

int TSP::calcCost(vector<int> &path) {
    int cost = 0;
    for (int i = 0; i < path.size(); i++) {
        cost += graph[i][path[i + 1]];
    }
    return cost;
}

int TSP::sa() {
    int shtsPath = INT_MAX;
    int cPath = 0;
    list<int> sol;
    vector<int> vertRand(graph.size());
    float iniTemp = 100.0;
    float coolRate = 0.5;
    for(int i = 1 ; i < graph.size();i++){
        vertRand[i - 1] = i;
    }
    vertRand[graph.size() - 1]=0;
    shuffleSol(0, 0, vertRand);
    cPath = calcCost(vertRand);
    sPath.resize(cPath);

    return shtsPath;
}
