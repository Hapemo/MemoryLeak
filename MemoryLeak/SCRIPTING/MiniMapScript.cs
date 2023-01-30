using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class MiniMapScript
    {
        public void Init() {
        }

        public void Update() {
            InternalCalls.EntityDeactivate("minimap", "MiniMap");
            InternalCalls.EntityDeactivate("minimapbig", "MiniMap");
            
        }

        public void Exit() {
            
        }
    }
}
