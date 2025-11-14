using System;

namespace Lab3
{
    public class Difficulty
    {

        public string Name { get; }
        public int Width { get; }
        public int Height { get; }
        public int Mines { get; }
        
        public Difficulty(string name, int width, int height, int mines)
        {

            if (width <= 0 || height <= 0)
            {
                throw new ArgumentException("Высота и ширина должны быть положительными");
            }

            if (mines <= 0 || mines >= width * height)
            {
                throw new ArgumentException("Неверное количество мин");
            }

            Name = name;
            Width = width;
            Height = height;
            Mines = mines;

        }

    }
}
