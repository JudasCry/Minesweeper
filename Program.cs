using System;

namespace Lab3
{
    public class Program
    {
        static void Main(string[] args)
        {

            Console.WriteLine("\n=== ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ ===");

            Difficulty beginner = new Difficulty("beginner", 10, 10, 10);
            Console.WriteLine("Создан уровень: " + beginner.Name + " " + beginner.Width + 
                              " x " + beginner.Height + " c " + beginner.Mines + " минами");

            Settings defaultSettings = Settings.Instance;
            Console.WriteLine("Настройки: язык " + defaultSettings.Language + " звук " + 
                             (defaultSettings.SoundEnabled ? "вкл" : "выкл") + 
                             " тема " + defaultSettings.Theme);

            Statistics gameStatistics = new Statistics(0, 0, 0, 0, 0);
            Console.WriteLine("Статистика: игр " + gameStatistics.TotalGames + " побед " + gameStatistics.Wins);

            Game game = new Game(beginner, defaultSettings, gameStatistics);
            Console.WriteLine("Игра создана успешно!");

            Console.WriteLine("\n=== ДЕМОНСТРАЦИЯ ТАЙМЕРА ===");

            game.Timer.TimeUpdated += (time) => Console.WriteLine($"Таймер:{ time }");

            game.Timer.Start();
            Console.WriteLine("Таймер запущен: " + game.Timer.IsRunning);

            Console.WriteLine("\n=== ДЕМОНСТРАЦИЯ ИГРОВОГО ПРОЦЕССА ===");

            game.StartGame(new Point(0, 0));
            Console.WriteLine("Игра начата в позиции (0, 0)");

            game.Field.RevealCell(new Point(1, 1));
            Console.WriteLine("Открыта клетка (1, 1)");

            game.Field.RevealCell(new Point(5, 5));
            Console.WriteLine("Открыта клетка (5, 5)");

            Console.WriteLine("\n=== ДЕМОНСТРАЦИЯ СМЕНЫ СЛОЖНОСТИ ===");

            Difficulty intermediate = new Difficulty("intermediate", 16, 16, 40);
            Console.WriteLine("Сложность изменена на: " + intermediate.Name);
            game.SetCurrentDifficulty(intermediate);

            Console.WriteLine("\n=== ДЕМОНСТРАЦИЯ НАСТРОЕК ===");

            defaultSettings.Language = "en";
            defaultSettings.SoundEnabled = false;
            defaultSettings.Theme = "dark";

            defaultSettings.SaveSettings();
            Console.WriteLine("Настройки изменены: язык " + defaultSettings.Language +
                              " звук " + (defaultSettings.SoundEnabled ? "вкл" : "выкл") +
                              " тема " + defaultSettings.Theme);

            defaultSettings.ResetToDefaults();
            Console.WriteLine("Настройки сброшены: язык " + defaultSettings.Language +
                              " звук " + (defaultSettings.SoundEnabled ? "вкл" : "выкл") +
                              " тема " + defaultSettings.Theme);

            Console.WriteLine("\n=== ДЕМОНСТРАЦИЯ СТАТИСТИКИ ===");

            gameStatistics.AddGameResult(true, 120);
            gameStatistics.AddGameResult(false, 45);

            Console.WriteLine("Статистика после 2 игр:");
            Console.WriteLine("Всего игр: " + gameStatistics.TotalGames);
            Console.WriteLine("Побед: " + gameStatistics.Wins);
            Console.WriteLine("Поражений: " + gameStatistics.Losses);
            Console.WriteLine($"Процент побед: {gameStatistics.WinRate():P1}");
            Console.WriteLine("Среднее время: " + gameStatistics.AverageTime());

            game.EndGame(true);
            Console.WriteLine("Игра завершена. Статистика обновлена:");
            Console.WriteLine("Побед: " + gameStatistics.Wins);

            Console.WriteLine("Нажмите Enter для выхода...");
            Console.ReadLine();

        }

    }
}
