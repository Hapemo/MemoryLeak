/*!*****************************************************************************
\file PassengerBaseScript.cs
\author Lee Hsien Wei Joachim
\par DP email: l.hsienweijoachim@digipen.edu
\par Group: Memory Leak Studios
\date 10-03-2023
\brief
Base script for passenger control, movement and everything related to passenger
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class PassengerBaseScript : BaseScript {
        protected int playerBoat = 0;
        protected int triggerBox = 0;

        protected int correctDestination_Box = 0;
        protected int correctDestination_RenderLocation = 0;

        protected int wrongDestination_Box = 0;
        protected int wrongDestination_RenderLocation = 0;

        protected bool correctDestinationDelivery;

        protected bool ReadyToAttach;
        protected bool AttachToPlayerAnimation;
        protected bool AttachedToPlayer;
        protected bool DetachFromPlayerAnimation;
        protected bool DestinationReached;

        protected float InitialScaleX;
        protected int InitialLayerVal;

        public virtual void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            correctDestinationDelivery = false;

            ReadyToAttach = false;
            AttachToPlayerAnimation = false;
            AttachedToPlayer = false;
            DetachFromPlayerAnimation = false;
            DestinationReached = false;

            // Store original scale x value
            InitialScaleX = VI.Transform.Scale.GetX(_ENTITY);
            InitialLayerVal = VI.Texture.GetLayer(_ENTITY);
        }

        public virtual void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            correctDestinationDelivery = false;

            ReadyToAttach = false;
            AttachToPlayerAnimation = false;
            AttachedToPlayer = false;
            DetachFromPlayerAnimation = false;
            DestinationReached = false;

            // Store original scale x value
            InitialScaleX = VI.Transform.Scale.GetX(_ENTITY);
            InitialLayerVal = VI.Texture.GetLayer(_ENTITY);
        }

        public virtual void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public virtual void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        public virtual void FixedUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        public virtual void LateUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public virtual void Exit(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            
            correctDestinationDelivery = false;

            ReadyToAttach = false;
            AttachToPlayerAnimation = false;
            AttachedToPlayer = false;
            DetachFromPlayerAnimation = false;
            DestinationReached = false;
        }

        public virtual void Dead(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        // Plays animation for attaching a passsenger entity to player entity
        // Returns true once complete
        protected bool AttachPassengerToPlayer(int _ePassenger, int _ePlayer, float _passengerInitialScaleX) {
            // Get distance between passenger and boat
            float diffX = VI.Transform.Position.GetX(_ePlayer) - VI.Transform.Position.GetX(_ePassenger);
            float diffY = VI.Transform.Position.GetY(_ePlayer) - VI.Transform.Position.GetY(_ePassenger);

            if (diffX * diffX > (_passengerInitialScaleX * _passengerInitialScaleX + VI.Transform.Scale.GetX(_ePlayer) * VI.Transform.Scale.GetX(_ePlayer)) / 4f) {
                // Animation
                VI.Transform.Position.SetX(_ePassenger, VI.Transform.Position.GetX(_ePassenger) + VI.Math.Normalize.X(diffX, diffY) * 200f * (float)VI.General.DeltaTime());
                VI.Transform.Position.SetY(_ePassenger, VI.Transform.Position.GetY(_ePassenger) + VI.Math.Normalize.Y(diffX, diffY) * 200f * (float)VI.General.DeltaTime());

                //VI.Transform.Scale.SetX(_ePassenger, VI.Transform.Scale.GetX(_ePassenger) / (1 + 8 * (float)VI.General.DeltaTime()));
                //VI.Transform.Scale.SetY(_ePassenger, VI.Transform.Scale.GetY(_ePassenger) / (1 + 8 * (float)VI.General.DeltaTime()));

                return false;
            }
            else {
                return true;
            }
        }

        // Moves the passenger along with the player and updates its layer values accordingly
        protected void MovePassengerWithPlayer(int _ePassenger, int _ePlayer, float _passengerInitialScaleX) {
            // Restore passenger's original scale x value
            this.RestorePassengerScale(_ePassenger, _passengerInitialScaleX);

            // Get player's direction
            int playerDirection = VI.Animation.SpriteSheet.SheetIndex.Get(_ePlayer) % 8;
            switch (playerDirection)
            {
                case 0: // Front
                    VI.Texture.SetLayer(_ePassenger, VI.Texture.GetLayer(_ePlayer) + 1);
                    VI.Transform.Position.SetX(_ePassenger, VI.Transform.Position.GetX(_ePlayer));
                    VI.Transform.Position.SetY(_ePassenger, VI.Transform.Position.GetY(_ePlayer));
                    VI.Animation.SpriteSheet.SheetIndex.Set(_ePassenger, 6);
                    break;
                case 1: // SW
                    VI.Texture.SetLayer(_ePassenger, VI.Texture.GetLayer(_ePlayer) + 1);
                    VI.Transform.Position.SetX(_ePassenger, VI.Transform.Position.GetX(_ePlayer) - VI.Transform.Scale.GetX(_ePlayer) / 10f);
                    VI.Transform.Position.SetY(_ePassenger, VI.Transform.Position.GetY(_ePlayer));
                    VI.Animation.SpriteSheet.SheetIndex.Set(_ePassenger, 5);
                    break;
                case 2: // Left
                    VI.Texture.SetLayer(_ePassenger, VI.Texture.GetLayer(_ePlayer) + 1);
                    VI.Transform.Position.SetX(_ePassenger, VI.Transform.Position.GetX(_ePlayer) - VI.Transform.Scale.GetX(_ePlayer) / 4f);
                    VI.Transform.Position.SetY(_ePassenger, VI.Transform.Position.GetY(_ePlayer) + VI.Transform.Scale.GetY(_ePlayer) / 16f);
                    VI.Animation.SpriteSheet.SheetIndex.Set(_ePassenger, 7);
                    break;
                case 3: // NW
                    VI.Texture.SetLayer(_ePassenger, VI.Texture.GetLayer(_ePlayer) + 1);
                    VI.Transform.Position.SetX(_ePassenger, VI.Transform.Position.GetX(_ePlayer) - VI.Transform.Scale.GetX(_ePlayer) / 6f);
                    VI.Transform.Position.SetY(_ePassenger, VI.Transform.Position.GetY(_ePlayer) + VI.Transform.Scale.GetY(_ePlayer) / 8f);
                    VI.Animation.SpriteSheet.SheetIndex.Set(_ePassenger, 3);
                    break;
                case 4: // Back
                    VI.Texture.SetLayer(_ePassenger, VI.Texture.GetLayer(_ePlayer) - 1);
                    VI.Transform.Position.SetX(_ePassenger, VI.Transform.Position.GetX(_ePlayer));
                    VI.Transform.Position.SetY(_ePassenger, VI.Transform.Position.GetY(_ePlayer));
                    break;
                case 5:
                    VI.Texture.SetLayer(_ePassenger, VI.Texture.GetLayer(_ePlayer) + 1);
                    VI.Transform.Position.SetX(_ePassenger, VI.Transform.Position.GetX(_ePlayer) + VI.Transform.Scale.GetX(_ePlayer) / 6f);
                    VI.Transform.Position.SetY(_ePassenger, VI.Transform.Position.GetY(_ePlayer) + VI.Transform.Scale.GetY(_ePlayer) / 8f);
                    VI.Animation.SpriteSheet.SheetIndex.Set(_ePassenger, 2);
                    break;
                case 6: // Right
                    VI.Texture.SetLayer(_ePassenger, VI.Texture.GetLayer(_ePlayer) + 1);
                    VI.Transform.Position.SetX(_ePassenger, VI.Transform.Position.GetX(_ePlayer) + VI.Transform.Scale.GetX(_ePlayer) / 4f);
                    VI.Transform.Position.SetY(_ePassenger, VI.Transform.Position.GetY(_ePlayer) + VI.Transform.Scale.GetY(_ePlayer) / 16f);
                    VI.Animation.SpriteSheet.SheetIndex.Set(_ePassenger, 1);
                    break;
                case 7:
                    VI.Texture.SetLayer(_ePassenger, VI.Texture.GetLayer(_ePlayer) + 1);
                    VI.Transform.Position.SetX(_ePassenger, VI.Transform.Position.GetX(_ePlayer) + VI.Transform.Scale.GetX(_ePlayer) / 10f);
                    VI.Transform.Position.SetY(_ePassenger, VI.Transform.Position.GetY(_ePlayer));
                    VI.Animation.SpriteSheet.SheetIndex.Set(_ePassenger, 4);
                    break;
                default:
                    break;
            }
        }

        // Plays animation for detaching a passsenger entity from player entity to a destination entity
        // Returns true once complete
        protected bool DetachPassengerFromPlayer(int _ePassenger, int _eDestination, float _passengerInitialScaleX) {
            // Get distance between passenger and boat
            float diffX = VI.Transform.Position.GetX(_eDestination) - VI.Transform.Position.GetX(_ePassenger);
            float diffY = VI.Transform.Position.GetY(_eDestination) - VI.Transform.Position.GetY(_ePassenger);

            if (diffX * diffX > (_passengerInitialScaleX * _passengerInitialScaleX + VI.Transform.Scale.GetX(_eDestination) * VI.Transform.Scale.GetX(_eDestination)) / 3f)
            {
                // Animation
                VI.Transform.Position.SetX(_ePassenger, VI.Transform.Position.GetX(_ePassenger) + diffX * (float)VI.General.DeltaTime());
                VI.Transform.Position.SetY(_ePassenger, VI.Transform.Position.GetY(_ePassenger) + diffY * (float)VI.General.DeltaTime());

                //VI.Transform.Scale.SetX(_ePassenger, VI.Transform.Scale.GetX(_ePassenger) / (1 + 8 * (float)VI.General.DeltaTime()));
                //VI.Transform.Scale.SetY(_ePassenger, VI.Transform.Scale.GetY(_ePassenger) / (1 + 8 * (float)VI.General.DeltaTime()));
                return false;
            }
            else {
                VI.Transform.Position.SetX(_ePassenger, VI.Transform.Position.GetX(_eDestination));
                VI.Transform.Position.SetY(_ePassenger, VI.Transform.Position.GetY(_eDestination));

                return true;
            }
        }

        // Plays animation to restore passsenger entity's scale value
        // Returns true once complete
        protected bool RestorePassengerScale(int _ePassenger, float _passengerInitialScaleX) {
            //LOG.WRITE("Passenger original X: " + _passengerInitialScaleX);
            //LOG.WRITE("Current scale value: " + VI.Transform.Scale.GetX(_ePassenger));

            // Restore passenger's original scale x value
            if (VI.Transform.Scale.GetX(_ePassenger) < _passengerInitialScaleX) {
                VI.Transform.Scale.SetX(_ePassenger, VI.Transform.Scale.GetX(_ePassenger) * (1 + 8 * (float)VI.General.DeltaTime()));
                VI.Transform.Scale.SetY(_ePassenger, VI.Transform.Scale.GetY(_ePassenger) * (1 + 8 * (float)VI.General.DeltaTime()));
                return false;
            }
            else {
                return true;
            }
        }
    }
}
