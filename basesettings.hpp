#pragma once

#include <QString>

class BaseSettings
{
protected:

    QString settingsVersion;
    bool isInitialized;


public:

    BaseSettings(const QString& version);

    virtual ~BaseSettings() = default;

    const QString& getVersion() const;
    bool getIsInitialized() const;
    virtual void validate() const;

};
