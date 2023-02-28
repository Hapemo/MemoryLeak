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
        static bool big = false;
        public void Alive(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }
        public void Init(int _ENTITY) {

            VI.Entity.s_SetActive("minimapbig", "MiniMap", false);
        }

        public void Update(int _ENTITY) {
            //////////////////////////////////////////////init
            if ((VI.Input.Button.s_Released("minimap", "MiniMap")) == true)
            {
                big = !big;
                if (big)
                {
                    //VI.Entity.s_SetActive("minimapbig", "MiniMap", true);
                    VI.Animation.Transform.Start(VI.Entity.GetId("minimap", "MiniMap"));
                }
                else
                {
                    //VI.Entity.s_SetActive("minimapbig", "MiniMap", false);
                    VI.Animation.Transform.Start(VI.Entity.GetId("minimap", "MiniMap"));
                }
            }

        }

        public void Exit(int _ENTITY) {
            big = false;
            VI.Entity.s_SetActive("minimapbig", "MiniMap", false);
        }
        public void Dead(int _ENTITY)
        {

        }
    }
}
