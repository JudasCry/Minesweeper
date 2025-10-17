#include "gametimer.hpp"

GameTimer::GameTimer() : elapsedSeconds(0), isRunning(false)
{
    // Обновляем время после каждой пройденной секунды //
    connect(&timer, &QTimer::timeout, this, &GameTimer::updateTimer);

}

void GameTimer::start() {

    if (!isRunning) {

        isRunning = true;
        timer.start(1000); // запускаем таймер на 1 секунду

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

    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;

    // Форматируем время как MM:SS //
    return QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));

}

void GameTimer::updateTimer() {

    if (isRunning) {
        elapsedSeconds++;
        emit timeUpdated(getFormattedTime());
    }

}


