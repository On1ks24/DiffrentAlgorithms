#include <iostream>
#include <chrono>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable :4996)
using namespace std;



int main()
{   
    setlocale(LC_ALL, "Russian");
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cout << "Введите размерность первого и второго массивов через пробел\n";
    int n;
    int k;
    cin >> n >> k;
    int* n1{ new int[n]};
    int* k1{ new int[k]};
    //cout << "Введите элементы первого множества\n";
    for (int i = 0; i < n; i++) 
    {
        int p;
        cin >> p;
        n1[i] = p;
    }
    //cout << "Введите элементы второго множества\n";
    for (int i = 0; i < k; i++)
    {
        int p;
        cin >> p;
        k1[i] = p;
    }
    int* itog{new int[n+k]};
    int d = 0;
    auto begin = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) //n итераций
    {
        int e = 0;
        for (int r = 0; r < k; r++) // k итераций
        {
            if (n1[i] == k1[r])
            {
                e = 1;
            }
        }
        for (int t = 0; t < n+k; t++)// n+k итераций
        {
            if (n1[i] == itog[t])
            {
                e = 1;
            }
        }
        if (e == 0)
        {
            itog[d] = n1[i];
            d++;
        }
    }
    for (int i = 0; i < k; i++) //k итераций
    {
        int e = 0;
        for (int r = 0; r < n; r++)// n итераций
        {
            if (k1[i] == n1[r])
            {
                e = 1;
            }
        }
        for (int t = 0; t < n+k; t++)//n+k итераций
        {
            if (k1[i] == itog[t])
            {
                e = 1;
            }
        }
        if (e == 0)
        {
            itog[d] = k1[i];
            d++;
        }
    }
    // O(2(n(n+2k))) где n и k это размеры исходных массивов
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "\nThe time: "<< std::to_string(elapsed_ms.count()) << " ms\n";
    cout << "Симметрическая разность двух массивов равна:\n";
    for (int i = 0; i < d; i++)
    {
        cout << itog[i] << " ";
    }
}


