#include "basesettings.hpp"
#include <stdexcept>

BaseSettings::BaseSettings(const QString& version)

    : settingsVersion(version),
      isInitialized(true)

{
}

const QString& BaseSettings::getVersion() const {
    return settingsVersion;
}

bool BaseSettings::getIsInitialized() const {
    return isInitialized;
}

void BaseSettings::validate() const {
    if (settingsVersion.isEmpty()) {
        throw std::invalid_argument("Версия не может быть пустой");
    }
}
