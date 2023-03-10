/*!*****************************************************************************
\file CutSceneScript.cs
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 01-03-2023
\brief
This file contains scripting functions for logic system for button.
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class CutSceneScript : BaseScript
    {
        int currScn;
        int currAlpha;
        int speed;
        bool isAlphaDecreasing;
        string entity;
        const string scene = "CutScene";
        const string light = "light";
        const string lightning = "lightning";
        bool skipping;
        int lightningAlpha;
        bool soundPlayed;
        int targetRadius;
        int currRadius;

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY);
            currScn = 0;
            isAlphaDecreasing = false;
            entity = "e" + currScn;
            currAlpha = 255;
            speed = 5;
            lightningAlpha = 255;
            soundPlayed = false;
            currRadius = 2000;
            skipping = false;
        }

        public void Init(int _ENTITY) {
            targetRadius = (int)VI.LightSource.Radius.s_Get(light, scene);
            VI.Audio.PlayBGM("CaveWithWaterDrops_Loop");
        }

        public void EarlyUpdate(int _ENTITY) { }

        public void Update(int _ENTITY) {
            if (VI.Input.Button.s_Released("Skip", "CutSceneUI"))
            {
                isAlphaDecreasing = true;
                skipping = true;
            }
            if (currScn >= 19)
            {
                if (skipping || !isAlphaDecreasing)
                {
                    VI.GameState.Go("LevelTutorial");
                }
            }
            if (!skipping && !isAlphaDecreasing && VI.Input.Key.Press(349) && currScn < 19)
                isAlphaDecreasing = true;
        }

        public void FixedUpdate(int _ENTITY) {
            if (isAlphaDecreasing)
                UpdateAlpha();
            if (currScn >= 12 && !skipping)
            {
                UpdateLightning();
                if (!soundPlayed)
                {
                    soundPlayed = true;
                    VI.Audio.s_Play("lightning", scene);
                }
            }
        }

        public void UpdateAlpha()
        {
            if (skipping)
            {
                if (currAlpha > 0)
                {
                    currAlpha -= speed;
                    if (currAlpha < 0) currAlpha = 0;
                    VI.LightSource.SpriteColor.s_Set(entity, scene, 255, 255, 255, currAlpha);

                    for (int i = currScn + 1; i < 19; ++i)
                        VI.LightSource.SpriteColor.s_Set("e" + i, scene, 255, 255, 255, 0);
                }
                if (currAlpha == 0)
                {
                    currAlpha = 255;
                    isAlphaDecreasing = false;
                    currScn = 19;
                }
            }
            else
            {
                if (currAlpha > 0)
                {
                    currAlpha -= speed; 
                    if (currAlpha < 0)
                        currAlpha = 0;
                    VI.LightSource.SpriteColor.s_Set(entity, scene, 255, 255, 255, currAlpha);
                }
                if (currAlpha == 0)
                {
                    currAlpha = 255;
                    isAlphaDecreasing = false;
                    ++currScn;
                    entity = "e" + currScn;
                }
            }
        }

        public void UpdateLightning()
        {
            if (lightningAlpha != 0)
            {
                lightningAlpha -= speed;
                if (lightningAlpha < 0)
                    lightningAlpha = 0;
                VI.LightSource.SpriteColor.s_Set(lightning, scene, 255, 255, 255, lightningAlpha);
            }
            if (currRadius != targetRadius)
            {
                currRadius -= 20;
                if (currRadius < targetRadius)
                    currRadius = targetRadius;
                VI.LightSource.Radius.s_Set(light, scene, currRadius);
            }
        }

        public void LateUpdate(int _ENTITY) { }

        public void Exit(int _ENTITY) {
            VI.Audio.StopBGM();
        }

        public void Dead(int _ENTITY) {

        }
    }
}
