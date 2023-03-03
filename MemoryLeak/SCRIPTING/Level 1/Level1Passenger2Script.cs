using System;
using System.Runtime.CompilerServices;
using VI;

namespace BonVoyage {

    public class Level1Passenger2Script : BaseScript {
    private int playerBoat;
    private int triggerBox;
    private int destinationBox;
    private int destinationRenderLocation;

    private bool ReadyToAttach;
    private bool AttachToPlayerAnimation;
    private bool AttachedToPlayer;
    private bool DetachFromPlayerAnimation;
    private bool DestinationReached;

    private float InitialScaleX;

    public void Alive(int _ENTITY) {
        THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        playerBoat = VI.Entity.GetId("Boat", "Level1");
        triggerBox = VI.Entity.GetId("Passenger2Box", "Level1");
        destinationBox = VI.Entity.GetId("destination", "Level1");
        destinationRenderLocation = VI.Entity.GetId("Passenger2DestRender", "Level1");

        ReadyToAttach = false;
        AttachToPlayerAnimation = false;
        AttachedToPlayer = false;
        DetachFromPlayerAnimation = false;
        DestinationReached = false;

        // Store original scale x value
        InitialScaleX = VI.Transform.Scale.GetX(_ENTITY);
    }

    public void Init(int _ENTITY) {

    }

    public void Update(int _ENTITY) {
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
            // Get distance between passenger and boat
            float diffX = VI.Transform.Position.GetX(playerBoat) - VI.Transform.Position.GetX(_ENTITY);
            float diffY = VI.Transform.Position.GetY(playerBoat) - VI.Transform.Position.GetY(_ENTITY);

            if (diffX * diffX > (InitialScaleX * InitialScaleX + VI.Transform.Scale.GetX(playerBoat) * VI.Transform.Scale.GetX(playerBoat)) / 3f) {
                // Animation
                VI.Transform.Position.SetX(_ENTITY, VI.Transform.Position.GetX(_ENTITY) + VI.Math.Normalize.X(diffX, diffY) * 200f * (float)VI.General.DeltaTime());
                VI.Transform.Position.SetY(_ENTITY, VI.Transform.Position.GetY(_ENTITY) + VI.Math.Normalize.Y(diffX, diffY) * 200f * (float)VI.General.DeltaTime());

                VI.Transform.Scale.SetX(_ENTITY, VI.Transform.Scale.GetX(_ENTITY) / (1 + 8 * (float)VI.General.DeltaTime()));
                VI.Transform.Scale.SetY(_ENTITY, VI.Transform.Scale.GetY(_ENTITY) / (1 + 8 * (float)VI.General.DeltaTime()));
            }
            else {
                // Move on to passenger moving with the player
                AttachedToPlayer = true;
                AttachToPlayerAnimation = false;
                PlayerScript.PlayerInOtherAnimation = false;
            }
        }

        // Move passenger with player       
        if (AttachedToPlayer) {
            // Restore passenger's original scale x value
            if (VI.Transform.Scale.GetX(_ENTITY) < InitialScaleX) {
                VI.Transform.Scale.SetX(_ENTITY, VI.Transform.Scale.GetX(_ENTITY) * (1 + 8 * (float)VI.General.DeltaTime()));
                VI.Transform.Scale.SetY(_ENTITY, VI.Transform.Scale.GetY(_ENTITY) * (1 + 8 * (float)VI.General.DeltaTime()));
            }

            // Get player's direction
            int playerDirection = VI.Animation.SpriteSheet.SheetIndex.Get(playerBoat) % 8;
            switch (playerDirection) { 
            case 0: // Front
                VI.Transform.Position.SetX(_ENTITY, VI.Transform.Position.GetX(playerBoat));
                VI.Transform.Position.SetY(_ENTITY, VI.Transform.Position.GetY(playerBoat));
                break;
            case 1:
                VI.Transform.Position.SetX(_ENTITY, VI.Transform.Position.GetX(playerBoat) - VI.Transform.Scale.GetX(playerBoat) / 10f);
                VI.Transform.Position.SetY(_ENTITY, VI.Transform.Position.GetY(playerBoat));
                break;
            case 2: // Left
                VI.Transform.Position.SetX(_ENTITY, VI.Transform.Position.GetX(playerBoat) - VI.Transform.Scale.GetX(playerBoat) / 4f);
                VI.Transform.Position.SetY(_ENTITY, VI.Transform.Position.GetY(playerBoat) + VI.Transform.Scale.GetY(playerBoat) / 16f);
                break;
            case 3:
                VI.Transform.Position.SetX(_ENTITY, VI.Transform.Position.GetX(playerBoat) - VI.Transform.Scale.GetX(playerBoat) / 6f);
                VI.Transform.Position.SetY(_ENTITY, VI.Transform.Position.GetY(playerBoat) + VI.Transform.Scale.GetY(playerBoat) / 8f);
                break;
            case 4: // Back
                VI.Transform.Position.SetX(_ENTITY, VI.Transform.Position.GetX(playerBoat));
                VI.Transform.Position.SetY(_ENTITY, VI.Transform.Position.GetY(playerBoat));
                break;
            case 5:
                VI.Transform.Position.SetX(_ENTITY, VI.Transform.Position.GetX(playerBoat) + VI.Transform.Scale.GetX(playerBoat) / 6f);
                VI.Transform.Position.SetY(_ENTITY, VI.Transform.Position.GetY(playerBoat) + VI.Transform.Scale.GetY(playerBoat) / 8f);
                break;
            case 6: // Right
                VI.Transform.Position.SetX(_ENTITY, VI.Transform.Position.GetX(playerBoat) + VI.Transform.Scale.GetX(playerBoat) / 4f);
                VI.Transform.Position.SetY(_ENTITY, VI.Transform.Position.GetY(playerBoat) + VI.Transform.Scale.GetY(playerBoat) / 16f);
                break;
            case 7:
                VI.Transform.Position.SetX(_ENTITY, VI.Transform.Position.GetX(playerBoat) + VI.Transform.Scale.GetX(playerBoat) / 10f);
                VI.Transform.Position.SetY(_ENTITY, VI.Transform.Position.GetY(playerBoat));
                break;  
            default:
                break;
            }
        }

