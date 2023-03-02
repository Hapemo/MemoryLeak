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
        static bool big = false;
        static bool active = true;
        int playerID;
        int rainID;
        public void Alive(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            playerID = VI.Entity.GetId("Boat", "Level1");
            rainID = VI.Entity.GetId("rain", "Level1");
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            
            VI.Entity.s_Deactivate("crystalBall", "CrystalBalls");
        }

        public void Update(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            VI.Entity.s_Activate("crystalBall", "CrystalBalls");
            if ((VI.Input.Button.s_Released("toggleMap", "CrystalBalls")) == true)
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
                    
                }
                else if (toggle == 1)
                {
                    VI.Entity.s_Deactivate("minimap", "MiniMap");
                    VI.Entity.s_Deactivate("enemymap", "EnemyMap");
                    VI.Scene.Pause("MiniMap");
                    VI.Scene.Play("WeatherMap");
                    VI.Entity.s_Activate("weathermap", "WeatherMap");
                    VI.Scene.Pause("EnemyMap");
                    

                }
                else if (toggle == 2)
                {
                    VI.Entity.s_Deactivate("minimap", "MiniMap");
                    VI.Entity.s_Deactivate("weathermap", "WeatherMap");
                    VI.Scene.Pause("MiniMap");
                    VI.Scene.Pause("WeatherMap");
                    VI.Scene.Play("EnemyMap");
                    VI.Entity.s_Activate("enemymap", "EnemyMap");
                    
                }
                else //if (toggle == 3)
                {
                    VI.Entity.s_Deactivate("minimap", "MiniMap");
                    VI.Entity.s_Deactivate("enemymap", "EnemyMap");
                    VI.Entity.s_Deactivate("weathermap", "WeatherMap");
                    VI.Scene.Pause("MiniMap");
                    VI.Scene.Pause("WeatherMap");
                    VI.Scene.Pause("EnemyMap");
                    
                }
                prevTog = toggle;
            }
            int index = VI.Weather.GetCurrent(12,
                    VI.Transform.Scale.GetY(playerID), VI.Transform.Scale.GetY(playerID));
            if(index == 1 || index == 3 || index == 7)
            {
                VI.Entity.SetActive(rainID, true);
                VI.Transform.Position.SetX(rainID, VI.Transform.Position.GetX(playerID));
                VI.Transform.Position.SetY(rainID, VI.Transform.Position.GetY(playerID));
            }
            else
            {
                VI.Entity.SetActive(rainID, false);
            }

        }
        public void Exit(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            toggle=0;
            prevTog = -1;
            VI.Entity.s_Deactivate("minimap", "MiniMap");
            VI.Entity.s_Deactivate("enemymap", "EnemyMap");
            VI.Entity.s_Deactivate("weathermap", "WeatherMap");
            VI.Entity.s_Deactivate("crystalBall", "CrystalBalls");
            VI.Scene.Pause("MiniMap");
            VI.Scene.Pause("WeatherMap");
            VI.Scene.Pause("EnemyMap");
        }
        public void Dead(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }
    }
}
