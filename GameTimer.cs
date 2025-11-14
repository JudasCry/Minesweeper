using System;
using System.Windows.Forms; // Таймер

namespace Lab3
{
    public class GameTimer
    {

        private const int TIMER_INTERVAL_MS = 1000; // Интервал обновления таймера в 1000 мс
        private const int SECONDS_PER_MINUTE = 60; // 60 секунд = 1 минута

        private Timer _timer;

        public int ElapsedSeconds { get; set; }
        public bool IsRunning { get; set; }

        public event Action<string> TimeUpdated; // Событие (аналог сигналам и слотам в Qt)

        public GameTimer()
        {

            _timer = new Timer();
            _timer.Interval = TIMER_INTERVAL_MS;
            _timer.Tick += Timer_Tick; // Подписываемся на событие Tick (аналог QTimer::timeout)

        }

        public void Start()
        {

            if (!IsRunning)
            {

                IsRunning = true;
                _timer.Start();

            }

        }

        public void Stop()
        {

            if (IsRunning)
            {

                IsRunning = false;
                _timer.Stop();

            }

        }

        public void Restart()
        {

            Stop();
            ElapsedSeconds = 0;
            TimeUpdated?.Invoke(GetFormattedTime());

        }

        public string GetFormattedTime()
        {

            int minutes = ElapsedSeconds / SECONDS_PER_MINUTE;
            int seconds = ElapsedSeconds % SECONDS_PER_MINUTE;


            return $" {minutes:D2}:{seconds:D2}";
        }

        public void Timer_Tick(object sender, EventArgs e)
        {

            if (IsRunning)
            {

                ElapsedSeconds++;
                TimeUpdated?.Invoke(GetFormattedTime());

            }

        }

        // Очистка ресурсов таймера //
        public void Dispose()
        {

            _timer.Stop();
            _timer.Tick -= Timer_Tick; // Отписываемся от события
            _timer.Dispose(); // Освобождаем ресурсы таймера

        }

    }
}
