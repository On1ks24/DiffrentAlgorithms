#include <iostream>
#include <chrono>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string> 
#pragma warning(disable :4996)
using namespace std;


int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	setlocale(LC_ALL, "Russian");
	//cout << "Введите количество неизвестных СЛАУ\n";
	int rows; // строки
	cin >> rows;
	int cols = rows + 1;// столбцы
	double** numbers = new double* [rows];
	for (int i = 0; i < rows; i++)
	{
		numbers[i] = new double[cols];
	}
	for (int i = 0; i < rows; i++) // ввод 
		for (int j = 0; j < cols; j++)
		{
			//cout << "Введите элемент расширенной матрицы " << "[" << i << "][" << j << "]  ";
			cin >> numbers[i][j];
		}
	/* Ответ: 1 2 3 4
	double numbers[4][5]
	{
	{1, 2, 3, 4, 30}, 
	{7, 2, 5, 1, 30}, 
	{3, 8, 1, 6, 46},
	{4, 3, 7, 2, 39}
	};
	*/
	auto begin = std::chrono::steady_clock::now();
	if (cols != rows + 1)
	{
		cout << "СЛАУ имеет либо 0 решений либо бесконечно количество ";
	}
	else
	{
		for (int i = 1; i < rows; i++) // строки (rows-1 итераций)
		{
			for (int t = 0; t < i; t++)// коэффиценты ((rows-1)! итераций)
			{
				double k = -1 * numbers[i][t] / numbers[t][t];
				for (int u = 0; u < cols; u++) // cols итераций
				{
					numbers[i][u] = numbers[i][u] + numbers[t][u] * k;
				}
			}
		}
	}
	/*
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < cols; j++)
			std::cout << " " << numbers[i][j];
		std::cout << std::endl; 
	}
	*/
	
	double* x{new double[rows]};
	for (int i = rows - 1; i >= 0; i = i - 1) //rows итераций
	{
		double d = 0;
		for (int t = cols - 2; t >= i; t = t - 1) // rows! итераций
		{
			if (i == rows - 1)
			{
				x[i] = numbers[i][cols - 1] / numbers[i][t];
			}
			else
			{
				if (i != t)
				{
					d = d + numbers[i][t] * x[t];
				}
			}
		}
		x[i] = (numbers[i][cols - 1] - d) / numbers[i][i];
	}
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << "\nThe time: " << std::to_string(elapsed_ms.count()) << " ms\n";
	cout << "\nРешение введенной СЛАУ\n";
	for (int i = 0; i < rows; i++)
	{
		cout << x[i]<<"\n";
	}
	//Пусть задана СЛАУ с n неизвестными.Тогда O((n)*(n-1)!*(n+1)!+n*n!)
}
