using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using static Laba3.Program;
using static System.Net.Mime.MediaTypeNames;

namespace Laba3
{
    internal class Program
    {
        public class GameField
        {
            public int[][] Matrix { get; set; }
        }
        static List<int[]> FindShortestPath(int[][] matrix, int numberRows, int numberColumns, int startRow, int startColumn, int endRow, int endColumn)
        {
            MyQueue<int[]> queue = new MyQueue<int[]>();

            Cell[][] cells = new Cell[numberRows][];

            for (int i = 0; i < numberRows; i++)
            {
                cells[i] = new Cell[numberColumns];
                for (int j = 0; j < numberColumns; j++)
                {
                    cells[i][j] = new Cell
                    {
                        Row = i,
                        Column = j,
                        Marked = false,
                        Wall = matrix[i][j] == 1,
                        Start = i == startRow && j == startColumn,
                        End = i == endRow && j == endColumn
                    };
                }
            }

            queue.Enqueue(new int[] { startRow, startColumn });
            cells[startRow][startColumn].Marked = true;

            while (queue.Count > 0)
            {
                int[] currentPoint = queue.Dequeue();
                int currentRow = currentPoint[0];
                int currentColumn = currentPoint[1];

                foreach (int[] direction in directions)
                {
                    int newRow = currentRow + direction[0];
                    int newColumn = currentColumn + direction[1];

                    if (newRow >= 0 && newRow < numberRows && newColumn >= 0 && newColumn < numberColumns && !cells[newRow][newColumn].Wall && !cells[newRow][newColumn].Marked)
                    {
                        cells[newRow][newColumn].Marked = true;
                        cells[newRow][newColumn].Row = currentRow;
                        cells[newRow][newColumn].Column = currentColumn;
                        queue.Enqueue(new int[] { newRow, newColumn });

                        if (cells[newRow][newColumn].End)
                        {
                            List<int[]> path = new List<int[]>();

                            int[] current = new int[] { newRow, newColumn };

                            while (current[0] != startRow || current[1] != startColumn)
                            {
                                path.Add(current);
                                current = new int[] { cells[current[0]][current[1]].Row, cells[current[0]][current[1]].Column };
                            }
                            path.Reverse();
                            return path;
                        }
                    }
                }
            }

            return null;
        }
        static int[][] directions = { new int[] { -1, 0 }, new int[] { 1, 0 }, new int[] { 0, -1 }, new int[] { 0, 1 } };
        static void Main(string[] args)
        {
            int startRow = 0;
            int startColumn = 0;
            int endRow = 0;
            int endColumn = 0;
            int NumberColumns = 0;
            int NumberRows = 0;
            int[][] Load()
            {
                using (StreamReader reader = new StreamReader("Input.txt"))
                {
                    int i = 0;
                    int row = 0;
                    string text = reader.ReadToEnd();
                    string[] words = text.Split(new char[] { '\n' });
                    NumberRows = words.Length - 2;
                    int[][] matrix = new int[NumberRows][];

                    foreach (string word in words)
                    {
                        if (i == 0)
                        {
                            string[] words2 = word.Split(new char[] { ' ' });
                            startRow = int.Parse(words2[0]);
                            startColumn = int.Parse(words2[1]);
                        }
                        else if (i == 1)
                        {
                            string[] words2 = word.Split(new char[] { ' ' });
                            endRow = int.Parse(words2[0]);
                            endColumn = int.Parse(words2[1]);
                        }
                        else
                        {
                            string[] words2 = word.Split(new char[] { ' ' });
                            NumberColumns = words2.Length;
                            matrix[row] = new int[NumberColumns];
                            for (int j = 0; j < NumberColumns; j++)
                            {
                                matrix[row][j] = int.Parse(words2[j]);
                            }
                            row++;
                        }
                        i++;
                    }
                    return matrix;
                }
            }
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();
            List<int[]> path = FindShortestPath(Load(), NumberRows, NumberColumns, startRow, startColumn, endRow, endColumn);
            stopwatch.Stop();
            if (path == null)
            {
                using (StreamWriter writer = new StreamWriter("Output.txt", false))
                {
                    writer.WriteLine("Пути нет");
                }
            }
            else
            {
                using (StreamWriter writer = new StreamWriter("Output.txt", false))
                {
                    foreach (var point in path)
                    {
                        writer.WriteLine("({0}, {1})", point[0], point[1]);
                    }
                    writer.WriteLine($"Затраченное время: {stopwatch.ElapsedMilliseconds}мс.");
                }
            }
        }
    }
}
