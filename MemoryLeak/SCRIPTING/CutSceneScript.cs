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
        }

        public void Init(int _ENTITY) {
            targetRadius = (int)VI.LightSource.Radius.Get(light, scene);
        }

        public void Update(int _ENTITY) {
            if (!isAlphaDecreasing && VI.Input.Key.Press(349) && currScn < 18)
                isAlphaDecreasing = true;
        }

        public void FixedUpdate(int _ENTITY) {
            if (isAlphaDecreasing)
                UpdateAlpha();
            if (currScn >= 12)
            {
                UpdateLightning();
                if (!soundPlayed)
                {
                    soundPlayed = true;
                    VI.Audio.Play("lightning", scene);
                }
            }
        }

        public void UpdateAlpha()
        {
            if (currAlpha > 0)
            {
                currAlpha -= speed *2; 
                if (currAlpha < 0)
                    currAlpha = 0;
                VI.LightSource.SpriteColor.Set(entity, scene, 255, 255, 255, currAlpha);
            }
            if (currAlpha == 0)
            {
                currAlpha = 255;
                isAlphaDecreasing = false;
                ++currScn;
                entity = "e" + currScn;
            }
        }

        public void UpdateLightning()
        {
            if (lightningAlpha != 0)
            {
                lightningAlpha -= speed;
                if (lightningAlpha < 0)
                    lightningAlpha = 0;
                VI.LightSource.SpriteColor.Set(lightning, scene, 255, 255, 255, lightningAlpha);
            }
            if (currRadius != targetRadius)
            {
                currRadius -= 20;
                if (currRadius < targetRadius)
                    currRadius = targetRadius;
                VI.LightSource.Radius.Set(light, scene, currRadius);
            }
        }

        public void Exit(int _ENTITY) {

        }

        public void Dead(int _ENTITY) {

        }
    }
}
