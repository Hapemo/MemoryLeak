using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class BGMcontroller : BaseScript
    {
        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            if (THIS.Input.Button.Clicked())
            {
                VI.Transform.Scale.s_SetX("BGMvolume", "Settings", 0.5f * THIS.Transform.Scale.GetX() - (THIS.Transform.Position.GetX() - VI.Input.Mouse.WorldPosX()));
                VI.Transform.Position.s_SetX("BGMvolume", "Settings", THIS.Transform.Position.GetX() - 0.5f * THIS.Transform.Scale.GetX() + VI.Transform.Scale.s_GetX("BGMvolume", "Settings") * 0.5f);
            }
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
    }
}
