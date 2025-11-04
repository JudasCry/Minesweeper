using System;

namespace Lab3
{
    public class Difficulty
    {

        private readonly string _name;
        private readonly int _width;
        private readonly int _height;
        private readonly int _mines;

        public Difficulty(string name, int width, int height, int mines)
        {

            if (width <= 0 || height <= 0)
            {
                throw new ArgumentException("Высота и ширина должна быть положительными");
            }

            if (mines <= 0 || mines >= width * height)
            {
                throw new ArgumentException("Неверное количество мин");
            }

            _name = name;
            _width = width;
            _height = height;
            _mines = mines;

        }

        public string Name
        {
            get { return _name; }
        }

        public int Width
        {
            get { return _width; }
        }

        public int Height
        {
            get { return _height; }
        }

        public int Mines
        {
            get { return _mines; }
        }
    }
}
