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
        static bool big = false;

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void Init(int _ENTITY) {

            VI.Entity.SetActive("minimapbig", "MiniMap", false);
        }

        public void Update(int _ENTITY) {
            if (init)
            {
                init = false;
                
            }
            //////////////////////////////////////////////init
            if ((VI.Input.Button.Released("minimap", "MiniMap")) == true)
            {
                big = !big;
                if (big)
                {
                    VI.Entity.SetActive("minimapbig", "MiniMap", true);
                }
                else
                {
                    VI.Entity.SetActive("minimapbig", "MiniMap", false);
                }
            }

        }

        public void FixedUpdate(int _ENTITY) {

        }

        public void Exit(int _ENTITY) {
            big = false;
            VI.Entity.SetActive("minimapbig", "MiniMap", false);
        }

        public void Dead(int _ENTITY) {

        }
    }
}
