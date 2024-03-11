#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include<chrono>
#pragma warning(disable :4996)
using namespace std;
struct Temp
{
    public: float time;
    public: float temp;
};
double getMax(vector<Temp> arr) {
    int max = arr[0].temp;
    int n = size(arr);
    for (int i = 1; i < n; i++) {
        if (arr[i].temp > max) {
            max = arr[i].temp;
        }
    }
    return max;
}
double getMin(vector<Temp> arr) {
    int min = arr[0].temp;
    int n = size(arr);
    for (int i = 1; i < n; i++) {
        if (arr[i].temp < min) {
            min = arr[i].temp;
        }
    }
    return min;
}
bool check(double max, double min, Temp temp)
{
    if ((temp.time > max) || (temp.time < min))
    {
        return true;
    }
    else
    {
        return false;
    }
}
vector<Temp> countingSort(vector<Temp>& arr) {
    int n = arr.size();
    int maxTemp = getMax(arr);
    int minTemp = getMin(arr);
    Temp temp1{};
    vector<Temp> myVector(maxTemp-minTemp+1, temp1);
    for (int i = 0; i < arr.size(); i++)
    {
        myVector[arr[i].temp - minTemp].time = arr[i].time;
        myVector[arr[i].temp-minTemp].temp += 1;
    }
    vector<Temp> output;
    for (int i = 0; i < myVector.size(); i++)
    {
        if (myVector[i].temp != 0)
        {
            for (int y = 0; y < myVector[i].temp; y++)
            {
                Temp temp;
                temp.time = myVector[i].time;
                temp.temp = i + minTemp;
                output.push_back(temp);
            }
        }
    }
    return output;
}


int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n; //Количество элементов всего
    cin >> n;
    int l;//Количество элементов которые надо вывести
    cin >> l;
    float maxdate, mindate;
    cin >> mindate;
    cin >> maxdate;
    vector<Temp> array;
    vector<Temp> arrayplus;
    vector<Temp> arrayminus;
    float k=0;
    float s=0;
    for (int y = 0; y < n; y++)
    {
        Temp t1;
        cin >> s >> k;
        t1.time = s;
        t1.temp = k;
        if (k >= 0)
        {
            t1.temp = t1.temp * 100;
            arrayplus.push_back(t1);
        }
        else
        {
            t1.temp = t1.temp * -1*100;
            arrayminus.push_back(t1);
        }
    }
    auto begin = std::chrono::steady_clock::now();
    for (auto it = arrayplus.begin(); it != arrayplus.end(); )
    {
        if (check(maxdate,mindate,*it))
        {
            it = arrayplus.erase(it);
        }
        else
        {
            it++;
        }
    }
    for (auto it = arrayminus.begin(); it != arrayminus.end(); )
    {
        if (check(maxdate, mindate, *it))
        {
            it = arrayminus.erase(it);
        }
        else
        {
            it++;
        }
    }
    if (arrayplus.size() > 0)
    {
        arrayplus=countingSort(arrayplus);
    }
    if (arrayminus.size() > 0)
    {
        arrayminus=countingSort(arrayminus);
        reverse(arrayminus.begin(), arrayminus.end());
    }
    for (Temp i : arrayminus)
    {
        i.temp = i.temp * -1;
        array.push_back(i);
    }
    for (Temp i : arrayplus)
    {
        array.push_back(i);
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    if (array.size() < l)
    {
        cout << "Количество дней, подходящих под заданные временные рамки меньше,чем N.Попробуйте поменять входные данные.";
    }
    else
    {
        for (int i = 0; i < l; i++)
        {
            cout << array[i].time << " " << array[i].temp / 100 << "\n";
        }
    }
    std::cout << "\nThe time: " << std::to_string(elapsed_ms.count()) << " ms\n";
}

