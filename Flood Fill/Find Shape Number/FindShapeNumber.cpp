//
//  FindShapeNumber.cpp
//  Algorithms Practice
//
//  Created by Farzana Ahmed Siddique on 2/12/18.
//  Copyright © 2018 Farzana Ahmed Siddique. All rights reserved.
//

#include "FindShapeNumber.h"

using namespace std;

const char kSymbolWhoseShapeToFind = 'X';
const char kVisitedSymbol = 'O';
const int kInitIndex = 0;

int totalShapeNumber, T, N, M;
vector < vector <char> > symbolMatrix;
queue < vector <int> > matrixIndexQueue;

void PushElementIndexToQueue(int i, int j) {
    vector <int> temp;
    temp.push_back(i);
    temp.push_back(j);
    matrixIndexQueue.push(temp);
    temp.clear();
}

void FindNeighboursToExplore(int i, int j) {
    symbolMatrix[i][j] = kVisitedSymbol;
    if (i + 1 != N) {
        if (symbolMatrix[i + 1][j] == kSymbolWhoseShapeToFind) {
            PushElementIndexToQueue(i + 1, j);
        }
    }
    if (i - 1 >= kInitIndex) {
        if (symbolMatrix[i - 1][j] == kSymbolWhoseShapeToFind) {
            PushElementIndexToQueue(i - 1, j);
        }
    }
}

void ExploreLeftNeighbours(int i, int j, bool &hasSetIndex, int &rowIndex, int &columnIndex) {
    while (j < M) {
        if (symbolMatrix[i][j] == kSymbolWhoseShapeToFind) {
            FindNeighboursToExplore(i, j);
        }
        else {
            if (!hasSetIndex) {
                hasSetIndex = true;
                rowIndex = i;
                columnIndex = j;
            }
            break;
        }
        j++;
    }
}

void ExploreRightNeighbours(int i, int j, bool &hasSetIndex, int &rowIndex, int &columnIndex) {
    while (j >= kInitIndex) {
        if (symbolMatrix[i][j] == kSymbolWhoseShapeToFind) {
            FindNeighboursToExplore(i, j);
        }
        else {
            if (!hasSetIndex) {
                hasSetIndex = true;
                rowIndex = i;
                columnIndex = j;
            }
            break;
        }
        j--;
    }
}

void FindTotalShapeNumber(int i, int j){
    if (symbolMatrix[i][j] != kSymbolWhoseShapeToFind) {
        if (j + 1 == M) {
            if (i + 1 == N) {
                return;
            }
            FindTotalShapeNumber(i + 1, kInitIndex);
        }
        else {
            FindTotalShapeNumber(i, j + 1);
        }
        return;
    }
    bool hasSetIndex = false;
    totalShapeNumber += 1;
    PushElementIndexToQueue(i, j);
    while (!matrixIndexQueue.empty()) {
        vector <int> currIndex = matrixIndexQueue.front();
        matrixIndexQueue.pop();
        ExploreLeftNeighbours(currIndex[0], currIndex[1], hasSetIndex, i, j);
        ExploreRightNeighbours(currIndex[0], currIndex[1] - 1, hasSetIndex, i, j);
    }
    FindTotalShapeNumber(i, j);
    return;
}

void GetInput() {
    freopen("input.txt", "r", stdin);
    cin >> T;
    while (T-- > 0) {
        totalShapeNumber = 0;
        cin >> N >> M;
        symbolMatrix.resize(N);
        for (int i = 0; i < N; i++) {
            symbolMatrix[i].resize(M);
            for (int j = 0; j < M; j++) {
                cin >> symbolMatrix[i][j];
            }
        }
        FindTotalShapeNumber(kInitIndex, kInitIndex);
        cout << totalShapeNumber << endl;
        symbolMatrix.clear();
    }
}
