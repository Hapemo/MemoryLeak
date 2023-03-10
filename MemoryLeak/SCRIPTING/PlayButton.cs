﻿using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class PlayButton : BaseScript
    {
    bool init = false;
        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void Init(int _ENTITY) {
            VI.Audio.PlayBGM("SwampNightTime_Loop");
        }

        public void EarlyUpdate(int _ENTITY) {
        
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY);
            if (!init)
            {
                Init(_ENTITY);
                init = true;

            }
            if (THIS.Input.Button.Hover())
                THIS.LightSource.SpriteColor.Set(0, 0, 0, 100);
            else
                THIS.LightSource.SpriteColor.Set(0, 0, 0, 0);


            if (THIS.Input.Button.Released())
                TransitionSquare.FadeOut("CutScene");
        }

        public void FixedUpdate(int _ENTITY) {

        }

        public void LateUpdate(int _ENTITY) {
        
        }

        public void Exit(int _ENTITY) {
            VI.Audio.StopBGM();
        }

        public void Dead(int _ENTITY) {

        }
    }
}
