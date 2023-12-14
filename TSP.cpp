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
    uniform_int_distribution<int> node(0,n-2);
    int L = (n * n)/2; // długość epoki
    int bestCost = INT_MAX;
    float alfa = 0.98;
    int stop_war = 100;
    int cCost;
    vector<int> vertRand(graph.size());
    double temp = calcInitTemp(); // temperatura
    for(int i = 1 ; i < graph.size();i++){
        vertRand[i - 1] = i;
    }
    vertRand[graph.size() - 1]=0;
    shuffleSol(0, 0, vertRand);
    cCost = calcCost(vertRand);
    sPath.assign(vertRand.begin(),vertRand.end());
    bestCost = cCost;
    int war = 0;
    //int k = 0;
    int oldCurCost = -1;

    while(war < stop_war){ // warunek końcowy
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
        //k++;
        temp = alfa * temp; // chłodzenie pierwsze
        //temp = (temp / (1 + log10(k))); //liniowe
    }

    return bestCost;
}

double TSP::calcInitTemp() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> d(0, n-2);

    vector<int> path(n);
    for(int i = 1 ; i < n;i++){
        path[i - 1] = i;
    }
    path[n - 1]=0;

    int delta = 0;
    int N = 10000;
    for(int i = 0;i < N;i++){
        shuffle(path.begin()+1 ,path.end()-1, g);
        int cost = calcCost(path);
        int a = d(rd); int b = d(rd);
        while (a == b)
            a = d(rd);
        iter_swap(path.begin() + a, path.begin() + b);
        int cost2 = calcCost(path);
        delta += abs(cost - cost2);
    }
    delta /= N;
    double temp =  -( (double) delta / (double) log(0.95) ); //0.95
    return temp;
}
