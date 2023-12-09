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

int TSP::calcCost(vector<int> path) {
    int cost = 0;
    cost+=graph[0][path[0]];
    for (int i = 0; i < path.size()-1; i++) {
        cost += graph[path[i]][path[i+1]];
    }
    return cost;
}

int TSP::sa() {
    random_device rd;
    mt19937 g(rd());
    uniform_real_distribution<double> num(0.0,1.0);
    uniform_int_distribution<int> node(1,n-1);
    int L = n * n;
    int bestCost = INT_MAX;
    int cCost;
    list<int> sol;
    vector<int> vertRand(graph.size());
    double temp = 200.0;
    for(int i = 1 ; i < graph.size();i++){
        vertRand[i - 1] = i;
    }
    vertRand[graph.size() - 1]=0;
    shuffleSol(0, 0, vertRand);
    cCost = calcCost(vertRand);
    sPath.assign(vertRand.begin(),vertRand.end());
    bestCost = cCost;
    int war = 0;
    int oldCurCost = -1;

    while(war < 9){
        for(int t = 0; t < L; t++){

            vector<int> sasiad(vertRand);
            int a = node(rd);
            int b = node(rd);
            while(a == b)
                a = node(rd);
            iter_swap(sasiad.begin() + a, sasiad.begin() + b);
            int sasiad_cost = calcCost(sasiad);
            if(sasiad_cost <= bestCost){
                bestCost = sasiad_cost;
                sPath = sasiad;
            }
            if(sasiad_cost <= cCost){
                cCost = sasiad_cost;
                vertRand = sasiad;
            }
            else{
                if(exp(((double (cCost - sasiad_cost))/temp)) > num(g)){
                    cCost = sasiad_cost;
                    vertRand = sasiad;
                }
            }
        }
        if(oldCurCost != -1){
            if(oldCurCost == cCost)
                war++;
            else
                war = 0;
        }
        oldCurCost = cCost;
        temp = 0.98 * temp;
    }

    return bestCost;
}
