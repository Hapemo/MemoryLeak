using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class MemoryFragmentExpand : BaseScript
    {
        static int[] relics;
        int[] backs;
        static bool[] activated;
        int expanded;
        bool showing;
        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            relics = new int[]
            {
                VI.Entity.GetId("Relic1", "Dialogue"),
                VI.Entity.GetId("Relic2", "Dialogue"),
                VI.Entity.GetId("Relic3", "Dialogue"),
                VI.Entity.GetId("Relic4", "Dialogue"),
                VI.Entity.GetId("Relic5", "Dialogue"),
                VI.Entity.GetId("Relic6", "Dialogue")
            };
            backs = new int[]
            {
                VI.Entity.GetId("Back1", "Dialogue"),
                VI.Entity.GetId("Back2", "Dialogue"),
                VI.Entity.GetId("Back3", "Dialogue"),
                VI.Entity.GetId("Back4", "Dialogue"),
                VI.Entity.GetId("Back5", "Dialogue"),
                VI.Entity.GetId("Back6", "Dialogue")
            };
            activated = new bool[] { false, false, false, false, false, false };
            expanded = VI.Entity.GetId("memoryfragmentscreen", "Dialogue");
            showing = false;
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            //make button toggle showing
            //activate every frame
            if (THIS.Input.Button.Released())
            {
                showing = !showing;
            }
            if (showing)
            {
                ActivateFragMenu();
            }
            else
            {
                DeactivateFragMenu();
            }
            //if (VI.Input.Key.Press(65))
            //{
            //    ActivateFragment(0);
            //}
            //if (VI.Input.Key.Press(66))
            //{
            //    ActivateFragment(1);
            //}
            //if (VI.Input.Key.Press(67))
            //{
            //    ActivateFragment(2);
            //}
            //if (VI.Input.Key.Press(68))
            //{
            //    ActivateFragment(3);
            //}
            //if (VI.Input.Key.Press(69))
            //{
            //    ActivateFragment(4);
            //}
            //if (VI.Input.Key.Press(70))
            //{
            //    ActivateFragment(5);
            //}
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
            DeactivateFragMenu();
        }

        public void Dead(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        private void ActivateFragMenu()
        {
            foreach (int back in backs)
                VI.Entity.Activate(back);
            for (int i = 0; i < 6; ++ i)
            {
                if (activated[i])
                    VI.Entity.Activate(relics[i]);
            }
            VI.Entity.Activate(expanded);
            showing = true;
        }

        private void DeactivateFragMenu()
        {
            foreach (int back in backs)
                VI.Entity.Deactivate(back);
            foreach (int relic in relics)
                VI.Entity.Deactivate(relic);
            VI.Entity.Deactivate(expanded);
            showing = false;
        }

        public static void ActivateFragment(int fragmentId)
        {
            activated[fragmentId] = true;
        }
    }
}
