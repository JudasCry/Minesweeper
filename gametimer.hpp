#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QTimer>
#include <QTime>
#include <QString>

class GameTimer : public QObject
{
    Q_OBJECT

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

#endif // GAMETIMER_H
