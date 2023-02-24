using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class FragmentScript
    {
        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY);
        }

        public void Init(int _ENTITY) {
            
        }

        public void Update(int _ENTITY) {
            //if (VI.Physics.s_EntitiesCollided("Boat", "fragment1drop", "Level1"))
            //{ 

            //}
        }

        public void EarlyUpdate(int _ENTITY) { }

        public void FixedUpdate(int _ENTITY) {

        }

        public void LateUpdate(int _ENTITY) { }

        public void Exit(int _ENTITY) {

        }

        public void Dead(int _ENTITY) {

        }
    }
}
