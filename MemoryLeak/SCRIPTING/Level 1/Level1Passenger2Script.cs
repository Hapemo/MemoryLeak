﻿using System;
using System.Runtime.CompilerServices;
using VI;

namespace BonVoyage {

    public class Level1Passenger2Script : PassengerBaseScript {
        public override void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            // Get required entities
            playerBoat = VI.Entity.GetId("Boat", "Level1");
            triggerBox = VI.Entity.GetId("Passenger2Box", "Level1");
            destinationA_Box = VI.Entity.GetId("DoubleStoryDropOffPoint", "Level1");
            destinationA_RenderLocation = VI.Entity.GetId("DoubleStoryDestRender", "Level1");

            destinationB_Box = VI.Entity.GetId("PortHouseDropOffPoint", "Level1");
            destinationB_RenderLocation = VI.Entity.GetId("PortHouseDestRender", "Level1");

            // Store original scale x value
            InitialScaleX = VI.Transform.Scale.GetX(_ENTITY);
            InitialLayerVal = VI.Texture.GetLayer(_ENTITY);
        }

        public override void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            // Check if passenger's trigger box is active
            if (VI.Entity.IsActive(triggerBox)) {
                // Check if player is colliding with that box
                if (VI.Physics.IsCollided(triggerBox, playerBoat)) {
                    // Check if dialogue script should be ran
                    if (!Level1DialogManager.runPassenger2Dialog) {
                        // Set Dialogue Manager's flag to true to run it
                        Level1DialogManager.runPassenger2Dialog = true;
                        // Deactivate the trigger box
                        VI.Entity.Deactivate(triggerBox);
                        // Set flag to true
                        ReadyToAttach = true;
                    }
                }
            }

            // Passenger is ready to attach & dialogue has ended
            if (ReadyToAttach && !Level1DialogManager.runPassenger2Dialog) {
                // Set flag variables
                AttachToPlayerAnimation = true;
                PlayerScript.PlayerInOtherAnimation = true;
                ReadyToAttach = false;
            }

            // For transition of passenger location to player's boat, to use particle system to indicate the transfer

            // Play animation of passenger attaching to player
            if (AttachToPlayerAnimation) {
                // Animate attachment to player
                // returns true once complete
                if (AttachPassengerToPlayer(_ENTITY, playerBoat, InitialScaleX)) {
                    // Move on to passenger moving with the player
                    AttachedToPlayer = true;
                    AttachToPlayerAnimation = false;
                    PlayerScript.PlayerInOtherAnimation = false;
                }
            }

            // Move passenger with player       
            if (AttachedToPlayer) {
                // Move passenger with player
                MovePassengerWithPlayer(_ENTITY, playerBoat, InitialScaleX);
            }

            // Check if passenger reaches destination
            if (VI.Physics.CheckCollision(destinationA_Box, _ENTITY, false)) {
                // Move on to detaching animation
                AttachedToPlayer = false;
                DetachFromPlayerAnimation = true;
                PlayerScript.PlayerInOtherAnimation = true;
            }

            // Play animation of passenger detaching from player
            if (DetachFromPlayerAnimation) {
                // Animate detachment to player
                // returns true once complete
                if (DetachPassengerFromPlayer(_ENTITY, destinationA_RenderLocation, InitialScaleX)) {
                    // Animation complete
                    DetachFromPlayerAnimation = false;
                    PlayerScript.PlayerInOtherAnimation = false;
                    DestinationReached = true;
                }

            }
        
            if (DestinationReached) {
                VI.Texture.SetLayer(_ENTITY, InitialLayerVal);

                // Restore passenger's original scale value
                if (RestorePassengerScale(_ENTITY, InitialScaleX)){
                    DestinationReached = false;
                }
            }
        }
    }
}
