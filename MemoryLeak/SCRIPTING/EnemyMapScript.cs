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
    public class EnemyMapScript : BaseScript
    {
        public override void PreInit(int _id)
        {
            var bs = new BaseScript();
            bs.PreInit(_id);
        }

        static bool init = true;
        static bool big = false;
        private float MapX, MapY;
        private float miniMapX, miniMapY;
        private float expMapX, expMapY;
        public void Init(int _id) {

            InternalCalls.SetEntityIsActive("enemymapbig", "EnemyMap", false);
            InternalCalls.SetEntityIsActive("enemybig", "EnemyMap", false);
            InternalCalls.SetEntityIsActive("playerbig", "EnemyMap", false);
            MapX = InternalCalls.GetScaleX("Water", "Level1");
            MapY = InternalCalls.GetScaleY("Water", "Level1");
            miniMapX = InternalCalls.GetScaleX("enemymap", "EnemyMap");
            miniMapY = InternalCalls.GetScaleY("enemymap", "EnemyMap");
            expMapX = InternalCalls.GetScaleX("enemymapbig", "EnemyMap");
            expMapY = InternalCalls.GetScaleY("enemymapbig", "EnemyMap");
           
        }

        public void Update(int _id) {
            
            if (init)
            {
                init = false;
                
            }

            //////////////////////////////////////////////init
            if ((InternalCalls.ButtonReleased("enemymap", "EnemyMap")) == true)
            {
                big = !big;
                if (big)
                {
                    InternalCalls.SetEntityIsActive("enemymapbig", "EnemyMap", true);
                    InternalCalls.SetEntityIsActive("enemybig", "EnemyMap", true);
                    InternalCalls.SetEntityIsActive("playerbig", "EnemyMap", true);
                }
                else {
                    InternalCalls.SetEntityIsActive("enemymapbig", "EnemyMap", false);
                    InternalCalls.SetEntityIsActive("enemybig", "EnemyMap", false);
                    InternalCalls.SetEntityIsActive("playerbig", "EnemyMap", false);
                }
            }
            float posx = InternalCalls.GetPosX("Enemy", "Level1")- InternalCalls.GetPosX("Boat", "Level1");
            float posy = InternalCalls.GetPosY("Enemy", "Level1") - InternalCalls.GetPosY("Boat", "Level1");
            if (posx > MapX / 4 || posy > MapY / 4)
            {
                InternalCalls.SetEntityIsActive("enemy", "EnemyMap", false);
            }
            else
            {
                InternalCalls.SetEntityIsActive("enemy", "EnemyMap", true);
                float eposx = InternalCalls.GetPosX("player", "EnemyMap") + (posx * (miniMapX / MapX));
                float eposy = InternalCalls.GetPosY("player", "EnemyMap") + (posy * (miniMapY / MapY));
                InternalCalls.SetPosX("enemy", "EnemyMap", eposx);
                InternalCalls.SetPosY("enemy", "EnemyMap", eposy);
            }
            if (big)
            { 
                if (posx > MapX / 2 || posy > MapY / 2)
                {
                    InternalCalls.SetEntityIsActive("enemybig", "EnemyMap", false);
                }
                else
                {
                    InternalCalls.SetEntityIsActive("enemybig", "EnemyMap", true);
                    float eposx = InternalCalls.GetPosX("playerbig", "EnemyMap") + (posx * (expMapX / MapX));
                    float eposy = InternalCalls.GetPosY("playerbig", "EnemyMap") + (posy * (expMapY / MapY));
                    InternalCalls.SetPosX("enemybig", "EnemyMap", eposx);
                    InternalCalls.SetPosY("enemybig", "EnemyMap", eposy);
                }
            }
        }

        public void Exit(int _id) {
            big= false;
            InternalCalls.SetEntityIsActive("enemymapbig", "EnemyMap", false);
            InternalCalls.SetEntityIsActive("enemybig", "EnemyMap", false);
            InternalCalls.SetEntityIsActive("playerbig", "EnemyMap", false);

        }
    }
}
