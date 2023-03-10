/*!*****************************************************************************
\file MemoryFragmentExpand.cs
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 01-03-2023
\brief
This file contains scripting functions for logic system for fragments.
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;
using VI;

namespace BonVoyage {
    public class MemoryFragmentExpand : BaseScript
    {
        static int[] relics;
        int[] backs;
        static bool[] activated;
        static bool activatedChanged;
        int expanded;
        bool showing;
        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            relics = new int[]
            {
                VI.Entity.GetId("Relic1"),
                VI.Entity.GetId("Relic2"),
                VI.Entity.GetId("Relic3"),
                VI.Entity.GetId("Relic4"),
                VI.Entity.GetId("Relic5"),
                VI.Entity.GetId("Relic6")
            };
            backs = new int[]
            {
                VI.Entity.GetId("Back1"),
                VI.Entity.GetId("Back2"),
                VI.Entity.GetId("Back3"),
                VI.Entity.GetId("Back4"),
                VI.Entity.GetId("Back5"),
                VI.Entity.GetId("Back6")
            };
            activated = new bool[] { false, false, false, false, false, false };
            expanded = VI.Entity.GetId("memoryfragmentscreen");
            showing = false;
            activatedChanged = false;
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
            if (activatedChanged) { 
                activatedChanged = false;
                VI.ParticleSystem.GenerateLoop(VI.Entity.GetId("memoryfragment"), 5.0f);
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
            activatedChanged = true;
            activated[fragmentId] = true;
        }
    }
}
