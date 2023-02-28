using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class EnemyController : BaseScript {
        private float PlayerPosX;
        private float PlayerPosY;

        private float HitInterval;
        private float HitCounter;
        public int HitTaken;
        private float RightAngle = (float)VI.Math.Pi() / 2;

        private int WorldId;
        private float maxX, maxY, minX, minY, halfX, halfY;

        private int OctopusAttacked;
        private float OctopusDirection;
        static private int ChasingPlayer = 0;
        private int DialogueSceneId;
        private int EnemyTriggerId;

        private const int MaxHealth = 12;

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            DialogueSceneId = VI.Entity.GetId("DialogueBox");
            EnemyTriggerId = VI.Entity.GetId("EnemyTrigger");

            PlayerPosX = 0;
            PlayerPosY = 0;

            WorldId = VI.Entity.GetId("Water");
            halfX = VI.Transform.Position.GetX(WorldId);
            halfY = VI.Transform.Position.GetY(WorldId);
            maxX = (VI.Transform.Scale.GetX(WorldId) / 2) + halfX - THIS.Transform.Scale.GetX();
            maxY = (VI.Transform.Scale.GetY(WorldId) / 2) + halfY - THIS.Transform.Scale.GetY();
            minX = halfX - (VI.Transform.Scale.GetX(WorldId) / 2) + THIS.Transform.Scale.GetX();
            minY = halfY - (VI.Transform.Scale.GetY(WorldId) / 2) + THIS.Transform.Scale.GetY();
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            // Console.WriteLine("From EnemyController!");
        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            VI.Camera.SetScale.X(5500);

            PlayerPosX = VI.Transform.Position.s_GetX("Boat");
            PlayerPosY = VI.Transform.Position.s_GetY("Boat");

            Console.WriteLine(PlayerPosX);
            Console.WriteLine(PlayerPosY);

            float EnemyPosX = THIS.Transform.Position.GetX();
            float EnemyPosY = THIS.Transform.Position.GetY();
            float EnemyDisX = PlayerPosX - EnemyPosX;
            float EnemyDisY = PlayerPosY - EnemyPosY;
            float EnemyNormDisX = 0f, EnemyNormDisY = 0f;
            if (VI.Math.SqMagnitude(EnemyDisX, EnemyDisY) > VI.Math.Epsilon() * VI.Math.Epsilon()) {
                EnemyNormDisX = VI.Math.Normalize.X(EnemyDisX, EnemyDisY);
                EnemyNormDisY = VI.Math.Normalize.Y(EnemyDisX, EnemyDisY);
            }

            // Enemy is in screen
            if (EnemyPosX <= VI.Camera.GetPos.X() + (VI.Camera.GetScale.X() / 2) &&
                EnemyPosY <= VI.Camera.GetPos.Y() + (VI.Camera.GetScale.Y() / 2) &&
                EnemyPosX >= VI.Camera.GetPos.X() - (VI.Camera.GetScale.X() / 2) &&
                EnemyPosY >= VI.Camera.GetPos.Y() - (VI.Camera.GetScale.Y() / 2)) {
                OctopusDirection = GetRotation(EnemyNormDisX, EnemyNormDisY);

                // Chasing player
                /*
                if (!VI.Entity.IsActive(DialogueSceneId) && VI.Math.Negate(EnemyDisX) <= VI.Transform.Scale.GetX(EnemyTriggerId) && VI.Math.Negate(EnemyDisY) <= VI.Transform.Scale.GetY(EnemyTriggerId)) {
                    //THIS.Animation.Transform.Stop();
                    THIS.Animation.Transform.AddAtCurrent.TransformPos(PlayerPosX, PlayerPosY);
                }
                else THIS.Animation.Transform.Start();
                */

                // Attacking player
                if (!VI.Entity.IsActive(DialogueSceneId) && VI.Physics.s_EntitiesCollided("Boat", "EnemyTrigger", "Level1")) {
                    switch (OctopusAttacked) {
                        case 0:
                            OctopusAttacked = 1;
                            SetCharRotation4(OctopusDirection, "Rising");
                            THIS.Animation.SpriteSheet.FrameCount.Set(0);
                            ChasingPlayer = THIS.Animation.Transform.GetCurrentIndex();
                            THIS.Animation.Transform.AddAtCurrent.TransformPos(PlayerPosX, PlayerPosY);
                            HitInterval = THIS.Animation.SpriteSheet.Speed.Get() * THIS.Animation.SpriteSheet.FrameCount.Get();
                            break;
                        case 1:
                            if (THIS.Animation.SpriteSheet.CurrentFrame.Get() == THIS.Animation.SpriteSheet.FrameCount.Get() - 1) {
                                SetCharRotation4(OctopusDirection, "Attack1");
                                THIS.Animation.SpriteSheet.FrameCount.Set(0);
                                OctopusAttacked = 2;
                            }
                            break;
                        case 2:
                            SetCharRotation4(OctopusDirection, "Attack1");
                            break;
                        default:
                            SetCharRotation4(OctopusDirection, "Idle");
                            break;
                    }
                }
                else {
                    OctopusAttacked = 0;
                    SetCharRotation4(OctopusDirection, "Idle");
                    if(ChasingPlayer > 0) THIS.Animation.Transform.Remove(ChasingPlayer);
                }

                if (VI.Physics.s_CheckCollision("Boat", "Enemy", "Level1", true) && HitTaken > -1) {
                    HitCounter += (float)VI.General.DeltaTime();
                    if (HitCounter >= HitInterval) {
                        HitCounter = 0;
                        ++HitTaken;
                        THIS.Audio.Play();
                        VI.Texture.s_Set("hpbar", "Dialogue", "Textures\\Icons\\healthbar-" + (HitTaken + 1) + ".png");
                    }
                }
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
        public int CheckRegion() {
            if (THIS.Transform.Position.GetX() > maxX || THIS.Transform.Position.GetY() > maxY ||
                THIS.Transform.Position.GetX() < minX || THIS.Transform.Position.GetY() < minY) return 0;
            if (THIS.Transform.Position.GetX() > halfX && THIS.Transform.Position.GetY() > halfY) return 1;
            if (THIS.Transform.Position.GetX() > halfX && THIS.Transform.Position.GetY() < halfY) return 2;
            if (THIS.Transform.Position.GetX() < halfX && THIS.Transform.Position.GetY() < halfY) return 3;
            if (THIS.Transform.Position.GetX() < halfX && THIS.Transform.Position.GetY() > halfY) return 4;
            //Console.Write("Out of bounds!\n");
            return -1;
        }

        public float GetRotation(float _x, float _y) {
            float Rotation = 0;
            if (_y != 0f && _x >= 0f)
                Rotation = VI.Math.ArcTangent(_y, _x);
            else if (_y == 0f && _x > 0f)
                Rotation = (float)VI.Math.Pi() / 2;
            else if (_y != 0f && _x < 0f)
            {
                Rotation = VI.Math.ArcTangent(_y, _x);
                Rotation += Rotation < 0f ? (float)VI.Math.Pi() * 2f : 0f;
            }
            else Rotation = 3f * (float)VI.Math.Pi() / 2f;
            return Rotation;
        }

        public void SetCharRotation4(float _rotation, string _status) {
            int InitialStatus = 0;
            switch (_status) {
                case "Idle":
                    InitialStatus = 0;
                    break;
                case "Rising":
                    InitialStatus = 4;
                    break;
                case "Attack1":
                    InitialStatus = 8;
                    break;
                case "Attack2":
                    InitialStatus = 12;
                    break;
                default:
                    break;
            }

            //Console.Write(OctopusDirection+"\n");
            //VI.Animation.SpriteSheet.Index.Set(_entityName, _sceneName, InitialStatus + direction);

            // 1st Quadrant
            if (0 <= _rotation && _rotation < RightAngle)
                THIS.Animation.SpriteSheet.SheetIndex.Set(InitialStatus + 2);
            // 2nd Quadrant
            else if (RightAngle <= _rotation && _rotation < VI.Math.Pi())
                THIS.Animation.SpriteSheet.SheetIndex.Set(InitialStatus + 1);
            // 3rd Quadrant
            else if (VI.Math.Pi() <= _rotation && _rotation < 3f * RightAngle)
                THIS.Animation.SpriteSheet.SheetIndex.Set(InitialStatus);
            // 4th Quadrant
            else
                THIS.Animation.SpriteSheet.SheetIndex.Set(InitialStatus + 3);

        }
    }
}
