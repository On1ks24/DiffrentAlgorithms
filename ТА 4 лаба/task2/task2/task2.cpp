#include <list>
#include <iostream>
#pragma warning(disable :4996)
#include <chrono>
#include <string>
using namespace std;

struct point
{
public: double x;
public: double y;
};
bool check(point _point, point centr, double radius)
{
    double equation = (_point.x - centr.x) * (_point.x - centr.x) + (_point.y - centr.y) * (_point.y - centr.y);
    if (equation <= radius*radius)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    setlocale(LC_ALL, "Russian");
    point centr;
    double radius;
    cin >> radius;
    cin >> centr.x >> centr.y;
    list<point> points;
    int k;
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        double a, b;
        cin >> a >> b;
        point point1;
        point1.x = a;
        point1.y = b;
        points.push_back(point1);
    }
    auto begin = std::chrono::steady_clock::now();
    /*
    while (it != points.end()) {
        if (!check(*it, centr, radius)) {
            it = points.erase(it);
        }
        else {
            it++;
        }
    }
    */
    for (auto it = points.begin(); it != points.end(); ) 
    {
        if (!check(*it, centr, radius)) 
        {
            it = points.erase(it);
        }
        else 
        {
            it++;
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    for (auto p : points) 
    {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }
    std::cout << "\nThe time: " << std::to_string(elapsed_ms.count()) << " ms\n";
}
