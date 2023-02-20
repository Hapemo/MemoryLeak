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
    public class WeatherMapScript
    {
        static bool init = true;
        static bool big = false;
        private float maxMapX, maxMapY;
        public void Init(int _id) {
            
            VI.Entity.SetActive("weathermapbig", "WeatherMap", false);
            for (int i = 0; i < 25; i++)
            {
                int modI = i % 5;
                int divI = i / 5;
                if (modI != 0 && modI != 4 && divI != 0 && divI != 4)
                {
                    string MIcon = "MIcon" + i;
                    VI.Entity.SetActive(MIcon, "WeatherMap", false);
                }
            }
            VI.Entity.SetActive("weathermapbig", "WeatherMap", false);
            for (int i = 0; i < 25; i++)
            {
                string EIcon = "EIcon" + i;
                VI.Entity.SetActive(EIcon, "WeatherMap", false);
            }
            if (init)
            {
                maxMapX = VI.Transform.Scale.GetX("Water", "Level1");
                maxMapY = VI.Transform.Scale.GetY("Water", "Level1");
                VI.Weather.Init(maxMapX, maxMapY);
                init = false;
            }
        }
        public void Update(int _id) {
            if ((VI.Input.Button.Released("weathermap", "WeatherMap")) == true)
            {
                big = !big;
                
                if (big)
                {
                    VI.Entity.SetActive("weathermapbig", "WeatherMap", true);
                    for (int i = 0; i < 25; i++)
                    {
                        string EIcon = "EIcon" + i;
                        VI.Entity.SetActive(EIcon, "WeatherMap", true);
                    }
                }
                else
                {
                    VI.Entity.SetActive("weathermapbig", "WeatherMap", false);
                    for (int i = 0; i < 25; i++)
                    {
                        string EIcon = "EIcon" + i;
                        VI.Entity.SetActive(EIcon, "WeatherMap", false);
                    }
                }
            }
            for (int i = 0; i < 25; i++)
            {
                int modI = i % 5;
                int divI = i / 5;
                int index = VI.Weather.GetCurrent(i, 
                    VI.Transform.Position.GetX("Boat", "Level1"), VI.Transform.Position.GetY("Boat", "Level1"));
                if (modI != 0 && modI != 4 && divI != 0 && divI != 4)
                {
                    string MIcon = "MIcon" + i;
                    VI.Animation.SheetIndex.Set(MIcon, "WeatherMap", index);
                    VI.Entity.SetActive(MIcon, "WeatherMap", true);
                }
                if (big)
                {
                    string EIcon = "EIcon" + i;
                    VI.Animation.SheetIndex.Set(EIcon, "WeatherMap", index);
                }
            }
            

        }

        public void Exit(int _id) {
            big = false;
            VI.Entity.SetActive("weathermapbig", "WeatherMap", false);
            for (int i = 0; i < 25; i++)
            {
                string EIcon = "EIcon" + i;
                VI.Entity.SetActive(EIcon, "WeatherMap", false);
            }
        }
    }
}
