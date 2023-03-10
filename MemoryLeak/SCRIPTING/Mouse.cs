/*!*****************************************************************************
\file Mouse.cs
\author Lee Hsien Wei Joachim
\par DP email: l.hsienweijoachim@digipen.edu
\par Group: Memory Leak Studios
\date 10-03-2023
\brief
Changes the mouse to a unique texture based on the player direction and animates on
player action
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class Mouse : BaseScript {
        private const double Pi = 3.141592653589793238f;
        private const float MiniAngle = (float)Pi / 8;
        private const int MovingIconIndexStart = 2;

        private float ZoomScaleFactorX;
        private float ZoomScaleFactorY;

        private int playerBoat;

        private bool InAnimation;

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            playerBoat = VI.Entity.GetId("Boat");
            InAnimation = false;
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            playerBoat = VI.Entity.GetId("Boat");
            InAnimation = false;
        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            // To change hardcoded value to get application's width n height when functions are added to internal calls or the compution of mouse world position is corrected to be in the world
            ZoomScaleFactorX = VI.Camera.GetScale.X() / VI.Window.GetScreenWidth();
            ZoomScaleFactorY = VI.Camera.GetScale.Y() / VI.Window.GetScreenHeight();

            VI.Transform.Position.SetX(_ENTITY, VI.Camera.GetPos.X() + ZoomScaleFactorX * VI.Input.Mouse.WorldPosX() + VI.Transform.Scale.GetX(_ENTITY) / 2f);
            VI.Transform.Position.SetY(_ENTITY, VI.Camera.GetPos.Y() + ZoomScaleFactorY * VI.Input.Mouse.WorldPosY() - VI.Transform.Scale.GetY(_ENTITY) / 2f);

            if (VI.Input.Mouse.Hold())
            {
                if (!PlayerScript.PlayerInDialogue)
                {
                    float DirX = VI.Input.Mouse.WorldPosX() + VI.Camera.GetPos.X() - VI.Transform.Position.GetX(playerBoat);
                    float DirY = VI.Input.Mouse.WorldPosY() + VI.Camera.GetPos.Y() - VI.Transform.Position.GetY(playerBoat);
                    SetMouseMovingIcon(_ENTITY, GetRotation(DirX, DirY));
                }
            }
            else if (VI.Input.Mouse.Press())
            {
                if (!InAnimation)
                {
                    VI.Animation.SpriteSheet.SheetIndex.Set(_ENTITY, 1);
                    VI.Animation.SpriteSheet.CurrentFrame.Set(_ENTITY, 0);
                    VI.Animation.SpriteSheet.FrameCount.Set(_ENTITY, 2);
                    InAnimation = true;
                }
            }
            else if (VI.Input.Mouse.Release())
            {
                InAnimation = false;
            }

            if (!InAnimation)
            {
                VI.Animation.SpriteSheet.SheetIndex.Set(_ENTITY, 0);
                VI.Animation.SpriteSheet.CurrentFrame.Set(_ENTITY, 0);
                VI.Animation.SpriteSheet.FrameCount.Set(_ENTITY, 1);
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

        private float GetRotation(float _x, float _y) {
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

        private void SetMouseMovingIcon(int _eID, float _rotation) {
            if (_rotation < 0)
                _rotation += 2 * (float)Pi;
            if (_rotation > 2 * (float)Pi)
                _rotation -= 2 * (float)Pi;

            if (_rotation >= 15f * MiniAngle || _rotation <= MiniAngle)
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, MovingIconIndexStart + 6);
            else if (_rotation <= 3f * MiniAngle)
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, MovingIconIndexStart + 5);
            else if (_rotation <= 5f * MiniAngle)
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, MovingIconIndexStart + 4);
            else if (_rotation <= 7f * MiniAngle)
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, MovingIconIndexStart + 3);
            else if (_rotation <= 9f * MiniAngle)
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, MovingIconIndexStart + 2);
            else if (_rotation <= 11f * MiniAngle)
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, MovingIconIndexStart + 1);
            else if (_rotation <= 13f * MiniAngle)
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, MovingIconIndexStart);
            else
                VI.Animation.SpriteSheet.SheetIndex.Set(_eID, MovingIconIndexStart + 7);
        }
    }
}
