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
using static System.Net.Mime.MediaTypeNames;

namespace Laba3
{
    internal class Program
    {
        static void Main(string[] args)
        {
            List<Cell> Cells = new List<Cell>();
            void Load()
            {
                using (StreamReader reader = new StreamReader("Input.txt"))
                {
                    int i = 0;
                    int row = 0;
                    string text = reader.ReadToEnd();
                    string[] words = text.Split(new char[] { '\n' });                        
                    foreach (string word in words)
                    {
                        if (i == 0)
                        {
                            string[] words2 = word.Split(new char[] {' '});
                            Cells.Add(new Cell
                            {
                                Row = Convert.ToInt32(words2[0]),
                                Column = Convert.ToInt32(words2[1]),
                                Marked = false,
                                Wall = false,
                                Start=true,
                                End=false
                            });
                        }
                        else if(i == 1)
                        {
                            string[] words2 = word.Split(new char[] { ' ' });
                            Cells.Add(new Cell
                            {
                                Row = Convert.ToInt32(words2[0]),
                                Column = Convert.ToInt32(words2[1]),
                                Marked = false,
                                Wall = false,
                                Start = false,
                                End = true
                            });
                        }
                        else
                        {
                            string[] words2 = word.Split(new char[] {' '});
                            for (int j = 0; j < words2.Length; j++)
                            {
                                if (words2[j].Trim() == "#")
                                {
                                    Cells.Add(new Cell { Column = j, Row = row, Marked = false, Wall = true, Start = false, End = false });
                                }
                                else
                                {
                                    if (!((j == Cells[0].Column) && (row == Cells[0].Row)) && !((j == Cells[1].Column) && (row == Cells[1].Row)))
                                    {
                                        Cells.Add(new Cell { Column = j, Row = row, Marked = false, Wall = false, Start = false, End = false });
                                    }
                                }
                            }
                            row++;
                        }
                        i++;
                    }
                }
            }

            List<Cell> GetNeighbors(Cell cell, List<Cell> cells)
            {
                List<Cell> neighbors = new List<Cell>();
                List<Cell> neighbors1 = new List<Cell>();
                neighbors1.Add(cells.FirstOrDefault(c => c.Row == cell.Row - 1 && c.Column == cell.Column));
                neighbors1.Add(cells.FirstOrDefault(c => c.Row == cell.Row + 1 && c.Column == cell.Column));
                neighbors1.Add(cells.FirstOrDefault(c => c.Row == cell.Row && c.Column == cell.Column - 1));
                neighbors1.Add(cells.FirstOrDefault(c => c.Row == cell.Row && c.Column == cell.Column + 1));
                foreach(Cell n in neighbors1)
                {
                    if(n!=null)
                    {
                        neighbors.Add(n);
                    }
                }
                return neighbors;
            }
            List<Cell> Path(List<Cell> cells)
            {
                Dictionary<Cell, Cell> parents = new Dictionary<Cell, Cell>();
                Queue<Cell> queue = new Queue<Cell>();
                cells.FirstOrDefault(c => c.Start).Marked = true;
                queue.Enqueue(cells.FirstOrDefault(c => c.Start));
                while (queue.Count > 0)
                {
                    Cell currentCell = queue.Dequeue();
                    if (currentCell == cells.FirstOrDefault(c => c.End))
                    {
                        break;
                    }
                    List<Cell> neighbors = GetNeighbors(currentCell, cells);
                    foreach (Cell neighbor in neighbors)
                    {
                        if (!neighbor.Marked && !neighbor.Wall)
                        {
                            neighbor.Marked = true;
                            queue.Enqueue(neighbor);
                            parents[neighbor] = currentCell;
                        }
                    }
                }
                if(!cells.FirstOrDefault(c => c.End).Marked)
                {
                    return null;
                }
                List<Cell> shortestPath = new List<Cell>();
                Cell cell = cells.FirstOrDefault(c => c.End);
                while (cell != null)
                {
                    shortestPath.Add(cell);
                    try
                    {
                        cell = parents[cell];
                    }
                    catch
                    {
                        cell = null;
                    }
                }
                shortestPath.Reverse();
                return shortestPath;
            }
            Load();
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();
            try
            {
                List<Cell> path = new List<Cell>(Path(Cells));
                stopwatch.Stop();
                string text = string.Empty;
                foreach (Cell cells in path)
                {
                    text += $"{cells.Row} {cells.Column}\n";
                }
                using (StreamWriter writer = new StreamWriter("Output.txt", false))
                {
                    writer.WriteLine(text);
                    writer.WriteLine($"Затраченное время: {stopwatch.ElapsedMilliseconds}мс.");
                }
            }
            catch
            {
                using (StreamWriter writer = new StreamWriter("Output.txt", false))
                {
                    writer.WriteLine("Пути нет");
                }
            }
        }
    }
}
