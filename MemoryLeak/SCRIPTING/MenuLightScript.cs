/*!*****************************************************************************
\file MenuLightScript.cs
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 27-01-2023
\brief
This script contains functions to alter the light in the menu of the game.
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class MenuLightScript : BaseScript
    {
        public override void PreInit(int _id)
        {
            var bs = new BaseScript();
            bs.PreInit(_id);
        }

        float radius;
        float speed;
        bool increasing;
        float upper, lower;
        public void Init(int _id) {
            radius = InternalCalls.GetLightSourceRadius("Title", "Menu_Main");
            speed = 500;
            increasing = false;
            upper = 1100;
            lower = 900;
        }

        public void Update(int _id) {
            UpdateRadius();
            InternalCalls.SetLightSourceRadius("Title", "Menu_Main", radius);
        }

        public void Exit(int _id) {
            
        }

        void UpdateRadius()
        {
            if (increasing)
            {
                radius += speed * (float)InternalCalls.GetDeltaTime();
                if (radius > upper)
                {
                    increasing = false;
                    radius = upper;
                }
            }
            else
            {
                radius -= speed * (float)InternalCalls.GetDeltaTime();
                if (radius < lower)
                {
                    increasing = true;
                    radius = lower;
                }
            }
        }
    }
}
