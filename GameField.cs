using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab3
{
    public class GameField
    {

        private Cell[,] _grid;
        private int _cellsRevealed;
        private int _flagsPlaced;

        public int Width { get; }
        public int Height { get; }
        public int TotalMines { get; set; }

        public IEnumerable<Cell> AllCells
        {
            get
            {
                return Enumerable.Range(0, Height)
                        .SelectMany(y => Enumerable.Range(0, Width)
                            .Select(x => _grid[y, x]));
            }
        }

        public GameField(Difficulty difficulty, MinePlacer minePlacer)
        {

            Width = difficulty.Width;
            Width = difficulty.Height;

            _grid = new Cell[Height, Width]; // Создаём двумерный массив

            for (int y = 0; y < Height; y++)
            {
                for (int x = 0; x < Width; x++)
                {
                    _grid[y, x] = new Cell(x, y); // Создаём клетку
                }

            }

        }

        public bool RevealCell(Point p)
        {

            if (p.X < 0 || p.X >= Width || p.Y < 0 || p.Y >= Height)
            {
                return false;
            }

            Cell cell = GetCell(p.X, p.Y);

            if (cell == null || cell.IsRevealed || cell.IsFlagged)
            {
                return false;
            }

            cell.IsRevealed = true;
            _cellsRevealed++;

            if (cell.IsMine)
            {
                return false;
            }
            else
            {
                if (cell.AdjacentMines == 0)
                {

                    // Рекурсивно открываем соседние клетки //
                    List<Cell> neighbours = GetNeighbours(p);

                    foreach (Cell neighbour in neighbours)
                    {
                        if (neighbour != null && !neighbour.IsRevealed && !neighbour.IsFlagged)
                        {
                            RevealCell(new Point(neighbour.X, neighbour.Y));
                        }
                    }

                    return true;
                }
            }

            return true;

        }

        public List<Cell> GetNeighbours(Point p)
        {

            List<Cell> neighbours = new List<Cell>();

            int x = p.X;
            int y = p.Y;

            // Перебираем все 8 возможных соседей //
            for (int dy = -1; dy <= 1; ++dy)
            {
                for (int dx = -1; dx <= 1; ++dx)
                {

                    if (dx == 0 && dy == 0) continue; // Пропускаем саму клетку

                    int nx = x + dx;
                    int ny = y + dy;

                    Cell neighbourCell = GetCell(nx, ny);

                    if (neighbourCell != null)
                    {
                        neighbours.Add(neighbourCell);
                    }

                }
            }

            return neighbours;

        }

        public void CountAdjacentMines()
        {

            foreach (var cell in AllCells)
            {

                if (cell.IsMine) continue;

                int mineCount = 0;

                var neighbours = GetNeighbours(new Point(cell.X,cell.Y));

                foreach (var neighbour in neighbours)
                {
                    if (neighbour.IsMine)
                    {
                        mineCount++;
                    }
                }
                cell.AdjacentMines = mineCount;
            }
        }

        public bool ToggleFlag(Point p)
        {

            if (p.X < 0 || p.X >= Width || p.Y < 0 || p.Y >= Height)
            {
                return false;
            }

            Cell cell = GetCell(p.X, p.Y);

            if (cell == null || cell.IsRevealed)
            {
                return false;
            }

            if (cell.IsFlagged)
            {
                cell.IsFlagged = false;
                _flagsPlaced--;
            }
            else
            {
                cell.IsFlagged = true;
                _flagsPlaced++;
            }

            return true;

        }

        public Cell GetCell(int x, int y)
        {
            
            if (x < 0 || x >= Width || y < 0 || y >= Height)
            {
                return null;
            }

            return _grid[y, x];

        }

        public bool CheckWin()
        {
            return _cellsRevealed == (Width * Height - TotalMines);
        }

        public void RevealAllMines()
        {

            foreach (var cell in AllCells)
            {
                if (cell.IsMine)
                {
                    cell.IsRevealed = true;
                }
            }

        }

        public void SetTotalMines(int totalMines)
        {
            TotalMines = totalMines;
        }

        public void ResetField()
        {

            foreach (var cell in AllCells) 
            {
                cell.Reset();
            }

            _cellsRevealed = 0;
            _flagsPlaced = 0;

        }

    }
}
