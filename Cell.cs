using System;

namespace Lab3
{
    public class Cell
    {

        public int X { get; }
        public int Y { get; }
        public bool IsMine { get; set; }
        public bool IsRevealed { get; set; }
        public bool IsFlagged { get; set; }
        public int AdjacentMines { get; set; }

        public Cell(int x, int y)
        {
            X = x;
            Y = y;
            Reset();
        }

        public void Reset()
        {
            IsMine = false;
            IsRevealed = false;
            IsFlagged = false;
            AdjacentMines = 0;
        }

        public bool IsEmpty()
        {
            return !IsMine && !IsRevealed;
        }

    }
}
