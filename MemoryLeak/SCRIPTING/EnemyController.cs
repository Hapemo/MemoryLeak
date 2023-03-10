/*!*****************************************************************************
\file EnemyController.cs
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Group: Memory Leak Studios
\date 10-03-2023
This script controls all the enemy movement and attacks
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class EnemyController : BaseScript {
        private float HealSpeed = 1f;
        private float HealCounter;
        private float HitSpeed = 0.5f;
        private float HitInterval;
        private float HitAnimationCounter;
        private float HitCounter;
        private int HitMax = 11;
        private int HitTaken = 0;

        static public bool EnemyActivated = false;
        public float EnemySpeed = 2.2f;
        private EnemyState OctopusState;
        private int ChasingIndex = 0;
        private float RightAngle = (float)VI.Math.Pi() / 2;

        private int PlayerId;
        private int EnemyTriggerId;
        private int HpBarId;

        public enum EnemyState {
            IDLE = 0,
            RISING = 4,
            ATTACK1 = 8,
            ATTACK2 = 12,
        }

        public enum Axis { x, y }

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            EnemyTriggerId = VI.Entity.GetId("EnemyTrigger");
            PlayerId = VI.Entity.GetId("Boat");
            HpBarId = VI.Entity.GetId("hpbar");
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            Alive(_ENTITY);
            //VI.Camera.SetScale.X(5500);

            if (EnemyActivated) {
                VI.Entity.Activate(EnemyTriggerId);

                float x = GetDistance(PlayerScript.PlayerPosX, PlayerScript.PlayerPosY, Axis.x);
                float y = GetDistance(PlayerScript.PlayerPosX, PlayerScript.PlayerPosY, Axis.y);
                float OctopusDirection = GetRotation(x, y);

                // Enemy is in screen
                if (OnScreen()) {
                    if (!PlayerScript.PlayerInDialogue && VI.Physics.CheckCollision(PlayerId, EnemyTriggerId, true))
                        ChasePlayer(x, y);
                    else {
                        VI.Audio.StopBGM();
                        OctopusState = EnemyState.IDLE;
                        UpdateTransform(OctopusState);
                        float x_ = GetDistance(THIS.Animation.Transform.Get.CurrentPosX(), THIS.Animation.Transform.Get.CurrentPosY(), Axis.x);
                        float y_ = GetDistance(THIS.Animation.Transform.Get.CurrentPosX(), THIS.Animation.Transform.Get.CurrentPosY(), Axis.y);
                        UpdateSpeed(GetSpeed(x_, y_));
                        if (ChasingIndex > 0) ChasingIndex = 0;
                    }
                    SetDirection(OctopusDirection, OctopusState);
                }
            } else {
                THIS.Deactivate();
                VI.Entity.Deactivate(EnemyTriggerId);
            }
        }

        public void FixedUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            
            if (EnemyActivated) {
                // Detecting player hits
                if (VI.Physics.IsCollided(PlayerId, THIS.GetId()) && HitTaken > -1) {
                    ++HitCounter;
                    ++HitAnimationCounter;
                    if (HitAnimationCounter >= HitInterval) {
                        THIS.Audio.Play();
                        HitAnimationCounter = 0;
                    }
                
                    if (HitCounter >= HitInterval * 80f * HitSpeed) {
                        HitCounter = 0;
                        HitTaken = (HitTaken < HitMax ? HitTaken + 1 : -1);
                        VI.Animation.SpriteSheet.SheetIndex.Set(HpBarId, HitTaken);
                    }

                    if(HitTaken >= HitMax) {
                        VI.Scene.Play("Game Over");
                        VI.Scene.Pause("Level2");
                        VI.Scene.Pause("How_To_Play");
                        VI.Scene.Pause("Pause");
                        VI.Scene.Pause("Dialogue2");
                        VI.Scene.Pause("Quit Confirmation");
                        VI.Scene.Pause("Settings");
                        VI.Scene.Pause("Mouse");
                        VI.Scene.Pause("CrystalBalls");
                        VI.Scene.Pause("Level2Background");
                        VI.Scene.Pause("MiniMap");
                        VI.Scene.Pause("WeatherMap");
                        VI.Scene.Pause("EnemyMap");
                        VI.Scene.Pause("GUI Scene");
                        VI.Scene.Pause("Transition");
                        VI.Scene.Pause("TutorialUILvl2");
                    }
                }
            }

            // Healing player
            if (!VI.Physics.IsCollided(PlayerId, THIS.GetId()) && HitTaken > 0) {
                ++HealCounter;
                if (HealCounter >= HitInterval * 100f * HealSpeed) {
                    HealCounter = 0;
                    --HitTaken;
                    VI.Animation.SpriteSheet.SheetIndex.Set(HpBarId, HitTaken);
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

        private bool OnScreen() {
            float EnemyPosX = THIS.Transform.Position.GetX();
            float EnemyPosY = THIS.Transform.Position.GetY();
            // Enemy is in screen
            if (EnemyPosX <= VI.Camera.GetPos.X() + (VI.Camera.GetScale.X() / 2) &&
                EnemyPosY <= VI.Camera.GetPos.Y() + (VI.Camera.GetScale.Y() / 2) &&
                EnemyPosX >= VI.Camera.GetPos.X() - (VI.Camera.GetScale.X() / 2) &&
                EnemyPosY >= VI.Camera.GetPos.Y() - (VI.Camera.GetScale.Y() / 2)) {
                return true;
            } else return false;
        }

        private float GetSpeed(float _x, float _y) {
            return VI.Math.Magnitude(_x, _y) * (float)VI.General.DeltaTime() * 100f * EnemySpeed;
        }

        private void ChasePlayer(float _x, float _y) {
            // First attack, enemy still in idle mode
            if (OctopusState == EnemyState.IDLE) {
                VI.Audio.PlayBGM("MonsterChase_BGM");
                OctopusState = EnemyState.RISING;
                THIS.Animation.SpriteSheet.CurrentFrame.Set(0);
            } else if (OctopusState == EnemyState.RISING &&
                THIS.Animation.SpriteSheet.CurrentFrame.Get() == THIS.Animation.SpriteSheet.FrameCount.Get() - 1) {
                HitInterval = THIS.Animation.SpriteSheet.Speed.Get() * THIS.Animation.SpriteSheet.FrameCount.Get() * (float)VI.General.DeltaTime() * 100f;
                THIS.Animation.SpriteSheet.CurrentFrame.Set(0);
                Random rand = new Random();
                OctopusState = (rand.Next(0, 2) == 0 ? EnemyState.ATTACK1 : EnemyState.ATTACK2);
            }
            UpdateTransform(OctopusState);
            UpdateSpeed(GetSpeed(_x, _y));
        }

        private void UpdateTransform(EnemyState _state) {
            if (ChasingIndex == 0) {
                ChasingIndex = THIS.Animation.Transform.GetCurrentIndex();
                THIS.Animation.Transform.AddAtCurrent.TransformPos(PlayerScript.PlayerPosX, PlayerScript.PlayerPosY);
                VI.Animation.Transform.AddAtCurrent.TransformPos(EnemyTriggerId, PlayerScript.PlayerPosX, PlayerScript.PlayerPosY);
            } else {
                if (_state != EnemyState.IDLE) { 
                    THIS.Animation.Transform.Edit.CurrentPosX(PlayerScript.PlayerPosX);
                    THIS.Animation.Transform.Edit.CurrentPosY(PlayerScript.PlayerPosY);
                    VI.Animation.Transform.Edit.CurrentPosX(EnemyTriggerId, PlayerScript.PlayerPosX);
                    VI.Animation.Transform.Edit.CurrentPosY(EnemyTriggerId, PlayerScript.PlayerPosY);
                } else {
                    THIS.Animation.Transform.Remove(ChasingIndex);
                    VI.Animation.Transform.Remove(EnemyTriggerId, ChasingIndex);
                }
            }
        }

        private void UpdateSpeed(float _speed) {
            THIS.Animation.Transform.Edit.Timing(_speed);
            VI.Animation.Transform.Edit.Timing(EnemyTriggerId, _speed);
            THIS.Animation.Transform.Edit.CurrentTiming(_speed);
            VI.Animation.Transform.Edit.CurrentTiming(EnemyTriggerId, _speed);
        }

        private float GetDistance(float _x, float _y, Axis _axis) {
            float xDis = _x - THIS.Transform.Position.GetX();
            float yDis = _y - THIS.Transform.Position.GetY();
            float xNorm = 0f, yNorm = 0f;
            if (VI.Math.SqMagnitude(xDis, yDis) > VI.Math.Epsilon() * VI.Math.Epsilon()) {
                xNorm = VI.Math.Normalize.X(xDis, yDis);
                yNorm = VI.Math.Normalize.Y(xDis, yDis);
            }
            return (_axis == Axis.x ? xNorm : yNorm);
        }

        private float GetRotation(float _x, float _y) {
            float Rotation = 0;
            if (_y != 0f && _x >= 0f)
                Rotation = VI.Math.ArcTangent(_y, _x);
            else if (_y == 0f && _x > 0f)
                Rotation = (float)VI.Math.Pi() / 2;
            else if (_y != 0f && _x < 0f) {
                Rotation = VI.Math.ArcTangent(_y, _x);
                Rotation += Rotation < 0f ? (float)VI.Math.Pi() * 2f : 0f;
            }
            else Rotation = 3f * (float)VI.Math.Pi() / 2f;
            return Rotation;
        }

        private void SetDirection(float _rotation, EnemyState _status) {
            // 1st Quadrant
            if (0 <= _rotation && _rotation < RightAngle)
                THIS.Animation.SpriteSheet.SheetIndex.Set((int)_status + 2);
            // 2nd Quadrant
            else if (RightAngle <= _rotation && _rotation < VI.Math.Pi())
                THIS.Animation.SpriteSheet.SheetIndex.Set((int)_status + 1);
            // 3rd Quadrant
            else if (VI.Math.Pi() <= _rotation && _rotation < 3f * RightAngle)
                THIS.Animation.SpriteSheet.SheetIndex.Set((int)_status);
            // 4th Quadrant
            else
                THIS.Animation.SpriteSheet.SheetIndex.Set((int)_status + 3);
        }
    }
}
