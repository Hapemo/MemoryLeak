﻿/*!*****************************************************************************
\file MenuLightCircle.cs
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 27-01-2023
\brief
This script contains functions to alter the light circle in the menu of the
game.
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class MenuLightCircle
    {
        float size;
        float alpha;
        float stepSize, stepAlpha;
        float upperSize, lowerSize;
        float upperAlpha, lowerAlpha;
        bool increasing;
        public void Init() {
            size = 110;
            lowerSize = 110;
            upperSize = 120;

            alpha = 150;
            lowerAlpha = 150;
            upperAlpha = 255;

            stepSize = (upperSize - lowerSize) / 0.4f;
            stepAlpha = (upperAlpha - lowerAlpha) / 0.4f;

            increasing = true;
        }

        public void Update() {
            UpdateSizeAlpha();
            InternalCalls.SetScaleX("LightCircle", "Menu_Main", size);
            InternalCalls.SetScaleY("LightCircle", "Menu_Main", size);
            InternalCalls.SetSpriteColor("LightCircle", "Menu_Main", 255, 255, 255, (int)alpha);
        }

        void UpdateSizeAlpha()
        {
            if (increasing)
            {
                size += stepSize * (float)InternalCalls.GetDeltaTime();
                alpha += stepAlpha * (float)InternalCalls.GetDeltaTime();
                if (size > upperSize)
                {
                    size = upperSize;
                    alpha = upperAlpha;
                    increasing = false;
                }
            }
            else
            {
                size -= stepSize * (float)InternalCalls.GetDeltaTime();
                alpha -= stepAlpha * (float)InternalCalls.GetDeltaTime();
                if (size < lowerSize)
                {
                    size = lowerSize;
                    alpha = lowerAlpha;
                    increasing = true;
                }
            }
        }

        public void Exit() {
            
        }
    }
}
