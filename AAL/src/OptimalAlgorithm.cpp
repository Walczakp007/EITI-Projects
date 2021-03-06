#include <chrono>
#include <iostream>
#include "OptimalAlgorithm.h"
#include "QuickSorter.h"


using namespace std;

OptimalAlgorithm::OptimalAlgorithm(): array{0}, onesArray{0}, pairsArray{0}, arrayOfIndices{0}, whichSticks{0}, pairsForPrint{0} {

}

OptimalAlgorithm::~OptimalAlgorithm() {

}

void OptimalAlgorithm::showCombinations(int size) {
    /***triplets***/
    int staticCounter[102400]= { 0 };
    for (int i = 1; i <= size; i++) {
        for (int s = i + 1; s <= size; s++)
                if (array[s] > array[s - 1] && onesArray[array[s]] >= 3) {
                    for (int j = 0; j < staticCounter[array[s] - array[i]]; j += 2)
                        cout << "1.Side: " << array[s] << "\n2.Side: " << array[s] << "\n3.Side: " << array[s] <<
                             "\n4.Side: " << array[i] << "," << whichSticks[array[s] - array[i]][j + 1] << ","
                             << whichSticks[array[s] - array[i]][j + 2] << endl << endl;
                }

                for (int j = 1; j < i; j++) {
                    pairsArray[array[i] + array[j]]++;
                    if (array[i] > array[i - 1] && array[j + 1] > array[j]) {
                        staticCounter[array[i] + array[j]] += 1;
                        whichSticks[array[i] + array[j]][staticCounter[array[i] + array[j]]] = array[i];
                        staticCounter[array[i] + array[j]] += 1;
                        whichSticks[array[i] + array[j]][staticCounter[array[i] + array[j]]] = array[j];
                    } else if (array[i] > array[i - 2] && (j == i - 2)) {
                        staticCounter[array[i] * 2] += 1;
                        whichSticks[2 * array[i]][staticCounter[array[i] * 2]] = array[i];
                        staticCounter[array[i] * 2] += 1;
                        whichSticks[2 * array[i]][staticCounter[array[i] * 2]] = array[i];
                    }
                }
            }

        /***Duplicates***/
        for (int i = 1; i <= size; i++)
            if (array[i] != array[i - 1] && onesArray[array[i]] > 1) {

                int counter = 0;
                int Ds[1024] = {0};
                int j = 1;
                for (j = 1; array[i] > array[j] * 2; j++)
                    if (array[j] > array[j - 1]) {
                        if (onesArray[array[i] - array[j]] >= 2)
                            cout << "1. Side: " << array[i] << "\n2. Side: " << array[i] << "\n3. Side: " << array[j] << ","
                                 << array[i] - array[j] <<
                                 "\n4. Side: " << array[j] << "," << array[i] - array[j] << endl << endl;
                        if (onesArray[array[i] - array[j]] >= 1)
                            for (int k = 0; k < counter;)
                                cout << "1. Side: " << array[i] << "\n2. Side: " << array[i] << "\n3. Side: " << array[j]
                                     << "," << array[i] - array[j] <<
                                     "\n4. Side: " << Ds[++k] << "," << Ds[++k] << endl << endl;
                        if (onesArray[array[j]] >= 1 && onesArray[array[i] - array[j]] >= 1) {
                            Ds[++counter] = array[j];
                            Ds[++counter] = array[i] - array[j];
                        }
                    }
                if (array[i] % 2 == 0) {
                    if (onesArray[array[i] / 2] >= 4)
                        cout << "1. Side: " << array[i] << "\n2. Side: " << array[i] << "\n3. Side: " << array[i] / 2 << ","
                             << array[i] / 2 <<
                             "\n4. Side: " << array[i] / 2 << "," << array[i] / 2 << endl << endl;
                    if (onesArray[array[i]/2] >= 2)
                        for (int k = 0; k < counter;)
                            cout << "1. Side: " << array[i] << "\n2. Side: " << array[i] << "\n3. Side: " << array[i] / 2
                                 << "," << array[i] / 2 <<
                                 "\n4. Side: " << Ds[++k] << "," << Ds[++k] << endl << endl;
                }
            }

 }



int OptimalAlgorithm::calculateSimple(int *tab, int size) {
    QuickSorter quickSorter = QuickSorter();
    for(int i = 0 ; i < size ; i++)
        arrayOfIndices[i] = i;
    int n = size;
    for (int i=1;i<=n;i++) array[i] = tab[i-1], onesArray[array[i]]++;

    quickSorter.sort(array,1,n,arrayOfIndices);
    long long ans=0,D = 0,DD = 0;



    for (int i=1;i<=n;i++){
        for (int s=i+1;s<=n;s++)
            if (array[s]>array[s-1]) {
                ans += 1ll * onesArray[array[s]] * (onesArray[array[s]] - 1) * (onesArray[array[s]] - 2) / 6 *
                       pairsArray[array[s] - array[i]];
            }

        for (int j=1;j<i;j++) {
            pairsArray[array[i] + array[j]]++;

        }
    }


    for (int i=1;i<=n;i++)
        if (array[i]!=array[i-1] && onesArray[array[i]]>1)
        {
            DD=onesArray[array[i]]*(onesArray[array[i]]-1)/2;
            D=0;
            int j = 1;
            for (j=1; array[i] > array[j] * 2; j++)
                if (array[j]>array[j-1]){
                    ans+=DD*onesArray[array[j]]*(onesArray[array[j]]-1)/2*onesArray[array[i]-array[j]]*(onesArray[array[i]-array[j]]-1)/2;
                    ans+=DD*D*onesArray[array[j]]*onesArray[array[i]-array[j]];
                    D+= onesArray[array[j]]*onesArray[array[i]-array[j]];


                }
            if (array[i]%2==0){
                ans+=DD*onesArray[array[i]/2]*(onesArray[array[i]/2]-1)*(onesArray[array[i]/2]-2)*(onesArray[array[i]/2]-3)/24;
                ans+=DD*D*onesArray[array[i]/2]*(onesArray[array[i]/2]-1)/2;
            }
        }

    return ans;
}

