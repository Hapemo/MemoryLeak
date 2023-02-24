/*!*****************************************************************************
\file CrystalBallScript.cs
\author Huang Wei Jhin
\par DP email: h.weijhin\@digipen.edu
\par Group: Memory Leak Studios
\date 28-01-2023
\brief
CrystalBallScript contains multiple script components to run the Level1 of the game.
Part of which are:
- Toggling of the mini maps
    -Minimap
    -WeatherMap
    -EmemyMap
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class CrystalBallScript
    {
        int toggle = 0; // 0 minimap, 1, weathermap, 2 enemymap
        int prevTog = -1;

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void Init(int _ENTITY) {
            //InternalCalls.SetEntityIsActive("weathermap", "WeatherMap", false);
            //InternalCalls.SetEntityIsActive("minimap", "MiniMap", false);
            //InternalCalls.SetEntityIsActive("enemymap", "EnemyMap", false);
            VI.Entity.s_Deactivate("Ball", "Dialogue");
        }

        public void EarlyUpdate(int _ENTITY) { }

        public void Update(int _ENTITY)
        {
            VI.Entity.s_Activate("Ball", "Dialogue");
            if ((VI.Input.Button.s_Released("cyclemap", "Dialogue")) == true)
            {
                toggle = toggle >= 2 ? 0 : (toggle + 1);
            }
            if(prevTog != toggle)
            { 
                if (toggle == 0)
                {
                    VI.Entity.s_Deactivate("weathermap", "WeatherMap");
                    VI.Entity.s_Deactivate("enemymap", "EnemyMap");
                    VI.Scene.Play("MiniMap");
                    VI.Entity.s_Activate("minimap", "MiniMap");
                    VI.Scene.Pause("WeatherMap");
                    VI.Scene.Pause("EnemyMap");
                    //InternalCalls.SetEntityIsActive("minimap", "MiniMap", true);
                    //InternalCalls.SetEntityIsActive("weathermap", "WeatherMap", false);
                    //InternalCalls.SetEntityIsActive("enemymap", "EnemyMap", false);
                    //InternalCalls.SetEntityIsActive("enemy", "EnemyMap", false);
                    //InternalCalls.SetEntityIsActive("player", "EnemyMap", false);
                    //for (int i = 0; i < 25; i++)
                    //{
                    //    int modI = i % 5;
                    //    int divI = i / 5;
                    //    if (modI != 0 && modI != 4 && divI != 0 && divI != 4)
                    //    {
                    //        string MIcon = "MIcon" + i;
                    //        InternalCalls.SetEntityIsActive(MIcon, "WeatherMap", false);
                    //    }
                    //}
                }
                else if (toggle == 1)
                {
                    VI.Entity.s_Deactivate("minimap", "MiniMap");
                    VI.Entity.s_Deactivate("enemymap", "EnemyMap");
                    VI.Scene.Pause("MiniMap");
                    VI.Scene.Play("WeatherMap");
                    VI.Entity.s_Activate("weathermap", "WeatherMap");
                    VI.Scene.Pause("EnemyMap");
                    //InternalCalls.SetEntityIsActive("minimap", "MiniMap", false);
                    //InternalCalls.SetEntityIsActive("weathermap", "WeatherMap", true);
                    //InternalCalls.SetEntityIsActive("enemymap", "EnemyMap", false);
                    //InternalCalls.SetEntityIsActive("enemy", "EnemyMap", false);
                    //InternalCalls.SetEntityIsActive("player", "EnemyMap", false);
                    //for (int i = 0; i < 25; i++)
                    //{
                    //    int modI = i % 5;
                    //    int divI = i / 5;
                    //    if (modI != 0 && modI != 4 && divI != 0 && divI != 4)
                    //    {
                    //        string MIcon = "MIcon" + i;
                    //        InternalCalls.SetEntityIsActive(MIcon, "WeatherMap", true);
                    //    }
                    //}

                }
                else if (toggle == 2)
                {
                    VI.Entity.s_Deactivate("minimap", "MiniMap");
                    VI.Entity.s_Deactivate("weathermap", "WeatherMap");
                    VI.Scene.Pause("MiniMap");
                    VI.Scene.Pause("WeatherMap");
                    VI.Scene.Play("EnemyMap");
                    VI.Entity.s_Activate("enemymap", "EnemyMap");
                    //InternalCalls.SetEntityIsActive("minimap", "MiniMap", false);
                    //InternalCalls.SetEntityIsActive("weathermap", "WeatherMap", false);
                    //InternalCalls.SetEntityIsActive("enemymap", "EnemyMap", true);
                    //InternalCalls.SetEntityIsActive("enemy", "EnemyMap", true);
                    //InternalCalls.SetEntityIsActive("player", "EnemyMap", true);
                    //for (int i = 0; i < 25; i++)
                    //{
                    //    int modI = i % 5;
                    //    int divI = i / 5;
                    //    if (modI != 0 && modI != 4 && divI != 0 && divI != 4)
                    //    {
                    //        string MIcon = "MIcon" + i;
                    //        InternalCalls.SetEntityIsActive(MIcon, "WeatherMap", false);
                    //    }
                    //}
                }
                else //if (toggle == 2)
                {
                    VI.Entity.s_Deactivate("minimap", "MiniMap");
                    VI.Entity.s_Deactivate("enemymap", "EnemyMap");
                    VI.Entity.s_Deactivate("weathermap", "WeatherMap");
                    VI.Scene.Pause("MiniMap");
                    VI.Scene.Pause("WeatherMap");
                    VI.Scene.Pause("EnemyMap");
                    //InternalCalls.SetEntityIsActive("minimap", "MiniMap", false);
                    //InternalCalls.SetEntityIsActive("weathermap", "WeatherMap", false);
                    //InternalCalls.SetEntityIsActive("enemymap", "EnemyMap", false);
                    //InternalCalls.SetEntityIsActive("enemy", "EnemyMap", false);
                    //InternalCalls.SetEntityIsActive("player", "EnemyMap", false);
                    //for (int i = 0; i < 25; i++)
                    //{
                    //    int modI = i % 5;
                    //    int divI = i / 5;
                    //    if (modI != 0 && modI != 4 && divI != 0 && divI != 4)
                    //    {
                    //        string MIcon = "MIcon" + i;
                    //        InternalCalls.SetEntityIsActive(MIcon, "WeatherMap", false);
                    //    }
                    //}
                }
                prevTog = toggle;
            }

        }

        public void FixedUpdate(int _ENTITY) {

        }

        public void LateUpdate(int _ENTITY) { }
        public void Exit(int _ENTITY) {
            toggle=0;
            prevTog = -1;
            VI.Entity.s_Deactivate("minimap", "MiniMap");
            VI.Entity.s_Deactivate("enemymap", "EnemyMap");
            VI.Entity.s_Deactivate("weathermap", "WeatherMap");
            VI.Entity.s_Deactivate("Ball", "Dialogue");
            VI.Scene.Pause("MiniMap");
            VI.Scene.Pause("WeatherMap");
            VI.Scene.Pause("EnemyMap");
        }
        public void Dead(int _ENTITY) {

        }
    }
}
