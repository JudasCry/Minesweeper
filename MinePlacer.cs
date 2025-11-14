using System;
using System.Collections.Generic;

namespace Lab3
{
    public class MinePlacer
    {

        private readonly Random _randomGenerator;
        
        public MinePlacer()
        {
            _randomGenerator = new Random();
        }

        public void PlaceMines(GameField field, int mines, Point safePoint)
        {

            int fieldWidth = field.Width;
            int fieldHeight = field.Height;

            int totalCells = fieldHeight * fieldWidth;

            List<Point> availablePositions = new List<Point>(totalCells);

            for (int y = 0; y < fieldHeight; y++)
            {
                for (int x = 0; x < fieldWidth; x++)
                {
                    Point currentPoint = new Point(x, y);

                    if (!(currentPoint.X == safePoint.X && currentPoint.Y == safePoint.Y))
                    {
                        availablePositions.Add(new Point(x, y));
                    }
                }
            }

            Shuffle(availablePositions); // Перемешиваем список клеток поля

            int placedMines = 0;

            for (int i = 0; i < mines; i++)
            {

                Point minePos = availablePositions[i];

                Cell cell = field.GetCell(minePos.X, minePos.Y);

                cell.IsMine = true;
                placedMines++;

            }

            field.SetTotalMines(placedMines);
        }

        public void Shuffle<T> (List<T> list) 
        {

            // Перемешиваем список //
            for (int n = list.Count - 1; n > 0; n--)
            {

                int k = _randomGenerator.Next(n + 1);

                T value = list[k];
                list[k] = list[n];
                list[n] = value;

            }

        }

    }
}
