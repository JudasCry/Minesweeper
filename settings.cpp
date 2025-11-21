#include "settings.hpp"

const QString Settings::THEME_KEY = "theme";
const QString Settings::SOUND_ENABLED_KEY = "soundEnabled";
const QString Settings::LANGUAGE_KEY = "language";

Settings::Settings(const QString& version)

    : language("ru"),
      soundEnabled(true),
      theme("default"),
      BaseSettings(version)

{
    loadSettings();

    Settings::validate();
}

// Загрузка настроек из файла //
void Settings::loadSettings() {

    QSettings settings;

    if (settings.contains(LANGUAGE_KEY)) {
        language = settings.value(LANGUAGE_KEY).toString();
    }
    else {
        language = "ru";
    }

    if (settings.contains(SOUND_ENABLED_KEY)) {
        soundEnabled = settings.value(SOUND_ENABLED_KEY).toBool();
    }
    else {
        soundEnabled = true;
    }

    if (settings.contains(THEME_KEY)) {
        theme = settings.value(THEME_KEY).toString();
    }
    else {
        theme = "default";
    }

}

// Сохранение настроек в файл //
void Settings::saveSettings() const {

    QSettings settings;

    settings.setValue(LANGUAGE_KEY, language);
    settings.setValue(SOUND_ENABLED_KEY, soundEnabled);
    settings.setValue(THEME_KEY, theme);

}

// Сброс настроек к значениям по умолчанию //
void Settings::resetToDefaults() {

    language = "ru";
    soundEnabled = true;
    theme = "default";

    saveSettings();
}

// Геттеры //
const QString& Settings::getLanguage() const {
    return language;
}

bool Settings::getSoundEnabled() const {
    return soundEnabled;
}

const QString& Settings::getTheme() const {
    return theme;
}

// Сеттеры //
void Settings::setLanguage(const QString& lang) {

    language = lang;

    saveSettings();

}

void Settings::setSoundEnabled(bool enabled) {

    soundEnabled = enabled;

    saveSettings();

}

void Settings::setTheme(const QString& themeName) {

    theme = themeName;

    saveSettings();

}

void Settings::validate() const {

    BaseSettings::validate();

    if (language.isEmpty()) {
        throw std::invalid_argument("Язык не может быть пустым");
    }
    if (theme.isEmpty()) {
        throw std::invalid_argument("Тема не может быть пустой");
    }
}
