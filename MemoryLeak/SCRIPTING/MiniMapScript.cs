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
    public class MiniMapScript : BaseScript
    {
        public override void PreInit(int _id)
        {
            var bs = new BaseScript();
            bs.PreInit(_id);
        }

        static bool init = true;
        static bool big = false;
        public void Init(int _id) {

            InternalCalls.SetEntityIsActive("minimapbig", "MiniMap", false);
        }

        public void Update(int _id) {
            if (init)
            {
                init = false;
                
            }
            //////////////////////////////////////////////init
            if ((InternalCalls.ButtonReleased("minimap", "MiniMap")) == true)
            {
                big = !big;
                if (big)
                {
                    InternalCalls.SetEntityIsActive("minimapbig", "MiniMap", true);
                }
                else
                {
                    InternalCalls.SetEntityIsActive("minimapbig", "MiniMap", false);
                }
            }

        }

        public void Exit(int _id) {
            big = false;
            InternalCalls.SetEntityIsActive("minimapbig", "MiniMap", false);
        }
    }
}
