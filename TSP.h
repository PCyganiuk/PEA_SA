//
// Created by pcyga on 06.12.2023.
//

#ifndef PEA_SA_TSP_H
#define PEA_SA_TSP_H


#include<vector>
#include<iostream>
#include<list>
#include<stack>
#include<string>
#include<fstream>
#include<bitset>
#include<climits>
#include<algorithm>
#include<random>

using namespace std;

class TSP {
private:
    int n;
    vector<vector<int>> graph;
public:
    stack<int>path;
    TSP();
    void readFromFile(const string& filename);
    int sa();
    void shuffleSol(int begin,int end, vector<int>& tab);
    void displayMatrix();
};


#endif //PEA_SA_TSP_H
