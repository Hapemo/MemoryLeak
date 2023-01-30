using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class WeatherMapScript
    {
        private float maxMapX, maxMapY;
        public void Init() {
            maxMapX = InternalCalls.GetScaleX("Water", "Level1");
            maxMapY = InternalCalls.GetScaleY("Water", "Level1");
            InternalCalls.WeatherAIinit(maxMapX, maxMapY);
        }

        public void Update() {
            InternalCalls.EntityDeactivate("weathermap", "WeatherMap");
            InternalCalls.EntityDeactivate("weathermapbig", "WeatherMap");
            for (int i = 0; i < 25; i++)
            {
                int modI = i % 5;
                int divI = i / 5;
                if (modI != 0 && modI != 4 && divI != 0 && divI != 4)
                {
                    string MIcon = "MIcon" + i;
                    InternalCalls.EntityDeactivate(MIcon, "WeatherMap");
                }
                string EIcon = "EIcon" + i;
                InternalCalls.EntityDeactivate(EIcon, "WeatherMap");
            }
            for (int i = 0; i < 25; i++)
            {
                int modI = i % 5;
                int divI = i / 5;
                int index = InternalCalls.GetCurrentWeather(i, 
                    InternalCalls.GetPosX("Boat", "Level1"), InternalCalls.GetPosY("Boat", "Level1"));
                if (modI != 0 && modI != 4 && divI != 0 && divI != 4)
                {
                    string MIcon = "MIcon" + i;
                    InternalCalls.SetSpriteSheetIndex(MIcon, "WeatherMap", index);
                }
                string EIcon = "EIcon" + i;
                InternalCalls.SetSpriteSheetIndex(EIcon, "WeatherMap", index);
            }
            
        }

        public void Exit() {
            
        }
    }
}
