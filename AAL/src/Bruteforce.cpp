//
// Created by Paul on 2016-12-25.
//

#include "Bruteforce.h"
#include "QuickSorter.h"
#include "Combinations.h"
#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

Bruteforce::Bruteforce(): array{0}, arrOfIndices{0} {

}

void Bruteforce::calculateBruteforce(int *tab, int size) {
    QuickSorter quickSorter = QuickSorter();
    for(int i = 0 ; i < 3009 ; i++)
        arrOfIndices[i] = i;
    int n = size;
    for (int i=0;i<n;i++) array[i] = tab[i];

    quickSorter.sort(array,0,n-1,arrOfIndices);
    long long ans=0;



    vector <Combinations*> sidesCombinations;
    int tempTab[6]={0};
    for (tempTab[0] = 0; tempTab[0] < n-5; tempTab[0]++)
        for (tempTab[1] = tempTab[0]+1; tempTab[1] < n-4; tempTab[1]++)
            for (tempTab[2] = tempTab[1]+1; tempTab[2] < n-3; tempTab[2]++)
                for (tempTab[3] = tempTab[2]+1; tempTab[3] < n-2; tempTab[3]++)
                    for (tempTab[4] = tempTab[3]+1; tempTab[4] < n-1; tempTab[4]++)
                        for (tempTab[5] = tempTab[4]+1; tempTab[5] < n; tempTab[5]++)
                        {
                            int someArr[6] = {0};
                            for(int t = 0; t < 6 ; t++) someArr[t] = array[tempTab[t]];
                            int yes = 0;
                            if(someArr[5] == someArr[4] && someArr[5] == someArr[3] && someArr[5] == someArr[2] + someArr[1] + someArr[0]) yes = 1;
                            if(someArr[5] == someArr[4] && someArr[5] == someArr[3] + someArr[0] && someArr[5] == someArr[2] + someArr[1]) yes = 1;
                            if(yes) {
                                sidesCombinations.push_back(new Combinations(arrOfIndices[tempTab[0]],arrOfIndices[tempTab[1]],arrOfIndices[tempTab[2]],arrOfIndices[tempTab[3]],arrOfIndices[tempTab[4]],arrOfIndices[tempTab[5]]));
                                ans++;
                            }
                        }

    cout << "There were found " << ans << " combinations" << endl;
    if (ans != 0){
        cout << "And these are: " << endl;
        int sizeOfVec = sidesCombinations.size();
        for( int i = 0; i < sizeOfVec; i++)
            sidesCombinations.at(i)->printSides();
    }
    getchar();
}