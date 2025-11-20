using System;
using System.Collections.Generic;

namespace Lab3
{
    public class Difficulty
    {

        // Статическое поле - словарь предустановленных уровней сложности //
        private static readonly Dictionary<string, Difficulty> _presetDifficulties = new Dictionary<string, Difficulty>
        {
            { "beginner", new Difficulty("beginner", 10, 10, 10) },
            { "intermediate", new Difficulty("intermediate", 16, 16, 40) },
            { "expert", new Difficulty("expert", 30, 16, 99) },
        };

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

        // Статический метод для получения всех доступных предустановленных уровней //
        public static IEnumerable<string> GetAvailableDifficulties()
        {
            return _presetDifficulties.Keys;
        }

    }
}
