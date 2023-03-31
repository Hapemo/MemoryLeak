/*!*****************************************************************************
\file EnemyAI.cs
\author Huang Wei Jhin
\par DP email: h.weijhin\@digipen.edu
\par Group: Memory Leak Studios
\date 10-03-2023
This script controls all the enemy movement and attacks
*******************************************************************************/
using System;
using System.Net.NetworkInformation;
using System.Runtime.CompilerServices;

namespace BonVoyage
{
    public class EnemyAI : BaseScript
    {
        private float HealSpeed = 1f;
        private float HealCounter;
        private float HitSpeed = 0.5f;
        private float HitInterval;
        private float HitAnimationCounter;
        private float HitCounter;
        private const int HitMax = 11;

        static public bool EnemyActivated = false;
        private float EnemySpeed = 2.2f;
        private float EnemyCurrentSpeed;
        private int ChasingIndex = 0;
        private float RightAngle = (float)VI.Math.Pi() / 2;

        private int HitTaken = 0;
        bool takingDamage = false;
        private float eDirection = 0;
        private EnemyState eState = EnemyState.IDLE;
        private int PlayerId;
        private int EnemyId;
        private int HpBarId;

        public enum EnemyState
        {
            IDLE = 0,
            RISING = 4,
            ATTACK1 = 8,
            ATTACK2 = 12,
        }

        public enum Axis { x, y }

