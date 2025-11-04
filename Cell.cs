using System;

namespace Lab3
{
    public class Cell
    {

        private bool _isMine;
        private bool _isRevealed;
        private bool _isFlagged;
        private int _adjacentMines;
        private int _x;
        private int _y;
            
        public Cell()
        {
            _x = -1;
            _y = -1;
        }

        public bool IsMine
        {
            get { return _isMine; }
            set { _isMine = value; }
        }

        public bool IsRevealed
        {
            get { return _isRevealed; }
            set { _isRevealed = value; }
        }

        public bool IsFlagged
        {
            get { return _isFlagged; }  
            set { _isFlagged = value; }
        }

        public int AdjacentMines
        {
            get { return _adjacentMines; }
            set { _adjacentMines = value; }
        }

        public int X
        {
            get { return _x; }
        }

        public int Y
        {
            get { return _y; }
        }

        public void Reset()
        {
            _isMine = false;
            _isRevealed = false;
            _isFlagged = false;
            _adjacentMines = 0;
            _x = -1;
            _y = -1;
        }

        public bool IsEmpty()
        {
            return !_isMine && !_isFlagged;
        }

        public void SetCoordinates(int newX, int newY)
        {
            _x = newX;
            _y = newY;
        }

    }
}
