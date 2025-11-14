using System.Configuration;

namespace Lab3
{

    [SettingsGroupName("ApplicationSettings")] // Указываем группу настроек
    public class Settings : ApplicationSettingsBase
    {

        [UserScopedSetting()] // Указывает, что настройка является пользовательской
        [DefaultSettingValue("ru")] // Значение по умолчанию
        public string Language
        {
            get { return ((string)this["Language"]); }
            set { this["Language"] = value; }
        }

        [UserScopedSetting()]
        [DefaultSettingValue("True")]
        public bool SoundEnabled
        {
            get { return ((bool)this["SoundEnabled"]); }
            set { this["SoundEnabled"] = value; }
        }

        [UserScopedSetting()]
        [DefaultSettingValue("default")]
        public string Theme
        {
            get { return ((string)this["Theme"]); }
            set { this["Theme"] = value; }
        }

        public static Settings Instance
        {
            get { return (Settings)ApplicationSettingsBase.Synchronized(new Settings()); }
        }

        public void SaveSettings() 
        {
            this.Save();
        }

        public void ResetToDefaults()
        {
            this.Reset();
            this.Save();
        }

    }
}
