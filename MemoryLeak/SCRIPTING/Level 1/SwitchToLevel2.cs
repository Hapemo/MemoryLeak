using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class SwitchToLevel2 : BaseScript
    {
        private int playerBoat;
        private bool ranOnceInit = true;

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            playerBoat = VI.Entity.GetId("Boat", "Level1");
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            playerBoat = VI.Entity.GetId("Boat", "Level1");
        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void Update(int _ENTITY) {
            // Temporary implementation TODO change this
            if (ranOnceInit) {
                ranOnceInit = false;
                
                playerBoat = VI.Entity.GetId("Boat", "Level1");
            }

            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            if (VI.Physics.IsCollided(_ENTITY, playerBoat) && PassengerDeliverUI.DelieveredAllPassengers()) {
                TransitionSquare.FadeOut("Level2");
                //VI.GameState.Go("Level1");
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
