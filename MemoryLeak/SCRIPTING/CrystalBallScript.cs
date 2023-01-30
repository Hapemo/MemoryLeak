using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class CrystalBallScript
    {
        int toggle = -1; // 0 minimap, 1, weathermap, 2 enemymap
        int prevTog = -2;
        public void Init() {
            //InternalCalls.SetEntityIsActive("weathermap", "WeatherMap", false);
            //InternalCalls.SetEntityIsActive("minimap", "MiniMap", false);
            //InternalCalls.SetEntityIsActive("enemymap", "EnemyMap", false);
        }

        public void Update()
        {
            if ((InternalCalls.ButtonReleased("cyclemap", "Dialogue")) == true)
            {
                toggle = toggle >= 2 ? 0 : (toggle + 1);
            }
            if(prevTog != toggle)
            { 
                if (toggle == 0)
                {
                    InternalCalls.SetEntityIsActive("minimap", "MiniMap", true);
                    InternalCalls.SetEntityIsActive("weathermap", "WeatherMap", false);
                    InternalCalls.SetEntityIsActive("enemymap", "EnemyMap", false);
                    InternalCalls.SetEntityIsActive("enemy", "EnemyMap", false);
                    InternalCalls.SetEntityIsActive("player", "EnemyMap", false);
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
                }
                else if (toggle == 1)
                {
                    InternalCalls.SetEntityIsActive("minimap", "MiniMap", false);
                    InternalCalls.SetEntityIsActive("weathermap", "WeatherMap", true);
                    InternalCalls.SetEntityIsActive("enemymap", "EnemyMap", false);
                    InternalCalls.SetEntityIsActive("enemy", "EnemyMap", false);
                    InternalCalls.SetEntityIsActive("player", "EnemyMap", false);
                    for (int i = 0; i < 25; i++)
                    {
                        int modI = i % 5;
                        int divI = i / 5;
                        if (modI != 0 && modI != 4 && divI != 0 && divI != 4)
                        {
                            string MIcon = "MIcon" + i;
                            InternalCalls.SetEntityIsActive(MIcon, "WeatherMap", true);
                        }
                    }
                    
                }
                else if (toggle == 2)
                {
                    InternalCalls.SetEntityIsActive("minimap", "MiniMap", false);
                    InternalCalls.SetEntityIsActive("weathermap", "WeatherMap", false);
                    InternalCalls.SetEntityIsActive("enemymap", "EnemyMap", true);
                    InternalCalls.SetEntityIsActive("enemy", "EnemyMap", true);
                    InternalCalls.SetEntityIsActive("player", "EnemyMap", true);
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
                }
                else //if (toggle == 2)
                {
                    InternalCalls.SetEntityIsActive("minimap", "MiniMap", false);
                    InternalCalls.SetEntityIsActive("weathermap", "WeatherMap", false);
                    InternalCalls.SetEntityIsActive("enemymap", "EnemyMap", false);
                    InternalCalls.SetEntityIsActive("enemy", "EnemyMap", false);
                    InternalCalls.SetEntityIsActive("player", "EnemyMap", false);
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
                }
                prevTog = toggle;
            }

        }
        public void Exit() {
            toggle=0;
        }
    }
}
