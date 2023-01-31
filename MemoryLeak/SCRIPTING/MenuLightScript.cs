using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class MenuLightScript
    {
        float radius;
        float speed;
        bool increasing;
        float upper, lower;
        public void Init() {
            radius = InternalCalls.GetLightSourceRadius("Title", "Menu_Main");
            speed = 500;
            increasing = false;
            upper = 1100;
            lower = 900;
        }

        public void Update() {
            UpdateRadius();
            InternalCalls.SetLightSourceRadius("Title", "Menu_Main", radius);
        }

        public void Exit() {
            
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
