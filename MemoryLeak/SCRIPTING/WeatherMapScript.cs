/*!*****************************************************************************
\file WeatherMapScript.cs
\author Huang Wei Jhin
\par DP email: h.weijhin\@digipen.edu
\par Group: Memory Leak Studios
\date 28-01-2023
\brief
WeatherMapScript contains multiple script components to run the Level1 of the game.
Part of which are:
- Functions of the weather map
- Expanding the weather minimap
- Gettign the each weather type of 9 or 16 locations in the mini and expanded map
*******************************************************************************/
using System;
using System.Reflection;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class WeatherMapScript : BaseScript
    {
        public override void PreInit(int _id)
        {
            var bs = new BaseScript();
            bs.PreInit(_id);
        }

        static bool init = true;
        static bool big = false;
        private float maxMapX, maxMapY;
        public void Init(int _id) {
            
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
            }
            InternalCalls.SetEntityIsActive("weathermapbig", "WeatherMap", false);
            for (int i = 0; i < 25; i++)
            {
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
        public void Update(int _id) {
            if ((InternalCalls.ButtonReleased("weathermap", "WeatherMap")) == true)
            {
                big = !big;
                
                if (big)
                {
                    InternalCalls.SetEntityIsActive("weathermapbig", "WeatherMap", true);
                    for (int i = 0; i < 25; i++)
                    {
                        string EIcon = "EIcon" + i;
                        InternalCalls.SetEntityIsActive(EIcon, "WeatherMap", true);
                    }
                }
                else
                {
                    InternalCalls.SetEntityIsActive("weathermapbig", "WeatherMap", false);
                    for (int i = 0; i < 25; i++)
                    {
                        string EIcon = "EIcon" + i;
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
                    InternalCalls.SetEntityIsActive(MIcon, "WeatherMap", true);
                }
                if (big)
                {
                    string EIcon = "EIcon" + i;
                    InternalCalls.SetSpriteSheetIndex(EIcon, "WeatherMap", index);
                }
            }
            

        }

        public void Exit(int _id) {
            big = false;
            InternalCalls.SetEntityIsActive("weathermapbig", "WeatherMap", false);
            for (int i = 0; i < 25; i++)
            {
                string EIcon = "EIcon" + i;
                InternalCalls.SetEntityIsActive(EIcon, "WeatherMap", false);
            }
        }
    }
}
