using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class MiniMapScript
    {
        static bool init = true;
        static bool big = false;
        public void Init() {

            InternalCalls.SetEntityIsActive("minimapbig", "MiniMap", false);
        }

        public void Update() {
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

        public void Exit() {
            big = false;
            InternalCalls.SetEntityIsActive("minimapbig", "MiniMap", false);
        }
    }
}
