﻿using System;
using System.Runtime.CompilerServices;
using VI;

namespace BonVoyage {

    public class Level1Passenger1Script : PassengerBaseScript {
        public override void Init(int _ENTITY) {
            base.Init(_ENTITY);

            // Find required entities
            playerBoat = VI.Entity.GetId("Boat", "Level1");
            triggerBox = VI.Entity.GetId("Passenger1Box", "Level1");
            
            correctDestination_Box = VI.Entity.GetId("DoubleStoryHouseDropOffPoint", "Level1");
            correctDestination_RenderLocation = VI.Entity.GetId("DoubleStoryHouseDestRender", "Level1");

            wrongDestination_Box = VI.Entity.GetId("LighthouseDropOffPoint", "Level1");
            wrongDestination_RenderLocation = VI.Entity.GetId("LighthouseDestRender", "Level1");

            // Store original scale and layer values
            //InitialScaleX = VI.Transform.Scale.GetX(_ENTITY);
            //InitialLayerVal = VI.Texture.GetLayer(_ENTITY);
        }

        public override void Update(int _ENTITY) {
            base.Update(_ENTITY);

            // Check if passenger's trigger box is active
            if (VI.Entity.IsActive(triggerBox)) {
                // Check if player is colliding with that box
                if (VI.Physics.IsCollided(triggerBox, playerBoat)) {
                    // Check if dialogue script should be ran
                    if (!Level1DialogManager.runPassengerDialog) {
                        // Set Dialogue Manager's flag to true to run it
                        Level1DialogManager.runPassengerDialog = true;
                        
                        // Deactivate the trigger box
                        VI.Entity.Deactivate(triggerBox);

                        // Activate the drop off point boxes
                        VI.Entity.Activate(correctDestination_Box);
                        VI.Entity.Activate(wrongDestination_Box);
                        
                        // Set flag to true
                        ReadyToAttach = true;
                    }
                }
            }

            // Passenger is ready to attach & dialogue has ended
            if (ReadyToAttach && !Level1DialogManager.runPassengerDialog) {
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

            // Check if passenger reaches destination A
            if (VI.Physics.IsCollided(correctDestination_Box, _ENTITY)) {
                // Move on to detaching animation
                AttachedToPlayer = false;
                DetachFromPlayerAnimation = true;
                PlayerScript.PlayerInOtherAnimation = true;
                Level1DialogManager.passengerDialogProgress = 11;

                // Set flag variable
                correctDestinationDelivery = true;
            }
            // Check if passenger reaches destination B
            else if (VI.Physics.IsCollided(wrongDestination_Box, _ENTITY)) {
                // Move on to detaching animation
                AttachedToPlayer = false;
                DetachFromPlayerAnimation = true;
                PlayerScript.PlayerInOtherAnimation = true;
                Level1DialogManager.passengerDialogProgress = 10;

                // Set flag variable
                correctDestinationDelivery = false;
            }

            // Play animation of passenger detaching from player
            if (DetachFromPlayerAnimation) {
                // Animate detachment to player
                // returns true once complete
                int renderLocation = correctDestinationDelivery ? correctDestination_RenderLocation : wrongDestination_RenderLocation;
                if (DetachPassengerFromPlayer(_ENTITY, renderLocation, InitialScaleX)) {
                    // Animation complete
                    DetachFromPlayerAnimation = false;
                    PlayerScript.PlayerInOtherAnimation = false;
                    DestinationReached = true;
                }                
            }

            // Passenger was delivered
            if (DestinationReached) {
                // Return layer value
                VI.Texture.SetLayer(_ENTITY, InitialLayerVal);

                

                // Restore passenger's original scale value
                // Returns true when completed
                if (RestorePassengerScale(_ENTITY, InitialScaleX)) {

                    // Run logic based on whether destination delievered was correct
                    switch (correctDestinationDelivery) {
                        case true:
                            // Run second script/logic from here

                            break;
                        case false:
                            // Run second script/logic from here

                            break;
                        default:
                            // Do nothing
                            break;
                    }

                    // Deactivate the drop off point boxes
                    VI.Entity.Deactivate(correctDestination_Box);
                    VI.Entity.Deactivate(wrongDestination_Box);

                    // Set flag to get out
                    DestinationReached = false;
                }
            }
        }
    }
}
