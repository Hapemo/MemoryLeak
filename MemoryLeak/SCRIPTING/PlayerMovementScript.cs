using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class PlayerMovementScript : BaseScript
    {
        static public bool PlayerInDialogue;
        private const float PlayerSpeed = 50f;
        private const double Pi = 3.141592653589793238f;
        private const float MiniAngle = (float)Pi / 8;

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void Init(int _ENTITY) {
            PlayerInDialogue = false;
        }

        public void Update(int _ENTITY) {
            if (VI.Input.Key.Press(256))
            {
                VI.Scene.Pause("Settings");
                VI.Scene.Pause("How_To_Play");
                VI.Scene.Pause(VI.GameState.GetName());
                VI.Scene.Pause("Game Over");
                VI.Scene.Play("Pause");
                //VI.Audio.
            }

        }

        public void FixedUpdate(int _ENTITY) {
            if (PlayerInDialogue == false)
            {
                if (VI.Input.Mouse.Hold(349))
                {
                    float PlayerPosX = THIS.Transform.Position.GetX();
                    float PlayerPosY = THIS.Transform.Position.GetY();
                    float DirX = VI.Input.Mouse.WorldPosX() - PlayerPosX;
                    float DirY = VI.Input.Mouse.WorldPosY() - PlayerPosY;
                    if (VI.Math.SqMagnitude(DirX, DirY) > float.Epsilon * float.Epsilon)
                    {
                        float NormX = VI.Math.Normalize.X(DirX, DirY);
                        float NormY = VI.Math.Normalize.Y(DirX, DirY);
                        ApplyForce(THIS.GetId(), NormX, NormY, PlayerSpeed);
                        float PlayerRotation = GetRotation(NormX, NormY);
                        SetCharRotation(THIS.GetId(), PlayerRotation, "Idle");
                        VI.Audio.Play(THIS.GetId());
                    }
                    Console.WriteLine("Test\n");
                }
                else {
                    VI.Audio.Stop(THIS.GetId());
                }
            }
        }
        public void ApplyForce(int _eID, float _x, float _y, float _multiplier)
        {
            VI.Physics.ApplyImpulse(_eID,
                (_x * _multiplier * (float)VI.General.DeltaTime()),
                (_y * _multiplier * (float)VI.General.DeltaTime()), 0f, 0f);
        }

        public float GetRotation(float _x, float _y)
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
            else Rotation = 3f * (float)Pi / 2f;
            return Rotation;
        }

        public void SetCharRotation(int _eID, float _rotation, string _status)
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
                VI.Animation.SheetIndex.Set(_eID, InitialStatus - 2);
            else if (_rotation <= 3f * MiniAngle) 
                VI.Animation.SheetIndex.Set(_eID, InitialStatus - 3);
            else if (_rotation <= 5f * MiniAngle) 
                VI.Animation.SheetIndex.Set(_eID, InitialStatus - 4);
            else if (_rotation <= 7f * MiniAngle)
                VI.Animation.SheetIndex.Set(_eID, InitialStatus - 5);
            else if (_rotation <= 9f * MiniAngle) 
                VI.Animation.SheetIndex.Set(_eID, InitialStatus - 6);
            else if (_rotation <= 11f * MiniAngle) 
                VI.Animation.SheetIndex.Set(_eID, InitialStatus - 7);
            else if (_rotation <= 13f * MiniAngle) 
                VI.Animation.SheetIndex.Set(_eID, InitialStatus - 8);
            else 
                VI.Animation.SheetIndex.Set(_eID, InitialStatus - 1);
        }

        public void Exit(int _ENTITY) {

        }

        public void Dead(int _ENTITY) {

        }
    }
}
