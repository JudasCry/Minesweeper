#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QSettings>

class Settings
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

    void saveSettings() const;
    void loadSettings();
    void resetToDefaults();
    const QString& getLanguage() const;
    bool getSoundEnabled() const;
    const QString& getTheme() const;
    void setLanguage(const QString& language);
    void setSoundEnabled(bool enabled);
    void setTheme(const QString& themeName);

};

#endif // SETTINGS_H
