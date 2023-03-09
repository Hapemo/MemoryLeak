using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class PassengerDeliverUI : BaseScript
    {
        static int p1icon, p2icon;
        static bool increase1, increase2;
        static float curr1, curr2;
        static float speed;
        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            p1icon = VI.Entity.GetId("PassengerIcon1", "Dialogue");
            p2icon = VI.Entity.GetId("PassengerIcon2", "Dialogue");
            curr1 = curr2 = 0;
            increase1 = false;
            increase2 = false;
            speed = 250;
            VI.LightSource.SpriteColor.Set(p1icon, 0,0,0, 255);
            VI.LightSource.SpriteColor.Set(p2icon, 0,0,0, 255);

        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            if ((curr1 < 255 && increase1) || (curr2 < 255 && increase2))
                UpdateColor();
        }

        public void FixedUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        public void LateUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public void Exit(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            curr1 = curr2 = 0;
            increase1 = false;
            increase2 = false;
            speed = 250;
        }

        public void Dead(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        static private void UpdateColor()
        {
            if (increase1)
            {
                curr1 += speed * (float)VI.General.DeltaTime();
                if (curr1 > 255)
                    curr1 = 255;
                VI.LightSource.SpriteColor.Set(p1icon, (int)curr1, (int)curr1, (int)curr1, 255);
            }
            if (increase2)
            {
                curr2 += speed * (float)VI.General.DeltaTime();
                if (curr2 > 255)
                    curr2 = 255;
                VI.LightSource.SpriteColor.Set(p2icon, (int)curr2, (int)curr2, (int)curr2, 255);
            }
        }

        static public void DeliveredPassenger()
        {
            if (!increase1)
                increase1 = true;
            else if (!increase2)
                increase2 = true;
        }
    }
}
