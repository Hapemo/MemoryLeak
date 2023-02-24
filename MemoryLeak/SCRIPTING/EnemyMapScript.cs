/*!*****************************************************************************
\file EnemyMapScript.cs
\author Huang Wei Jhin
\par DP email: h.weijhin\@digipen.edu
\par Group: Memory Leak Studios
\date 28-01-2023
\brief
EnemyMapScript contains multiple script components to run the Level1 of the game.
Part of which are:
- Functions of the ememy map
- Expanding the ememy minimap
- Calculating the position of the player and enemy in the mini and expanded map
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class EnemyMapScript
    {
        static bool init = true;
        private float MapX, MapY;
        private float miniMapX, miniMapY;
        private float expMapX, expMapY;
        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            VI.Entity.s_SetActive("enemymapbig", "WeatherMap", false);
            VI.Entity.s_SetActive("enemybig", "WeatherMap", false);
            VI.Entity.s_SetActive("playerbig", "WeatherMap", false);
            MapX = VI.Transform.Scale.s_GetX("Water", "Level1");
            MapY = VI.Transform.Scale.s_GetY("Water", "Level1");
            miniMapX = VI.Transform.Scale.s_GetX("enemymap", "WeatherMap");
            miniMapY = VI.Transform.Scale.s_GetY("enemymap", "WeatherMap");
            expMapX = VI.Transform.Scale.s_GetX("enemymapbig", "WeatherMap");
            expMapY = VI.Transform.Scale.s_GetY("enemymapbig", "WeatherMap");
        }
        public void Init(int _ENTITY) {

            VI.Entity.s_SetActive("enemymap", "WeatherMap", true);
            VI.Entity.s_SetActive("enemy", "WeatherMap", true);
            VI.Entity.s_SetActive("player", "WeatherMap", true);
            if (CrystalBallScript.Big())
            {
                VI.Entity.s_SetActive("enemymapbig", "WeatherMap", true);
                VI.Entity.s_SetActive("enemybig", "WeatherMap", true);
                VI.Entity.s_SetActive("playerbig", "WeatherMap", true);
            }
        }

        public void Update(int _ENTITY) {
            
            if (init)
            {
                init = false;
                
            }

            //////////////////////////////////////////////init
            
             if (CrystalBallScript.Big())
             {
                 VI.Entity.s_SetActive("enemymapbig", "WeatherMap", true);
                 VI.Entity.s_SetActive("enemybig", "WeatherMap", true);
                 VI.Entity.s_SetActive("playerbig", "WeatherMap", true);
             }
             else {
                 VI.Entity.s_SetActive("enemymapbig", "WeatherMap", false);
                 VI.Entity.s_SetActive("enemybig", "WeatherMap", false);
                 VI.Entity.s_SetActive("playerbig", "WeatherMap", false);
             }

            float posx = VI.Transform.Position.s_GetX("Enemy", "Level1")- VI.Transform.Position.s_GetX("Boat", "Level1");
            float posy = VI.Transform.Position.s_GetY("Enemy", "Level1") - VI.Transform.Position.s_GetY("Boat", "Level1");
            if (posx > MapX / 4 || posy > MapY / 4)
            {
                VI.Entity.s_SetActive("enemy", "WeatherMap", false);
            }
            else
            {
                VI.Entity.s_SetActive("enemy", "WeatherMap", true);
                float eposx = VI.Transform.Position.s_GetX("player", "WeatherMap") + (posx * (miniMapX / MapX));
                float eposy = VI.Transform.Position.s_GetY("player", "WeatherMap") + (posy * (miniMapY / MapY));
                VI.Transform.Position.s_SetX("enemy", "WeatherMap", eposx);
                VI.Transform.Position.s_SetY("enemy", "WeatherMap", eposy);
            }
            if (CrystalBallScript.Big())
            { 
                if (posx > MapX / 2 || posy > MapY / 2)
                {
                    VI.Entity.s_SetActive("enemybig", "WeatherMap", false);
                }
                else
                {
                    VI.Entity.s_SetActive("enemybig", "WeatherMap", true);
                    float eposx = VI.Transform.Position.s_GetX("playerbig", "WeatherMap") + (posx * (expMapX / MapX));
                    float eposy = VI.Transform.Position.s_GetY("playerbig", "WeatherMap") + (posy * (expMapY / MapY));
                    VI.Transform.Position.s_SetX("enemybig", "WeatherMap", eposx);
                    VI.Transform.Position.s_SetY("enemybig", "WeatherMap", eposy);
                }
            }
        }

        public void FixedUpdate(int _ENTITY) {

        }

        public void Exit(int _ENTITY) {
            VI.Entity.s_SetActive("enemymapbig", "WeatherMap", false);
            VI.Entity.s_SetActive("enemybig", "WeatherMap", false);
            VI.Entity.s_SetActive("playerbig", "WeatherMap", false);
            VI.Entity.s_SetActive("enemymap", "WeatherMap", false);
            VI.Entity.s_SetActive("enemy", "WeatherMap", false);
            VI.Entity.s_SetActive("player", "WeatherMap", false);
        }
        public void Dead(int _ENTITY) {

        }
    }
}
