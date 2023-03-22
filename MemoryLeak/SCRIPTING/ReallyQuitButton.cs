﻿/*!*****************************************************************************
\file ReallyQuitButton.cs
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 01-03-2023
\brief
This file contains scripting functions for logic system for quitting the game.
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class ReallyQuitButton : BaseScript
    {
        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        public void Init(int _ENTITY) {
        }

        public void EarlyUpdate(int _ENTITY) {
        
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            if (THIS.Input.Button.Hover())
                THIS.Sprite.SetColor(0, 0, 0, 100);
            else
                THIS.Sprite.SetColor(0, 0, 0, 0);
            if (THIS.Input.Button.Released())
            {
                VI.GameState.Exit();
            }
        }

        public void FixedUpdate(int _ENTITY) {

        }

        public void LateUpdate(int _ENTITY) {
        
        }

        public void Exit(int _ENTITY) {

        }

        public void Dead(int _ENTITY) {

        }
    }
}
