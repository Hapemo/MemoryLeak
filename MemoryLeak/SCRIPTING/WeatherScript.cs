using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class WeatherScript
    {
        private float maxMapX, maxMapY;
        public void Init() {
            maxMapX = InternalCalls.GetScaleX("Water", "Level1");
            maxMapY = InternalCalls.GetScaleY("Water", "Level1");
            InternalCalls.WeatherAIinit(maxMapX, maxMapY);
        }

        public void Update() {
            for (int i = 0; i < 25; i++)
            {
                int modI = i % 5;
                int divI = i / 5;
                if (modI != 0 && modI != 4 && divI != 0 && divI != 4)
                {
                    string icon = "MIcon" + i;
                    int index = InternalCalls.GetCurrentWeather(i, 
                        InternalCalls.GetPosX("Boat", "Level1"), InternalCalls.GetPosY("Boat", "Level1"));
                    InternalCalls.SetSpriteSheetIndex(icon, "WeatherMap", index);
                }
            }
            
        }

        public void Exit() {
            
        }
    }
}
