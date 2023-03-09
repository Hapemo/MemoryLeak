﻿using System;
using System.Runtime.CompilerServices;
using VI;

namespace BonVoyage {

    public class Level1Passenger2Script : PassengerBaseScript {
        private bool ranOnceInit = true;

        public override void Alive(int _ENTITY)
        {
            base.Alive(_ENTITY);
        }
        public override void Init(int _ENTITY) {
            base.Init(_ENTITY);

            // Get required entities (ALL THESE ENTITIES NEED TO UPDATE IN Level1DialogManager.cs AS WELL IF CHANGED!!!)
            playerBoat = VI.Entity.GetId("Boat");
            triggerBox = VI.Entity.GetId("Passenger2Box");
            correctDestination_Box = VI.Entity.GetId("FountainDropOffPoint");
            correctDestination_RenderLocation = VI.Entity.GetId("FountainDestRender");

            wrongDestination_Box = VI.Entity.GetId("PortHouseDropOffPoint");
            wrongDestination_RenderLocation = VI.Entity.GetId("PortHouseDest2Render");
            // Store original scale x value
            InitialScaleX = VI.Transform.Scale.GetX(_ENTITY);
            InitialLayerVal = VI.Texture.GetLayer(_ENTITY);
        }

        public override void EarlyUpdate(int _ENTITY)
        {
            base.EarlyUpdate(_ENTITY);
        }

        public override void Update(int _ENTITY) {
            // Temporary implementation TODO change this
            if (ranOnceInit) { 
                ranOnceInit = false;

                // Get required entities (ALL THESE ENTITIES NEED TO UPDATE IN Level1DialogManager.cs AS WELL IF CHANGED!!!)
                playerBoat = VI.Entity.GetId("Boat");
                triggerBox = VI.Entity.GetId("Passenger2Box");
                correctDestination_Box = VI.Entity.GetId("FountainDropOffPoint");
                correctDestination_RenderLocation = VI.Entity.GetId("FountainDestRender");

                wrongDestination_Box = VI.Entity.GetId("PortHouseDropOffPoint");
                wrongDestination_RenderLocation = VI.Entity.GetId("PortHouseDest2Render");
                // Store original scale x value
                InitialScaleX = VI.Transform.Scale.GetX(_ENTITY);
                InitialLayerVal = VI.Texture.GetLayer(_ENTITY);
            }

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

                        // Activate the drop off point boxes
                        //VI.Entity.Activate(correctDestination_Box);
                        //VI.Entity.Activate(wrongDestination_Box);

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
            if (VI.Physics.IsCollided(correctDestination_Box, _ENTITY)) {
                // Move on to detaching animation
                AttachedToPlayer = false;
                DetachFromPlayerAnimation = true;
                PlayerScript.PlayerInOtherAnimation = true;
                Level1DialogManager.passengerDialogProgress = 21;

                // Set flag
                correctDestinationDelivery = true;
            }
            else if (VI.Physics.IsCollided(wrongDestination_Box, _ENTITY)) {
                // Move on to detaching animation
                AttachedToPlayer = false;
                DetachFromPlayerAnimation = true;
                PlayerScript.PlayerInOtherAnimation = true;
                Level1DialogManager.passengerDialogProgress = 20;

                // Set flag
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
                if (RestorePassengerScale(_ENTITY, InitialScaleX)){
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

        public override void FixedUpdate(int _ENTITY)
        {
            base.FixedUpdate(_ENTITY);
        }

        public override void LateUpdate(int _ENTITY)
        {
            base.LateUpdate(_ENTITY);
        }

        public override void Exit(int _ENTITY)
        {
            base.Exit(_ENTITY);
        }

        public override void Dead(int _ENTITY)
        {
            base.Dead(_ENTITY);
        }
    }
}
