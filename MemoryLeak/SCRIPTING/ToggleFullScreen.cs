﻿/*!*****************************************************************************
\file PlayerScriptMenu.cs
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Group: Memory Leak Studios
\date 10-03-2023
\brief
The base script for all the script that will be made
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class ToggleFullScreen : BaseScript
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

            if (THIS.Input.Button.Hover())
                THIS.Sprite.SetColor(0, 0, 0, 100);
            else
                THIS.Sprite.SetColor(0, 0, 0, 0);

            if (THIS.Input.Button.Released())
                VI.Window.SetFullScreen(!VI.Window.GetFullScreen());
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