        public void Alive(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void Init(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            EnemyId = VI.Entity.GetId("Enemy");
            PlayerId = VI.Entity.GetId("Boat");
            HpBarId = VI.Entity.GetId("hpbar");
            HitTaken = 0;
            takingDamage = false;
            ChangeState(EnemyState.IDLE);
        }

        public void EarlyUpdate(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void Update(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            //Init(_ENTITY);
            float diffx = GetDistance(PlayerScript.PlayerPosX, PlayerScript.PlayerPosY, Axis.x);
            float diffy = GetDistance(PlayerScript.PlayerPosX, PlayerScript.PlayerPosY, Axis.y);
            float eDirection = GetRotation(diffx, diffy);
            SetDirection(eDirection, eState);
            if (OnScreen(0.95f))
            {
                if (eState == EnemyState.IDLE)
                {
                    ChangeState(EnemyState.RISING);
                }
                else if (eState == EnemyState.RISING)
                {
                    if(THIS.Animation.SpriteSheet.FrameCount.Get() == THIS.Animation.SpriteSheet.CurrentFrame.Get()+1)
                        ChangeState(EnemyState.ATTACK1);
                }
            }
            else if (!OnScreen(1.1f))
            {
                THIS.MovementAI.Run();
                eState = EnemyState.IDLE;
            }
            if (eState != EnemyState.IDLE && eState != EnemyState.RISING)
            {
                THIS.MovementAI.ForceStop();
                float xDis = Math.Abs(PlayerScript.PlayerPosX - THIS.Transform.Position.GetX());
                float yDis = Math.Abs(PlayerScript.PlayerPosY - THIS.Transform.Position.GetY());
                if ((xDis*2.0f < THIS.Transform.Scale.GetX() + VI.Transform.Scale.GetX(PlayerId)) && (yDis*2.0f < THIS.Transform.Scale.GetY() + VI.Transform.Scale.GetX(PlayerId)))
                {
                    eState = EnemyState.ATTACK2;
                    ApplyForce(_ENTITY, diffx, diffy, PlayerScript.PlayerSpeed * 0.50f);
                    //minus health
                }
                else
                {
                    eState = EnemyState.ATTACK1;
                    ApplyForce(_ENTITY, diffx, diffy, PlayerScript.PlayerSpeed *0.80f);
                }
            }


           

        }

        public void FixedUpdate(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            
            // Detecting player hits
            if (eState == EnemyState.ATTACK2 )
            {

                if (THIS.Animation.SpriteSheet.CurrentFrame.Get() == THIS.Animation.SpriteSheet.FrameCount.Get() - 1)
                {
                    if (!takingDamage)
                    { 
                        PlayerScript.PlayerHealth += 1;
                        VI.Animation.SpriteSheet.SheetIndex.Set(HpBarId, PlayerScript.PlayerHealth);
                    }
                    takingDamage = true;
                }
                else
                    takingDamage = false;

            }

            //Healing player
            //if (!VI.Physics.IsCollided(PlayerId, THIS.GetId()) && HitTaken > 0)
            if (eState == EnemyState.IDLE)
            {
                ++HealCounter;
                if (HealCounter >= HitInterval * 100f * HealSpeed)
                {
                    HealCounter = 0;
                    --PlayerScript.PlayerHealth;
                    VI.Animation.SpriteSheet.SheetIndex.Set(HpBarId, PlayerScript.PlayerHealth);
                }
            }

        }

        public void LateUpdate(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        public void Exit(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        public void Dead(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }
        private void ChangeState(EnemyState state)
        {
            eState = state;
            THIS.Animation.SpriteSheet.CurrentFrame.Set(0);
        }
        private bool OnScreen(float offset)
        {
            float EnemyPosX = THIS.Transform.Position.GetX();
            float EnemyPosY = THIS.Transform.Position.GetY();
            // Enemy is in screen
            if (EnemyPosX <= VI.Camera.GetPos.X() + (VI.Camera.GetScale.X() / 2 * offset) &&
                EnemyPosY <= VI.Camera.GetPos.Y() + (VI.Camera.GetScale.Y() / 2 * offset) &&
                EnemyPosX >= VI.Camera.GetPos.X() - (VI.Camera.GetScale.X() / 2 * offset) &&
                EnemyPosY >= VI.Camera.GetPos.Y() - (VI.Camera.GetScale.Y() / 2 * offset))
            {
                return true;
            }
            else return false;
        }

        private float GetSpeed(float _x, float _y)
        {
            return VI.Math.Magnitude(_x, _y) * (float)VI.General.DeltaTime() * 100f * EnemyCurrentSpeed;
        }

        //private void ChasePlayer(float _x, float _y)
        //{
        //    // First attack, enemy still in idle mode
        //    if (OctopusState == EnemyState.IDLE)
        //    {
        //        VI.Audio.PlayBGM("MonsterChase_BGM");
        //        OctopusState = EnemyState.RISING;
        //        THIS.Animation.SpriteSheet.CurrentFrame.Set(0);
        //    }
        //    else if (OctopusState == EnemyState.RISING &&
        //        THIS.Animation.SpriteSheet.CurrentFrame.Get() == THIS.Animation.SpriteSheet.FrameCount.Get() - 1)
        //    {
        //        HitInterval = THIS.Animation.SpriteSheet.Speed.Get() * THIS.Animation.SpriteSheet.FrameCount.Get() * (float)VI.General.DeltaTime() * 100f;
        //        THIS.Animation.SpriteSheet.CurrentFrame.Set(0);
        //        Random rand = new Random();
        //        OctopusState = (rand.Next(0, 2) == 0 ? EnemyState.ATTACK1 : EnemyState.ATTACK2);
        //    }
        //    UpdateTransform(OctopusState);
        //    UpdateSpeed(GetSpeed(_x, _y));
        //}

        

        //private void UpdateSpeed(float _speed)
        //{
        //    THIS.MovementAI.Edit.Timing(_speed);
        //    THIS.MovementAI.Edit.CurrentTiming(_speed);
        //}

        private float GetDistance(float _x, float _y, Axis _axis)
        {
            float xDis = _x - THIS.Transform.Position.GetX();
            float yDis = _y - THIS.Transform.Position.GetY();
            float xNorm = 0f, yNorm = 0f;
            if (VI.Math.SqMagnitude(xDis, yDis) > VI.Math.Epsilon() * VI.Math.Epsilon())
            {
                xNorm = VI.Math.Normalize.X(xDis, yDis);
                yNorm = VI.Math.Normalize.Y(xDis, yDis);
            }
            return (_axis == Axis.x ? xNorm : yNorm);
        }

        private float GetRotation(float _x, float _y)
        {
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

        private void SetDirection(float _rotation, EnemyState _status)
        {
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