        // Check if passenger reaches destination
        if (VI.Physics.CheckCollision(destinationBox, _ENTITY, false)) {
            // Move on to detaching animation
            AttachedToPlayer = false;
            DetachFromPlayerAnimation = true;
            PlayerScript.PlayerInOtherAnimation = true;
        }

        // Play animation of passenger detaching from player
        if (DetachFromPlayerAnimation) {
            // Get distance between passenger and boat
            float diffX = VI.Transform.Position.GetX(destinationRenderLocation) - VI.Transform.Position.GetX(_ENTITY);
            float diffY = VI.Transform.Position.GetY(destinationRenderLocation) - VI.Transform.Position.GetY(_ENTITY);

            if (diffX * diffX > (InitialScaleX * InitialScaleX + VI.Transform.Scale.GetX(destinationRenderLocation) * VI.Transform.Scale.GetX(destinationRenderLocation)) / 3f) { 
                // Animation
                VI.Transform.Position.SetX(_ENTITY, VI.Transform.Position.GetX(_ENTITY) + diffX * (float)VI.General.DeltaTime());
                VI.Transform.Position.SetY(_ENTITY, VI.Transform.Position.GetY(_ENTITY) + diffY * (float)VI.General.DeltaTime());

                VI.Transform.Scale.SetX(_ENTITY, VI.Transform.Scale.GetX(_ENTITY) / (1 + 8 * (float)VI.General.DeltaTime()));
                VI.Transform.Scale.SetY(_ENTITY, VI.Transform.Scale.GetY(_ENTITY) / (1 + 8 * (float)VI.General.DeltaTime()));
            }
            else {
                // Animation complete
                DetachFromPlayerAnimation = false;
                PlayerScript.PlayerInOtherAnimation = false;
                DestinationReached = true;
            }

        }
        
        if (DestinationReached) {
            // Restore passenger's original scale x value
            if (VI.Transform.Scale.GetX(_ENTITY) < InitialScaleX) {
                VI.Transform.Scale.SetX(_ENTITY, VI.Transform.Scale.GetX(_ENTITY) * (1 + 8 * (float)VI.General.DeltaTime()));
                VI.Transform.Scale.SetY(_ENTITY, VI.Transform.Scale.GetY(_ENTITY) * (1 + 8 * (float)VI.General.DeltaTime()));
            }

            // Get distance between passenger and boat
            float diffX = VI.Transform.Position.GetX(destinationRenderLocation) - VI.Transform.Position.GetX(_ENTITY);
            float diffY = VI.Transform.Position.GetY(destinationRenderLocation) - VI.Transform.Position.GetY(_ENTITY);

            if (diffX * diffX > (InitialScaleX * InitialScaleX + VI.Transform.Scale.GetX(destinationRenderLocation) * VI.Transform.Scale.GetX(destinationRenderLocation))) {
                // Animation
                VI.Transform.Position.SetX(_ENTITY, VI.Transform.Position.GetX(_ENTITY) + diffX * (float)VI.General.DeltaTime());
                VI.Transform.Position.SetY(_ENTITY, VI.Transform.Position.GetY(_ENTITY) + diffY * (float)VI.General.DeltaTime());
            }
            else { 
                DestinationReached = false;
            }
        }
    }

    public void FixedUpdate(int _ENTITY) {

    }

    public void Exit(int _ENTITY) {

    }

    public void Dead(int _ENTITY) {

    }

    }
}
