using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class Mouse : BaseScript {
        private int playerBoat;

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            playerBoat = VI.Entity.GetId("Boat", VI.GameState.GetName());
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            VI.Transform.Position.SetX(_ENTITY, VI.Input.Mouse.WorldPosX() + VI.Transform.Scale.GetX(_ENTITY) / 2f);
            VI.Transform.Position.SetY(_ENTITY, VI.Input.Mouse.WorldPosY() - VI.Transform.Scale.GetY(_ENTITY) / 2f);

            if (VI.Input.Mouse.Hold()) { 
                // 
            }
            else if (VI.Input.Mouse.Press()) { 
                
            }
            else if (VI.Input.Mouse.Release()) { 
                
            }
        }

        public void FixedUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        public void LateUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public void Exit(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        public void Dead(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }
    }
}
