/*!*****************************************************************************
\file Level2Passenger2Script.cs
\author Lee Hsien Wei Joachim
\par DP email: l.hsienweijoachim@digipen.edu
\par Group: Memory Leak Studios
\date 10-03-2023
\brief
Level2Passenger2Script contains the logic that handles the logic of the animation
calls of the second passenger in the second level and setting the level's dialog
manager variable to true when the player collides with its trigger box
*******************************************************************************/

using System;
using System.Runtime.CompilerServices;
using VI;

namespace BonVoyage {

    public class Level2Passenger2Script : PassengerBaseScript {
    bool runOnce = true;
        public override void Alive(int _ENTITY)
        {
            base.Alive(_ENTITY);
        }

        public override void Init(int _ENTITY) {
            base.Init(_ENTITY);

            // Get required entities
            playerBoat                          = VI.Entity.GetId("Boat");
            triggerBox                          = VI.Entity.GetId(Level2DialogManager.P2BoxString);

            correctDestination_Box              = VI.Entity.GetId(Level2DialogManager.P2CorrectBoxString);
            correctDestination_RenderLocation   = VI.Entity.GetId(Level2DialogManager.P2CorrectRenderString);

            wrongDestination_Box                = VI.Entity.GetId(Level2DialogManager.P2WrongBoxString);
            wrongDestination_RenderLocation     = VI.Entity.GetId(Level2DialogManager.P2WrongRenderString);
        }

        public override void EarlyUpdate(int _ENTITY)
        {
            base.EarlyUpdate(_ENTITY);
        }

        public override void Update(int _ENTITY) {
            base.Update(_ENTITY);
            if (runOnce) { runOnce = false; Init(_ENTITY); }

      //if (playerBoat == 0) LOG.WRITE("playerBoat========================");
      //if (triggerBox == 0) LOG.WRITE("triggerBox========================");
      //if (correctDestination_Box == 0) LOG.WRITE("correctDestination_Box========================");
      //if (correctDestination_RenderLocation == 0) LOG.WRITE("correctDestination_RenderLocation========================");
      //if (wrongDestination_Box == 0) LOG.WRITE("wrongDestination_Box========================");
      //if (wrongDestination_RenderLocation == 0) LOG.WRITE("wrongDestination_RenderLocation========================");

            // Check if passenger's trigger box is active
            if (triggerBox != 0)
            if (VI.Entity.IsActive(triggerBox)) {
                // Check if player is colliding with that box
                if (VI.Physics.IsCollided(triggerBox, playerBoat)) {
                    // Check if dialogue script should be ran
                    if (!Level2DialogManager.runPassenger2Dialog) {
                        // Set Dialogue Manager's flag to true to run it
                        Level2DialogManager.runPassenger2Dialog = true;
                        
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
            if (ReadyToAttach && !Level2DialogManager.runPassenger2Dialog) {
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



            // Check if passenger reaches destination
            if (VI.Physics.IsCollided(correctDestination_Box, _ENTITY)) {
                // Move on to detaching animation
                AttachedToPlayer = false;
                DetachFromPlayerAnimation = true;
                PlayerScript.PlayerInOtherAnimation = true;
                Level2DialogManager.passengerDialogProgress = 21;

                // Set flag
                correctDestinationDelivery = true;
            }
            else if (VI.Physics.IsCollided(wrongDestination_Box, _ENTITY)) {
                // Move on to detaching animation
                AttachedToPlayer = false;
                DetachFromPlayerAnimation = true;
                PlayerScript.PlayerInOtherAnimation = true;
                Level2DialogManager.passengerDialogProgress = 20;

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

            // Move passenger with player       
            if (AttachedToPlayer)
            {
                // Move passenger with player
                MovePassengerWithPlayer(_ENTITY, playerBoat, InitialScaleX);
            }
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