/*
 *  Method below used only for test purposes.
 */

int OptimalAlgorithm::calculateSolution(int *tab, int size, vector <Combinations*> &sidesCombinations) {
    QuickSorter quickSorter = QuickSorter();
    for(int i = 0 ; i < size ; i++)
        arrayOfIndices[i] = i;
    int n = size;
    int staticCounter[102400]= { 0 };
    for (int i=1;i<=n;i++) array[i] = tab[i-1], onesArray[array[i]]++;

    quickSorter.sort(array,1,n,arrayOfIndices);
    long long ans=0,D = 0,DD = 0;



    for (int i=1;i<=n;i++){
        for (int s=i+1;s<=n;s++)
            if (array[s]>array[s-1]) {
                ans += 1ll * onesArray[array[s]] * (onesArray[array[s]] - 1) * (onesArray[array[s]] - 2) / 6 *
                       pairsArray[array[s] - array[i]];
                if (onesArray[array[s]] >= 3)
                    for (int k = 0; k < staticCounter[array[s] - array[i]]; k += 2)
                      sidesCombinations.push_back(new Combinations(array[s],array[s],array[s], array[i], whichSticks[array[s]-array[i]][k+1], whichSticks[array[s]-array[i]][k+2], true));
            }

        for (int j=1;j<i;j++) {
            pairsArray[array[i] + array[j]]++;
            if(array[i]>array[i-1] && array[j+1] > array[j] )
            {
                staticCounter[array[i]+array[j]] += 1;
                whichSticks[array[i]+array[j]][staticCounter[array[i]+array[j]]] = array[i];
                staticCounter[array[i]+array[j]] += 1;
                whichSticks[array[i]+array[j]][staticCounter[array[i]+array[j]]] = array[j];
            }
            else if (array[i] > array[i-2] && (j==i-2)){
                staticCounter[array[i]*2] += 1;
                whichSticks[2*array[i]][staticCounter[array[i]*2]] = array[i];
                staticCounter[array[i]*2] += 1;
                whichSticks[2*array[i]][staticCounter[array[i]*2]] = array[i];
            }
        }
    }

    cout << sidesCombinations.size() << endl;
    for (int i=1;i<=n;i++)
        if (array[i]!=array[i-1] && onesArray[array[i]]>1)
        {
            DD=onesArray[array[i]]*(onesArray[array[i]]-1)/2;
            D=0;
            int counter = 0;
            int Ds[1024] = {0};
            int j = 1;
            for (j=1; array[i] > array[j] * 2; j++)
                if (array[j]>array[j-1]){
                    ans+=DD*onesArray[array[j]]*(onesArray[array[j]]-1)/2*onesArray[array[i]-array[j]]*(onesArray[array[i]-array[j]]-1)/2;
                    if(onesArray[array[j]]>=2 && onesArray[array[i]-array[j]]>=2 && onesArray[array[i]]>=2)
                        sidesCombinations.push_back(new Combinations(array[j], array[j], array[i]-array[j], array[i]-array[j],array[i],array[i] ,false));
                    ans+=DD*D*onesArray[array[j]]*onesArray[array[i]-array[j]];
                    if(onesArray[array[i]]>=2 && onesArray[array[j]]>=1 && onesArray[array[i]-array[j]] >= 1 && D!=0)
                        for(int k = 0 ; k < counter; k+=2 )
                            sidesCombinations.push_back(new Combinations(array[j], Ds[k+1], Ds[k+2],array[i]-array[j], array[i],array[i], false));
                    if(onesArray[array[j]]>=1 && onesArray[array[i]-array[j]]>=1) {
                        Ds[++counter] = array[j];
                        Ds[++counter] = array[i] - array[j];
                    }
                    D+= onesArray[array[j]]*onesArray[array[i]-array[j]];
                }
            if (array[i]%2==0){
                ans+=DD*onesArray[array[i]/2]*(onesArray[array[i]/2]-1)*(onesArray[array[i]/2]-2)*(onesArray[array[i]/2]-3)/24;
                if(onesArray[array[i]/2]>=4 && onesArray[array[i]]>=2)
                    sidesCombinations.push_back(new Combinations(array[i]/2, array[i]/2,array[i]/2,array[i]/2, array[i],array[i], false));
                ans+=DD*D*onesArray[array[i]/2]*(onesArray[array[i]/2]-1)/2;
                if(onesArray[array[i]/2]>=2 && onesArray[array[i]]>=2 && D!=0)
                    for(int k = 0 ; k < counter; k+=2 )
                        sidesCombinations.push_back(new Combinations(array[i]/2, Ds[k+1], Ds[k+2], array[i]/2, array[i],array[i], false));
            }
        }

    return ans;


}

