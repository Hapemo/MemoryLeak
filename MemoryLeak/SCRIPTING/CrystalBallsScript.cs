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
        int crystalBallID;
        int toggleMapID;
        int minimapID;
        int weathermapID;
        int enemymapID;
        string currlevel;
        string currlevelBG;
        public void Alive(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            currlevel = VI.GameState.GetName();
            currlevelBG = currlevel + "Background";
            //if (currlevel == "Level1")
            playerID = VI.Entity.GetId("Boat", currlevel);
            rainID = VI.Entity.GetId("rain", currlevelBG);
            crystalBallID = VI.Entity.GetId("crystalBall", "CrystalBalls");
            toggleMapID = VI.Entity.GetId("toggleMap", "CrystalBalls");
            minimapID = VI.Entity.GetId("minimap", "MiniMap");
            weathermapID = VI.Entity.GetId("weathermap", "WeatherMap");
            enemymapID = VI.Entity.GetId("enemymap", "EnemyMap");
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            toggle = 0;
            prevTog = -1;
            VI.Entity.Activate(crystalBallID);
        }

        public void Update(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            if ((VI.Input.Button.Released(toggleMapID)) == true)
            {
                toggle = toggle >= 2 ? 0 : (toggle + 1);
                if (currlevel == "Level1" && toggle == 2)
                    toggle = 0;
            }
            if(prevTog != toggle)
            { 
                if (toggle == 0)
                {
                    VI.Entity.Deactivate(weathermapID);
                    VI.Entity.Deactivate(enemymapID);
                    VI.Scene.Play("MiniMap");
                    VI.Entity.Activate(minimapID);
                    VI.Scene.Pause("WeatherMap");
                    VI.Scene.Pause("EnemyMap");
                    
                }
                else if (toggle == 1)
                {
                    VI.Entity.Deactivate(minimapID);
                    VI.Entity.Deactivate(enemymapID);
                    VI.Scene.Pause("MiniMap");
                    VI.Scene.Play("WeatherMap");
                    VI.Entity.Activate(weathermapID);
                    VI.Scene.Pause("EnemyMap");
                    

                }
                else if (toggle == 2)
                {
                    VI.Entity.Deactivate(minimapID);
                    VI.Entity.Deactivate(weathermapID);
                    VI.Scene.Pause("MiniMap");
                    VI.Scene.Pause("WeatherMap");
                    VI.Scene.Play("EnemyMap");
                    VI.Entity.Activate(enemymapID);
                    
                }
                else //if (toggle == 3)
                {
                    VI.Entity.Deactivate(minimapID);
                    VI.Entity.Deactivate(enemymapID);
                    VI.Entity.Deactivate(weathermapID);
                    VI.Scene.Pause("MiniMap");
                    VI.Scene.Pause("WeatherMap");
                    VI.Scene.Pause("EnemyMap");
                    
                }
                prevTog = toggle;
            }
            int index = VI.Weather.GetCurrent(12, VI.Transform.Scale.GetY(playerID), VI.Transform.Scale.GetY(playerID));
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
            VI.Entity.Deactivate(crystalBallID);
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
