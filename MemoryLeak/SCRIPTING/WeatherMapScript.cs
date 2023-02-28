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
        public void Alive(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }
        public void Init(int _ENTITY) {

            VI.Entity.s_SetActive("weathermapbig", "WeatherMap", false);
            for (int i = 0; i < 25; i++)
            {
                int modI = i % 5;
                int divI = i / 5;
                if (modI != 0 && modI != 4 && divI != 0 && divI != 4)
                {
                    string MIcon = "MIcon" + i;
                    VI.Entity.s_SetActive(MIcon, "WeatherMap", false);
                }
            }
            VI.Entity.s_SetActive("weathermapbig", "WeatherMap", false);
            for (int i = 0; i < 25; i++)
            {
                string EIcon = "EIcon" + i;
                VI.Entity.s_SetActive(EIcon, "WeatherMap", false);
            }
            if (init)
            {
                
                maxMapX = VI.Transform.Scale.GetX(VI.Entity.GetId("Water", "Level1"));
                maxMapY = VI.Transform.Scale.GetY(VI.Entity.GetId("Water", "Level1"));
                VI.Weather.Init(maxMapX, maxMapY);
                init = false;
            }
        }
        public void Update(int _ENTITY) {
            if ((VI.Input.Button.s_Released("weathermap", "WeatherMap")) == true)
            {
                big = !big;
                
                if (big)
                {
                    VI.Entity.s_SetActive("weathermapbig", "WeatherMap", true);
                    for (int i = 0; i < 25; i++)
                    {
                        string EIcon = "EIcon" + i;
                        VI.Entity.s_SetActive(EIcon, "WeatherMap", true);
                    }
                }
                else
                {
                    VI.Entity.s_SetActive("weathermapbig", "WeatherMap", false);
                    for (int i = 0; i < 25; i++)
                    {
                        string EIcon = "EIcon" + i;
                        VI.Entity.s_SetActive(EIcon, "WeatherMap", false);
                    }
                }
            }
            for (int i = 0; i < 25; i++)
            {
                int modI = i % 5;
                int divI = i / 5;
                
                int index = VI.Weather.GetCurrent(i,
                    VI.Transform.Scale.GetY(VI.Entity.GetId("Boat", "Level1")), VI.Transform.Scale.GetY(VI.Entity.GetId("Boat", "Level1")));
                if (modI != 0 && modI != 4 && divI != 0 && divI != 4)
                {
                    string MIcon = "MIcon" + i;
                    VI.Animation.SpriteSheet.SheetIndex.s_Set(MIcon, "WeatherMap", index);
                    VI.Entity.s_SetActive(MIcon, "WeatherMap", true);
                }
                if (big)
                {
                    string EIcon = "EIcon" + i;
                    VI.Animation.SpriteSheet.SheetIndex.s_Set(EIcon, "WeatherMap", index);
                }
            }
            

        }

        public void Exit(int _ENTITY) {
            big = false;
            VI.Entity.s_SetActive("weathermapbig", "WeatherMap", false);
            for (int i = 0; i < 25; i++)
            {
                string EIcon = "EIcon" + i;
                VI.Entity.s_SetActive(EIcon, "WeatherMap", false);
            }
        }
        public void Dead(int _ENTITY)
        {

        }
    }
}
