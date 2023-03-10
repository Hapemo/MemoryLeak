/*!*****************************************************************************
\file MoveToCat.cs
\author Lee Hsien Wei Joachim
\par DP email: l.hsienweijoachim@digipen.edu
\par Group: Memory Leak Studios
\date 10-03-2023
\brief
MoveToCat contains the logic that handles auto movement of the player after the
introductory dialogue of the player monologue-ing. 
(Does not work currently due to it querying a non-existent entity component)
*******************************************************************************/

using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class MoveToCat : BaseScript
    {
        private int playerBoat;
        private int catBox;

        private bool MovePlayer;

        private bool init = true;
        private double DelayActivation = 1f;

        private const float PlayerSpeed = 10f;
        private const double Pi = 3.141592653589793238f;
        private const float MiniAngle = (float)Pi / 8;

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            playerBoat = VI.Entity.GetId("Boat");
            catBox = VI.Entity.GetId("CatBox");

            MovePlayer = false;
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            playerBoat = VI.Entity.GetId("Boat");
            catBox = VI.Entity.GetId("CatBox");

            MovePlayer = false;
        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public void Update(int _ENTITY) {
            if (init)
            {
                playerBoat = VI.Entity.GetId("Boat");
                catBox = VI.Entity.GetId("CatBox");

                MovePlayer = false;

                init = false;
            }

            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            if (DelayActivation >= 0f)
                DelayActivation -= VI.General.DeltaTime();

            if (VI.Input.Mouse.Release())
            {
                if (DelayActivation < 0f)
                {
                    MovePlayer = true;
                    PlayerScript.PlayerInDialogue = true;
                }
            }

        }

        public void FixedUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!


            if (MovePlayer)
            {
                float DirX = VI.Transform.Position.GetX(catBox) - VI.Transform.Position.GetX(playerBoat);
                float DirY = VI.Transform.Position.GetY(catBox) - VI.Transform.Position.GetY(playerBoat);

                float totalScaleX = VI.Transform.Scale.GetX(catBox) / 2f + VI.Transform.Scale.GetX(playerBoat) / 2f;
                float totalScaleY = VI.Transform.Scale.GetY(catBox) / 2f + VI.Transform.Scale.GetY(playerBoat) / 2f;

                if (DirX * DirX >= totalScaleX * totalScaleX || DirY * DirY >= totalScaleY * totalScaleY) {

                    float NormX = VI.Math.Normalize.X(DirX, DirY);
                    float NormY = VI.Math.Normalize.Y(DirX, DirY);
                    ApplyForce(playerBoat, NormX, NormY, PlayerSpeed);

                    // Get new rotation and set sprite
                    SetPlayerSprite(playerBoat, GetRotation(NormX, NormY), "Idle");
                }
                else
                {
                    MovePlayer = false;
                    VI.Entity.Deactivate(_ENTITY);
                }
            }
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

        private void ApplyForce(int _eID, float _x, float _y, float _multiplier)
        {
            VI.Physics.ApplyImpulse(_eID,
                (_x * _multiplier),
                (_y * _multiplier), 0f, 0f);
        }
        private float GetRotation(float _x, float _y)
        {
            float Rotation = 0;
            if (_y != 0f && _x >= 0f)
                Rotation = VI.Math.ArcTangent(_y, _x);
            else if (_y == 0f && _x > 0f)
                Rotation = (float)Pi / 2;
            else if (_y != 0f && _x < 0f)
            {
                Rotation = VI.Math.ArcTangent(_y, _x);
                Rotation += Rotation < 0f ? (float)Pi * 2f : 0f;
            }
            else
                Rotation = 3f * (float)Pi / 2f;

            return Rotation;
        }


        private void SetPlayerSprite(int _eID, float _rotation, string _status)
        {
            int InitialStatus = 0;
            switch (_status)
            {
                case "Idle":
                    InitialStatus = 8;
                    break;
                case "Hit":
                    InitialStatus = 16;
                    break;
                case "Death":
                    InitialStatus = 24;
                    break;
                default:
                    break;
            }
            if (_rotation < 0)
                _rotation += 2 * (float)Pi;

            if (_rotation >= 15f * MiniAngle || _rotation <= MiniAngle)
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, InitialStatus - 2);
            else if (_rotation <= 3f * MiniAngle)
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, InitialStatus - 3);
            else if (_rotation <= 5f * MiniAngle)
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, InitialStatus - 4);
            else if (_rotation <= 7f * MiniAngle)
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, InitialStatus - 5);
            else if (_rotation <= 9f * MiniAngle)
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, InitialStatus - 6);
            else if (_rotation <= 11f * MiniAngle)
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, InitialStatus - 7);
            else if (_rotation <= 13f * MiniAngle)
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, InitialStatus - 8);
            else
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, InitialStatus - 1);
        }
    }
}
