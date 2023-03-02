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
using System.Runtime.Remoting.Metadata.W3cXsd2001;

namespace BonVoyage {
    public class WeatherMapScript
    {
        static bool big = false;
        int weathermapID;
        float textOffsetX;
        float textOffsetY;
        float textbigOffsetX;
        float textbigOffsetY;
        float textScale;
        float textbigScale;
        private float maxMapX, maxMapY;
        public void Alive(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            weathermapID = VI.Entity.GetId("weathermap", "WeatherMap");
            textOffsetX = -59;// VI.Text.Offset.GetX(minimapID);
            textOffsetY = -170;// VI.Text.Offset.GetY(minimapID);
            textbigOffsetX = -100;
            textbigOffsetY = 360;
            textScale = VI.Text.Scale.Get(weathermapID);
            textbigScale = 1.0f;
            maxMapX = VI.Transform.Scale.GetX(VI.Entity.GetId("Water", "Level1"))/2;
            maxMapY = VI.Transform.Scale.GetY(VI.Entity.GetId("Water", "Level1"))/2;
            VI.Weather.Init(maxMapX, maxMapY);
        }
        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            VI.Entity.s_SetActive("blur", "WeatherMap", false);
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
            big = false;
            VI.Animation.Transform.SetNext(weathermapID, 0);
            VI.Text.Offset.Set(weathermapID, textOffsetX, textOffsetY);
            VI.Text.Scale.Set(weathermapID, textScale);
            VI.Animation.Transform.Start(weathermapID);
            VI.Entity.Sprite.SetType(weathermapID, 1);
            for (int i = 0; i < 25; i++)
            {
                int modI = i % 5;
                int divI = i / 5;
                string EIcon = "EIcon" + i;
                if (!(modI != 0 && modI != 4 && divI != 0 && divI != 4))
                {
                    VI.Entity.s_SetActive(EIcon, "WeatherMap", false);
                }
                VI.Animation.Transform.SetNext(VI.Entity.GetId(EIcon, "WeatherMap"), 0);
                VI.Animation.Transform.Start(VI.Entity.GetId(EIcon, "WeatherMap"));
            }

            VI.Entity.s_SetActive("blur", "WeatherMap", false);
        }
        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            if (!big && (VI.Input.Button.Released(weathermapID)))
            {
                big = true;
                VI.Animation.Transform.SetNext(weathermapID, 1);
                VI.Text.Offset.Set(weathermapID, textbigOffsetX, textbigOffsetY);
                VI.Text.Scale.Set(weathermapID, textbigScale);
                VI.Animation.Transform.Start(weathermapID);
                VI.Entity.Sprite.SetType(weathermapID, 0);
                for (int i = 0; i < 25; i++)
                {
                    string EIcon = "EIcon" + i;
                    VI.Entity.s_SetActive(EIcon, "WeatherMap", true);
                    VI.Animation.Transform.SetNext(VI.Entity.GetId(EIcon, "WeatherMap"), 1);
                    VI.Animation.Transform.Start(VI.Entity.GetId(EIcon, "WeatherMap"));
                }
                VI.Entity.s_SetActive("blur", "WeatherMap", true);
            }
            else if (big && (VI.Input.Mouse.Release(349)) && (!VI.Input.Button.Released(weathermapID)))
            {
                big = false;
                VI.Animation.Transform.SetNext(weathermapID, 0);
                VI.Text.Offset.Set(weathermapID, textOffsetX, textOffsetY);
                VI.Text.Scale.Set(weathermapID, textScale);
                VI.Animation.Transform.Start(weathermapID);
                VI.Entity.Sprite.SetType(weathermapID, 1);
                for (int i = 0; i < 25; i++)
                {
                    int modI = i % 5;
                    int divI = i / 5;
                    string EIcon = "EIcon" + i;
                    if (!(modI != 0 && modI != 4 && divI != 0 && divI != 4))
                    {
                        VI.Entity.s_SetActive(EIcon, "WeatherMap", false);
                    }
                    VI.Animation.Transform.SetNext(VI.Entity.GetId(EIcon, "WeatherMap"), 0);
                    VI.Animation.Transform.Start(VI.Entity.GetId(EIcon, "WeatherMap"));
                }

                VI.Entity.s_SetActive("blur", "WeatherMap", false);
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
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            big = false;
            VI.Animation.Transform.SetNext(weathermapID, 0);
            VI.Text.Offset.Set(weathermapID, textOffsetX, textOffsetY);
            VI.Text.Scale.Set(weathermapID, textScale);
            VI.Animation.Transform.Start(weathermapID);
            VI.Entity.Sprite.SetType(weathermapID, 1);
            for (int i = 0; i < 25; i++)
            {
                int modI = i % 5;
                int divI = i / 5;
                string EIcon = "EIcon" + i;
                if (!(modI != 0 && modI != 4 && divI != 0 && divI != 4))
                {
                    VI.Entity.s_SetActive(EIcon, "WeatherMap", false);
                }
                VI.Animation.Transform.SetNext(VI.Entity.GetId(EIcon, "WeatherMap"), 0);
                VI.Animation.Transform.Start(VI.Entity.GetId(EIcon, "WeatherMap"));
            }

            VI.Entity.s_SetActive("blur", "WeatherMap", false);
        }
        public void Dead(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }
    }
}
