using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class WeatherScript
    {
        private float maxMapX, maxMapY;
        public void Init() {
            maxMapX = 4000;// (InternalCalls.GetScaleX("Water", "Level1"));
            maxMapY = 3000;// (InternalCalls.GetScaleY("Water", "Level1"));
            InternalCalls.WeatherAIinit(maxMapX, maxMapY);
        }

        public void Update() {
            
        }

        public void Exit() {
            
        }
    }
}
