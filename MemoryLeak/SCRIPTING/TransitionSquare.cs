/*!*****************************************************************************
\file TransitionSquare.cs
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 01-03-2023
\brief
This file contains scripting functions for logic system for transition.
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class TransitionSquare : BaseScript
    {
        static bool fadingin;
        static bool fadingout;
        static string nextgs;

        static float currAlpha;
        static float speed;

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            fadingin = true;
            fadingout = false;
            nextgs = "";
            currAlpha = 255;
            speed = 250;
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            fadingin = true;
            fadingout = false;
            nextgs = "";
            currAlpha = 255;
            speed = 250;


        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            if (fadingin)
                DecreaseAlpha();

            if (fadingout)
                IncreaseAlpha();
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

        private static void DecreaseAlpha()
        {
            currAlpha -= speed * (float)VI.General.DeltaTime();
            if (currAlpha < 0)
            {
                currAlpha = 0;
                fadingin = false;
            }
            THIS.LightSource.SpriteColor.Set(0, 0, 0, (int)currAlpha);
        }

        private static void IncreaseAlpha()
        {
            currAlpha += speed * (float)VI.General.DeltaTime();
            if (currAlpha > 255)
            {
                currAlpha = 255;
                fadingout = false;
            }
            THIS.LightSource.SpriteColor.Set(0, 0, 0, (int)currAlpha);
            if (currAlpha == 255)
            {
                fadingin = true;
                VI.GameState.Go(nextgs);
            }
        }

        public static void FadeIn()
        {
            fadingin = true;
            fadingout = false;
        }
        public static void FadeOut(string _nextstate)
        {
            fadingout = true;
            fadingin = false;
            nextgs = _nextstate;
        }
    }
}
