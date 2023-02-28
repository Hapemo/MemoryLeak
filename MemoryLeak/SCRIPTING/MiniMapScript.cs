/*!*****************************************************************************
\file MiniMapScript.cs
\author Huang Wei Jhin
\par DP email: h.weijhin\@digipen.edu
\par Group: Memory Leak Studios
\date 28-01-2023
\brief
MiniMapScript contains multiple script components to run the Level1 of the game.
Part of which are:
- Functions of the minimap
- Expanding the minimap
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class MiniMapScript
    {
        static bool init = true;

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            VI.Entity.s_SetActive("minimapbig", "WeatherMap", false);
            VI.Entity.s_SetActive("minimap", "WeatherMap", false);
            VI.Entity.s_SetActive("minimaphead", "WeatherMap", false);
        }

        public void Init(int _ENTITY) {
            VI.Entity.s_SetActive("minimap", "WeatherMap", true);
            VI.Entity.s_SetActive("minimapbig", "WeatherMap", true);
            VI.Entity.s_SetActive("minimaphead", "WeatherMap", true);

        }

        public void EarlyUpdate(int _ENTITY) { }

        public void Update(int _ENTITY) {
            if (init)
            {
                init = false;
                
            }
            //////////////////////////////////////////////init
            VI.Entity.s_SetActive("minimaphead", "WeatherMap", true);
            VI.Entity.s_SetActive("minimap", "WeatherMap", true);

            ///
            if (CrystalBallScript.Big())
            {
                VI.Entity.s_SetActive("minimapbig", "WeatherMap", true);
            }
            else
            {
                VI.Entity.s_SetActive("minimapbig", "WeatherMap", false);
            }

        }

        public void FixedUpdate(int _ENTITY) {

        }

        public void LateUpdate(int _ENTITY) { }

        public void Exit(int _ENTITY) {
            VI.Entity.s_SetActive("minimap", "WeatherMap", false);
            VI.Entity.s_SetActive("minimapbig", "WeatherMap", false);
            VI.Entity.s_SetActive("minimaphead", "WeatherMap", false);

        }

        public void Dead(int _ENTITY) {

        }
    }
}
