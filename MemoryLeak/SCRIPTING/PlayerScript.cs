﻿/*!*****************************************************************************
\file PlayerScript.cs
\author Lee Hsien Wei Joachim
\par DP email: l.hsienweijoachim@digipen.edu
\par Group: Memory Leak Studios
\date 10-03-2023
\brief
Script to control the movement and controls of the player, and everything related
to the player
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class PlayerScript : BaseScript
    {
        static public bool PlayerInDialogue;
        static public bool PlayerInOtherAnimation;
        static public bool PlayerInDeathAnimation;
        static public float PlayerHealth;
        static public bool CameraFollowPlayer;

        private const double Pi = 3.141592653589793238f;
        private const float MiniAngle = (float)Pi / 8;

        private const float MaxHealth = 12f;
        private const float PlayerSpeed = 10f;
        private const float SpeedCheatMultiplier = 2.5f;

        private bool SpeedCheatToggle;

        static public float PlayerPosX;
        static public float PlayerPosY;
        private float PlayerRotation;

        private int PlayerCurrWeather;
        private float MovementXModifier;
        private float MovementYModifier;

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            // Initialize bool variables
            PlayerInDialogue = false;
            PlayerInOtherAnimation = false;
            PlayerInDeathAnimation = false;
            PlayerHealth = MaxHealth;
            CameraFollowPlayer = true;

            SpeedCheatToggle = false;

            // Initialize position variables
            PlayerPosX = VI.Transform.Position.GetX(_ENTITY);
            PlayerPosY = VI.Transform.Position.GetY(_ENTITY);
            PlayerRotation = 0;

            PlayerCurrWeather = 0;
            MovementXModifier = 0f;
            MovementYModifier = 0f;
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            #region Player Death
            // Once health hits 0
            if (PlayerHealth <= 0f && !PlayerInDeathAnimation)
            {
                // Update bool flag
                PlayerInDeathAnimation = true;

                // Set animation
                SetPlayerSprite(_ENTITY, PlayerRotation, "Death");
                VI.Animation.SpriteSheet.CurrentFrame.Set(_ENTITY, 0);
                VI.Animation.SpriteSheet.FrameCount.Set(_ENTITY, 11);
            }

            // Check for completion of death animation
            if (PlayerInDeathAnimation && (VI.Animation.SpriteSheet.CurrentFrame.Get(_ENTITY) + 1 == VI.Animation.SpriteSheet.FrameCount.Get(_ENTITY)))
            {
                // Assumes the main game scene level running is the same as the gamestate name
                VI.Scene.Pause(VI.GameState.GetName());     // Pause current scene
                VI.Scene.Play("Game Over");                 // Play Game Over scene
                // Play audio transition if required
            }
            #endregion

            // Things allowed to run when player is not dead
            if (!PlayerInDeathAnimation)
            {
                // Pausing the game
                #region Pause Game
                // Escape key is pressed
                if (VI.Input.Key.Release(256))
                {
                    // Assumes the main game scene level running is the same as the gamestate name
                    //VI.Scene.Play(VI.GameState.GetName());
                    //if (VI.Scene.IsPaused("Pause") == false)
                    //    VI.Scene.Pause("Pause");
                    //else
                    //VI.Scene.Play("Pause");
                    //VI.Scene.Pause("Game Over");
                    //VI.Scene.Pause("How_To_Play");
                    //VI.Scene.Pause("Quit Confirmation");
                    //VI.Scene.Pause("Dialogue");
                    //VI.Scene.Pause("cutscene1");
                    //VI.Scene.Pause("CrystalBalls");
                    //VI.Scene.Pause("MiniMap");
                    //VI.Scene.Pause("EnemyMap");
                    //VI.Scene.Pause("WeatherMap");
                    //VI.Scene.Pause("BackGround");

                    // Play audio transition if required

                }

                #endregion

                // Game cheats
                #region Player Cheats
                // Left control & shift held
                if (VI.Input.Key.Hold(340) && VI.Input.Key.Hold(341))
                {
                    // A is pressed
                    if (VI.Input.Key.Press(65))
                    {
                        PlayerInDialogue = !PlayerInDialogue;
                    }

                    // B is pressed
                    if (VI.Input.Key.Press(66))
                    {
                        SpeedCheatToggle = !SpeedCheatToggle;
                    }

                    // D is pressed
                    if (VI.Input.Key.Press(68))
                    {
                        PlayerHealth = 0f;
                    }
                }
                #endregion

                // Weather effects on the player
                #region Weather Effects
                // Update player's current weather based on updated position
                if (VI.GameState.GetName() != "LevelTutorial") { 
                    PlayerCurrWeather = VI.Weather.GetCurrent(0, PlayerPosX, PlayerPosY);
                    if (PlayerCurrWeather == 2) {
                        MovementXModifier = 0f;
                        MovementYModifier = 0f;
                    }
                }
                #endregion
            }
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void FixedUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            #region Movement
            // Move only if player is not in dialogue or death animation
            if (!PlayerInDialogue && !PlayerInDeathAnimation && !PlayerInOtherAnimation)
            {
                // Left mouse button is held
                if (VI.Input.Mouse.Hold())
                {
                    float DirX = VI.Input.Mouse.WorldPosX() + VI.Camera.GetPos.X() - PlayerPosX;
                    float DirY = VI.Input.Mouse.WorldPosY() + VI.Camera.GetPos.Y() - PlayerPosY;

                    DirX += MovementXModifier;
                    DirY += MovementYModifier;

                    // Move if the vector is significant
                    if (VI.Math.SqMagnitude(DirX, DirY) > float.Epsilon * float.Epsilon)
                    {
                        // Apply force
                        float NormX = VI.Math.Normalize.X(DirX, DirY);
                        float NormY = VI.Math.Normalize.Y(DirX, DirY);
                        ApplyForce(_ENTITY, NormX, NormY, PlayerSpeed * (SpeedCheatToggle ? SpeedCheatMultiplier : 1f));

                        // Get new rotation and set sprite
                        PlayerRotation = GetRotation(NormX, NormY);
                        SetPlayerSprite(_ENTITY, PlayerRotation, "Idle");

                        // Play rowing boat audio
                        VI.Audio.Play(_ENTITY);
                    }

                }
                else // Not held anymore
                {
                    // Stop rowing audio
                    VI.Audio.Stop(_ENTITY);
                }
            }
            else // In dialogue or death animation
            {
                // Stop rowing audio in case
                //VI.Audio.Stop(_ENTITY);
            }

            // Update player position variables
            PlayerPosX = VI.Transform.Position.GetX(_ENTITY);
            PlayerPosY = VI.Transform.Position.GetY(_ENTITY);

            #endregion

        }

        public void LateUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            #region Camera Follow Player
            // Update camera position to follow entity assumed to be player
            if (CameraFollowPlayer)
            {
                VI.Camera.SetPos.Y(VI.Camera.GetPos.Y() + (PlayerPosY - VI.Camera.GetPos.Y()) * (float)VI.General.DeltaTime());
                VI.Camera.SetPos.X(VI.Camera.GetPos.X() + (PlayerPosX - VI.Camera.GetPos.X()) * (float)VI.General.DeltaTime());
            }
            #endregion
        }

        public void Exit(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        public void Dead(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

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

        private void ApplyForce(int _eID, float _x, float _y, float _multiplier)
        {
            VI.Physics.ApplyImpulse(_eID,
                (_x * _multiplier),
                (_y * _multiplier), 0f, 0f);
        }
    }
}
