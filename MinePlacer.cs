using System;

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

            int placedMines = 0;
            int fieldWidth = field.Width;
            int fieldHeight = field.Height;

            int attempts = 0;
            int maxAttempts = fieldWidth * fieldHeight * 2;

            while (placedMines < mines && attempts < maxAttempts)
            {

                Point RandomPos = GetRandomPosition(fieldWidth, fieldHeight);

                if (CanPlaceMine(field, RandomPos, safePoint))
                {

                    Cell cell = field.GetCell(RandomPos.X, RandomPos.Y);

                    if (cell != null)
                    {
                        cell.IsMine = true;
                        placedMines++;
                    }

                }

                attempts++;
            }

            field.SetTotalMines(placedMines);
        }

        public bool CanPlaceMine(GameField field, Point point, Point safePoint)
        {

            // Проверяем не является ли это безопасной точкой //
            if (point.X == safePoint.X && point.Y == safePoint.Y)
            {
                return false;
            }

            Cell cell = field.GetCell(point.X, point.Y);

            if (cell != null && !cell.IsMine)
            {
                return true;
            }

            return false;
        }

        public Point GetRandomPosition(int maxX, int maxY)
        {
            int x = _randomGenerator.Next(0, maxX);
            int y = _randomGenerator.Next(0, maxY);

            return new Point(x, y);
        }

    }
}
