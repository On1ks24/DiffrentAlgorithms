#include<iostream>
#include<chrono>
#include<string>
#include<queue>
#include <vector>
using namespace std;
#pragma warning(disable :4996)
struct Cell
{
    public: int row;
    public: int column;
    public: bool razrez;
};
vector <int> minCell(vector<vector<Cell>> matrix,int n,int m)
{
    int row=n+1;
    int column = m+1;
    vector <int> itog;
    for (int i = 0; i < n; i++)
    {
        for (int r = 0; r < m; r++)
        {
            if (matrix[i][r].row < row && !matrix[i][r].razrez)
            {
                row = matrix[i][r].row;
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        if (row < n)
        {
            if (matrix[row][i].column < column && !matrix[row][i].razrez)
            {
                column = matrix[row][i].column;
            }
        }
    }
    itog.push_back(row);
    itog.push_back(column);
    return itog;
}
void Obhod(vector<vector<Cell>>& matrix, int n, int m,int& minrow,int& mincolumn)
{
    queue<Cell> q;
    q.push(matrix[minrow][mincolumn]);
    while (q.size() != 0)
    {
        Cell current = q.front();
        matrix[current.row][current.column].razrez = true;
        q.pop();
        if (current.row - 1 >= 0 && !matrix[current.row-1][current.column].razrez)
        {
            q.push(matrix[current.row - 1][current.column]);
        }
        if (current.column-1 >= 0 && !matrix[current.row][current.column-1].razrez)
        {
            q.push(matrix[current.row][current.column-1]);
        }
        if (current.row + 1 < n && !matrix[current.row + 1][current.column].razrez)
        {
            q.push(matrix[current.row + 1][current.column]);
        }
        if (current.column+1 < m && !matrix[current.row][current.column + 1].razrez)
        {
            q.push(matrix[current.row][current.column + 1]);
        }
    }
    vector<int> gg = minCell(matrix, n, m);
    minrow = gg[0];
    mincolumn = gg[1];
}
int PoiskKuskov(vector<vector<Cell>>& matrix,int n,int m)
{
    int itog = 0;
    vector<int> gg = minCell(matrix, n, m);
    int row = gg[0];
    int column = gg[1];
    while (row <= n || column <= m)
    {
        Obhod(matrix, n, m,row,column);
        itog++;
    }
    return itog;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Cell cell;
    int k;
    int n, m; // n-количество строк m-количество столбцов
    cin >> n >> m;
    vector<vector<Cell>> matrix(n, vector<Cell>(m));
    for (int i = 0; i < n; i++)
    {
        for (int r = 0; r < m; r++)
        {
            cin >> k;
            cell.razrez = k == 1 ? true : false;
            cell.row = i;
            cell.column = r;
            matrix[i][r] = cell;
        }
    }
    auto begin = std::chrono::steady_clock::now();
    int y = PoiskKuskov(matrix, n, m);
    auto end = std::chrono::steady_clock::now();
    cout << y;
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "\nThe time: " << std::to_string(elapsed_ms.count()) << " ms\n";
}

