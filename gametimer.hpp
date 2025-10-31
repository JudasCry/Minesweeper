#pragma once

#include <QTimer>
#include <QTime>
#include <QString>

class GameTimer : public QObject
{
    Q_OBJECT

private:

    static const int TIMER_INTERVAL_MS = 1000; // Интервал обновления таймера в 1000 мс
    static const int SECONDS_PER_MINUTE = 60; // 60 секунд = 1 минута
    static const int TIME_COMPONENT_WIDTH = 2; // Минимальная ширина формата для минут и секунд
    static const int DECIMAL_BASE = 10; // Основание системы счисления (десятичная)


private:

    int elapsedSeconds;
    bool isRunning;
    QTimer timer;

public:

    GameTimer();

    void start();
    void stop();
    void restart();
    int getElapsedSeconds() const;
    bool getIsRunning() const;
    QString getFormattedTime() const;

public slots:

    void updateTimer();

signals:

    void timeUpdated(const QString& formattedTime);

};
