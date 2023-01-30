﻿using System;
using System.Reflection;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class WeatherMapScript
    {
        static bool init = true;
        static bool big = false;
        private float maxMapX, maxMapY;
        public void Init() {
            
            InternalCalls.SetEntityIsActive("weathermapbig", "WeatherMap", false);
            for (int i = 0; i < 25; i++)
            {
                int modI = i % 5;
                int divI = i / 5;
                if (modI != 0 && modI != 4 && divI != 0 && divI != 4)
                {
                    string MIcon = "MIcon" + i;
                    InternalCalls.SetEntityIsActive(MIcon, "WeatherMap", false);
                }
                string EIcon = "EIcon" + i;
                InternalCalls.SetEntityIsActive(EIcon, "WeatherMap", false);
            }
            if (init)
            {
                maxMapX = InternalCalls.GetScaleX("Water", "Level1");
                maxMapY = InternalCalls.GetScaleY("Water", "Level1");
                InternalCalls.WeatherAIinit(maxMapX, maxMapY);
                init = false;
            }
        }
        public void Update() {
            if ((InternalCalls.ButtonReleased("weathermap", "WeatherMap")) == true)
            {
                big = !big;
                if (big)
                {
                    InternalCalls.SetEntityIsActive("weathermapbig", "WeatherMap", true);
                }
                else
                {
                    InternalCalls.SetEntityIsActive("weathermapbig", "WeatherMap", false);
                }
                for (int i = 0; i < 25; i++)
                {
                    string EIcon = "EIcon" + i;
                    if (big)
                    {
                        InternalCalls.SetEntityIsActive(EIcon, "WeatherMap", true);
                    }
                    else
                    {
                        InternalCalls.SetEntityIsActive(EIcon, "WeatherMap", false);
                    }
                }
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
                if (big)
                {
                    string EIcon = "EIcon" + i;
                    InternalCalls.SetSpriteSheetIndex(EIcon, "WeatherMap", index);
                }
            }
            

        }

        public void Exit() {
            
        }
    }
}
