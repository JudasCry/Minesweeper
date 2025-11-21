#pragma once

#include <QString>
#include <QSettings>
#include "basesettings.hpp"

class Settings : public BaseSettings
{
private:

    static const QString LANGUAGE_KEY;
    static const QString SOUND_ENABLED_KEY;
    static const QString THEME_KEY;

private:

    QString language;
    bool soundEnabled;
    QString theme;

public:

    Settings();

    Settings(const QString& version);

    void saveSettings() const;
    void loadSettings();
    void resetToDefaults();
    const QString& getLanguage() const;
    bool getSoundEnabled() const;
    const QString& getTheme() const;
    void setLanguage(const QString& language);
    void setSoundEnabled(bool enabled);
    void setTheme(const QString& themeName);

    void validate() const override;

};
