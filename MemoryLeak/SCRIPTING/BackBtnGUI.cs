/*!*****************************************************************************
\file BackButton.cs
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 01-03-2023
\brief
This file contains scripting functions for logic system for button.
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class BackBtnGUI : BaseScript
    {
        static int[] expandedRelics;
        
        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            expandedRelics = new int[]
            {
                VI.Entity.GetId("Relic1Expanded"),
                VI.Entity.GetId("Relic2Expanded"),
                VI.Entity.GetId("Relic3Expanded"),
                VI.Entity.GetId("Relic4Expanded"),
                VI.Entity.GetId("Relic5Expanded"),
                VI.Entity.GetId("Relic6Expanded")
            };
        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            Init(_ENTITY);

            if (THIS.Input.Button.Released())
            {
                foreach (int relic in expandedRelics)
                    VI.Entity.Deactivate(relic);
                VI.Scene.Pause("GUI Scene Expanded");
                VI.Scene.Play("GUI Scene");
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
