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
        static bool big = false;
        private float MapX, MapY;
        private float miniMapX, miniMapY;
        private float expMapX, expMapY;
        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }
        public void Init(int _ENTITY) {

            VI.Entity.s_SetActive("enemymapbig", "EnemyMap", false);
            VI.Entity.s_SetActive("enemybig", "EnemyMap", false);
            VI.Entity.s_SetActive("playerbig", "EnemyMap", false);
            MapX = VI.Transform.Scale.s_GetX("Water", "Level1");
            MapY = VI.Transform.Scale.s_GetY("Water", "Level1");
            miniMapX = VI.Transform.Scale.s_GetX("enemymap", "EnemyMap");
            miniMapY = VI.Transform.Scale.s_GetY("enemymap", "EnemyMap");
            expMapX = VI.Transform.Scale.s_GetX("enemymapbig", "EnemyMap");
            expMapY = VI.Transform.Scale.s_GetY("enemymapbig", "EnemyMap");

        }

        public void EarlyUpdate(int _ENTITY) { }

        public void Update(int _ENTITY) {
            
            if (init)
            {
                init = false;
                
            }

            //////////////////////////////////////////////init
            if ((VI.Input.Button.s_Released("enemymap", "EnemyMap")) == true)
            {
                big = !big;
                if (big)
                {
                    VI.Entity.s_SetActive("enemymapbig", "EnemyMap", true);
                    VI.Entity.s_SetActive("enemybig", "EnemyMap", true);
                    VI.Entity.s_SetActive("playerbig", "EnemyMap", true);
                }
                else {
                    VI.Entity.s_SetActive("enemymapbig", "EnemyMap", false);
                    VI.Entity.s_SetActive("enemybig", "EnemyMap", false);
                    VI.Entity.s_SetActive("playerbig", "EnemyMap", false);
                }
            }
            float posx = VI.Transform.Position.s_GetX("Enemy", "Level1")- VI.Transform.Position.s_GetX("Boat", "Level1");
            float posy = VI.Transform.Position.s_GetY("Enemy", "Level1") - VI.Transform.Position.s_GetY("Boat", "Level1");
            if (posx > MapX / 4 || posy > MapY / 4)
            {
                VI.Entity.s_SetActive("enemy", "EnemyMap", false);
            }
            else
            {
                VI.Entity.s_SetActive("enemy", "EnemyMap", true);
                float eposx = VI.Transform.Position.s_GetX("player", "EnemyMap") + (posx * (miniMapX / MapX));
                float eposy = VI.Transform.Position.s_GetY("player", "EnemyMap") + (posy * (miniMapY / MapY));
                VI.Transform.Position.s_SetX("enemy", "EnemyMap", eposx);
                VI.Transform.Position.s_SetY("enemy", "EnemyMap", eposy);
            }
            if (big)
            { 
                if (posx > MapX / 2 || posy > MapY / 2)
                {
                    VI.Entity.s_SetActive("enemybig", "EnemyMap", false);
                }
                else
                {
                    VI.Entity.s_SetActive("enemybig", "EnemyMap", true);
                    float eposx = VI.Transform.Position.s_GetX("playerbig", "EnemyMap") + (posx * (expMapX / MapX));
                    float eposy = VI.Transform.Position.s_GetY("playerbig", "EnemyMap") + (posy * (expMapY / MapY));
                    VI.Transform.Position.s_SetX("enemybig", "EnemyMap", eposx);
                    VI.Transform.Position.s_SetY("enemybig", "EnemyMap", eposy);
                }
            }
        }

        public void FixedUpdate(int _ENTITY) {

        }

        public void LateUpdate(int _ENTITY) { }

        public void Exit(int _ENTITY) {
            big= false;
            VI.Entity.s_SetActive("enemymapbig", "EnemyMap", false);
            VI.Entity.s_SetActive("enemybig", "EnemyMap", false);
            VI.Entity.s_SetActive("playerbig", "EnemyMap", false);

        }
        public void Dead(int _ENTITY) {

        }
    }
}
