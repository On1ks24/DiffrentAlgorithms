#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include<chrono>
#include<queue>
#include<map>
#pragma warning(disable :4996)
using namespace std;
int getMax(vector<string>& arr) {
    int max_length = 0;
    for (const string& s : arr) {
        max_length = max(max_length, (int)s.length());
    }
    return max_length;
}
void radixSort(vector<string>& arr) {
    int maxrazr = getMax(arr);
    int y = 1;
    for (int e = maxrazr - 1; e >= 0; e--)
    {
        vector<queue<string>> bins(10);
        for (int i = 0; i < arr.size(); i++)
        {
            int digit;
            if (int(arr[i].size()) - y < 0)
            {
                digit = 0;
            }
            else
            {
                digit = arr[i][arr[i].size() - y] - '0';
            }
            bins[digit].push(arr[i]);
        }
        int idx = 0;
        for (auto& bin : bins)
        {
            while (!bin.empty())
            {
                arr[idx] = bin.front();
                bin.pop();
                idx++;
            }
        }
        y++;
    }
}
string sumThreeNumbers(const string& num1, const string& num2, const string& num3) {
    string sum;
    int n1 = num1.size();
    int n2 = num2.size();
    int n3 = num3.size();
    int maxLength = max(max(n1, n2), n3);
    int carry = 0;
    for (int i = 0; i < maxLength; i++) 
    {
        int digit1 = i < n1 ? num1[n1 - i - 1] - '0' : 0;
        int digit2 = i < n2 ? num2[n2 - i - 1] - '0' : 0;
        int digit3 = i < n3 ? num3[n3 - i - 1] - '0' : 0;
        int sumDigits = digit1 + digit2 + digit3 + carry;
        carry = sumDigits / 10;
        sum.insert(sum.begin(), sumDigits % 10 + '0');
    }
    if (carry > 0) {
        sum.insert(sum.begin(), carry + '0');
    }
    return sum;
}
vector<string> ThreeNumbers(vector<string> s)
{
    vector<string> itog;
    int n = s.size();
    int numberplus = 0;
    int numberminus = 0;
    for (string n : s)
    {
        if (n[0] == '-')
        {
            numberminus += 1;
        }
        else
        {
            numberplus += 1;
        }
    }
    if (n < 3)
    {
        cout << "Программа не может выбрать 3 числа, потому что вы ввели меньше трех чисел.";
    }
    else
    {
        if (numberminus < 2)
        {
            itog.push_back(s[n - 1]);
            itog.push_back(s[n - 2]);
            itog.push_back(s[n - 3]);
        }
        else
        {
            string s1 = s[0];
            string s2 = s[1];
            s1.erase(0, 1);
            s2.erase(0, 1);
            string var1 = sumThreeNumbers(s1, s2, s[n - 1]);
            string var2 = sumThreeNumbers(s[n - 1], s[n - 2], s[n - 3]);
            vector<string> y;
            y.push_back(var1);
            y.push_back(var2);
            radixSort(y);
            if (y[1] == var1)
            {
                itog.push_back(s[0]);
                itog.push_back(s[1]);
                itog.push_back(s[n-1]);
            }
            else
            {
                itog.push_back(s[n - 1]);
                itog.push_back(s[n - 2]);
                itog.push_back(s[n - 3]);
            }
        }
    }
    return itog;
}
int main() 
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    vector<string>array;
    vector<string>arrayplus;
    vector<string>arrayminus;
    string k;
    for (int y = 0; y < n; y++)
    {
        cin >> k;
        if (k[0] == '-')
        {
            k.erase(0, 1);
            arrayminus.push_back(k);
        }
        else
        {
            arrayplus.push_back(k);
        }
    }
    auto begin = std::chrono::steady_clock::now();
    if (int(arrayplus.size()) == 0)
    {
        radixSort(arrayminus);
        reverse(arrayminus.begin(), arrayminus.end());
        for (string i : arrayminus)
        {
            i = "-" + i;
            array.push_back(i);
        }
    }
    else if (int(arrayminus.size() == 0))
    {
        radixSort(arrayplus);
        for (string i : arrayplus)
        {
            array.push_back(i);
        }
    }
    else
    {
        radixSort(arrayminus);
        reverse(arrayminus.begin(), arrayminus.end());
        radixSort(arrayplus);
        for (string i : arrayminus)
        {
            i = "-" + i;
            array.push_back(i);
        }
        for (string i : arrayplus)
        {
            array.push_back(i);
        }
    }
    vector<string> gg = ThreeNumbers(array);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    for (string i : array)
    {
        cout << i<<" ";
    }
    cout << "\n3 Числа, произведение которых максимально:\n";
    for (string i : gg)
    {
        cout << i << " ";
    }
    std::cout << "\nThe time: " << std::to_string(elapsed_ms.count()) << " ms\n";
}
