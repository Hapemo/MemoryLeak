﻿using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class Fragment6 : BaseScript
    {
        bool increasingalpha;
        float currclr;
        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            increasingalpha = false;
            currclr = 0;
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            increasingalpha = true;
        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            if (increasingalpha)
                IncreaseAlpha();

        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

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

        private void IncreaseAlpha()
        {
            currclr += 2;
            if (currclr > 255)
            {
                currclr = 255;
                increasingalpha = false;
            }
            THIS.LightSource.SpriteColor.Set((int)currclr, (int)currclr, (int)currclr, 255);
        }
    }
}
