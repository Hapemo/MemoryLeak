using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class EnemyMapScript
    {
        public void Init() {
        }

        public void Update() {
            InternalCalls.EntityDeactivate("enemymap", "EnemyMap");
            InternalCalls.EntityDeactivate("enemymapbig", "EnemyMap");
            
        }

        public void Exit() {
            
        }
    }
}
