using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class LevelTutorialPassengerScript : PassengerBaseScript {
        public override void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            // Find required entities
            playerBoat = VI.Entity.GetId("Boat", "LevelTutorial");
            triggerBox = VI.Entity.GetId("PassengerPickupBox", "LevelTutorial");

            correctDestination_Box = VI.Entity.GetId("", "");
            correctDestination_RenderLocation = VI.Entity.GetId("", "");

            // Store original scale and layer values
            InitialScaleX = VI.Transform.Scale.GetX(_ENTITY);
            InitialLayerVal = VI.Texture.GetLayer(_ENTITY);
        }

        public override void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            // Check if passenger's trigger box is active
            if (VI.Entity.IsActive(triggerBox)) { 
                // Check if player is colliding with that box
                if (VI.Physics.IsCollided(triggerBox, playerBoat)) { 
                    // Check if dialogue script should be rAn
                    //if (){
                    
                    //}
                }
            }
        }
    }
}
