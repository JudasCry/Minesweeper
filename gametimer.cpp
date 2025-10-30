#include "gametimer.hpp"

GameTimer::GameTimer() : elapsedSeconds(0), isRunning(false)
{
    // Обновляем время после каждой пройденной секунды //
    connect(&timer, &QTimer::timeout, this, &GameTimer::updateTimer);

}

void GameTimer::start() {

    if (!isRunning) {

        isRunning = true;
        timer.start(TIMER_INTERVAL_MS); // запускаем таймер на 1 секунду

    }
}

void GameTimer::stop() {

    if (isRunning) {

        isRunning = false;
        timer.stop();

    }
}

void GameTimer::restart() {

    stop();
    elapsedSeconds = 0;

}

int GameTimer::getElapsedSeconds() const {
    return elapsedSeconds;
}

bool GameTimer::getIsRunning() const {
    return isRunning;
}

QString GameTimer::getFormattedTime() const {

    int minutes = elapsedSeconds / SECONDS_PER_MINUTE;
    int seconds = elapsedSeconds % SECONDS_PER_MINUTE;

    // Форматируем время как MM:SS //
    return QString("%1:%2").arg(minutes, TIME_COMPONENT_WIDTH, DECIMAL_BASE, QChar('0')).arg(seconds, TIME_COMPONENT_WIDTH, DECIMAL_BASE, QChar('0'));

}

void GameTimer::updateTimer() {

    if (isRunning) {
        elapsedSeconds++;
        emit timeUpdated(getFormattedTime());
    }

}


