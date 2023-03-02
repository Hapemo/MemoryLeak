/*!*****************************************************************************
\file MiniMapScript.cs
\author Huang Wei Jhin
\par DP email: h.weijhin\@digipen.edu
\par Group: Memory Leak Studios
\date 28-01-2023
\brief
MiniMapScript contains multiple script components to run the Level1 of the game.
Part of which are:
- Functions of the minimap
- Expanding the minimap
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class MiniMapScript
    {
        static bool big = false;
        int minimapID;
        int boatID;
        int playerheadID;
        float textOffsetX;
        float textOffsetY;
        float textbigOffsetX;
        float textbigOffsetY;
        float textScale;
        float textbigScale;
        private float MapX, MapY;
        private float miniMapX, miniMapY;
        int i = 1;
        public void Alive(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            minimapID = VI.Entity.GetId("minimap", "MiniMap");
            boatID = VI.Entity.GetId("Boat", "Level1");
            playerheadID = VI.Entity.GetId("playerhead", "MiniMap");
            textOffsetX = -59;// VI.Text.Offset.GetX(minimapID);
            textOffsetY = -170;// VI.Text.Offset.GetY(minimapID);
            textbigOffsetX = -100;
            textbigOffsetY = 360;
            textScale = VI.Text.Scale.Get(minimapID);
            textbigScale = 1.0f;
            MapX = VI.Transform.Scale.GetX(VI.Entity.GetId("Water", "Level1"));
            MapY = VI.Transform.Scale.GetY(VI.Entity.GetId("Water", "Level1"));
            miniMapX = 1244;
            miniMapY = 700;
        }
        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            big = false;
            VI.Animation.Transform.SetNext(minimapID, 0);
            VI.Text.Offset.Set(minimapID, textOffsetX, textOffsetY);
            VI.Text.Scale.Set(minimapID, textScale);
            VI.Animation.Transform.Start(minimapID);
            VI.Viewport.SetIsUI(minimapID, false);
            VI.Viewport.SetWidth(minimapID, (int)(MapX / 4));
            VI.Entity.Sprite.SetType(minimapID, 1);

            VI.Animation.Transform.SetNext(playerheadID, 0);
            VI.Animation.Transform.Start(playerheadID);
            VI.Entity.s_SetActive("blur", "MiniMap", false);
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

           
            if (!big && (VI.Input.Button.Released(minimapID)))
            {
                big = true;
                VI.Animation.Transform.SetNext(minimapID, 1);
                VI.Text.Offset.Set(minimapID, textbigOffsetX, textbigOffsetY);
                VI.Text.Scale.Set(minimapID, textbigScale);
                VI.Animation.Transform.Start(minimapID);
                VI.Viewport.SetIsUI(minimapID, true);
                VI.Viewport.SetWidth(minimapID, (int)(MapX / 2));
                VI.Entity.Sprite.SetType(minimapID, 0);

                float posx = VI.Transform.Position.GetX(boatID) * (miniMapX / MapX) * 2;
                float posy = VI.Transform.Position.GetY(boatID) * (miniMapY / MapY) * 2;//helppp
                VI.Animation.Transform.Remove(playerheadID, 1);
                VI.Animation.Transform.Add.Transform(playerheadID, 100, 100, 0, posx, posy, 0.5f);

                VI.Animation.Transform.SetNext(playerheadID, 1);
                VI.Animation.Transform.Start(playerheadID);
                VI.Entity.s_SetActive("blur", "MiniMap", true);
            }
            else if (big && (VI.Input.Mouse.Release(349)) && (!VI.Input.Button.Released(minimapID)))
            {
                big = false;
                VI.Animation.Transform.SetNext(minimapID, 0);
                VI.Text.Offset.Set(minimapID, textOffsetX, textOffsetY);
                VI.Text.Scale.Set(minimapID, textScale);
                VI.Animation.Transform.Start(minimapID);
                VI.Viewport.SetIsUI(minimapID, false);
                VI.Viewport.SetWidth(minimapID, (int)(MapX / 4));
                VI.Entity.Sprite.SetType(minimapID, 1);

                VI.Animation.Transform.SetNext(playerheadID, 0);
                VI.Animation.Transform.Start(playerheadID);
                VI.Entity.s_SetActive("blur", "MiniMap", false);
            }

        }

        public void Exit(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            big = false;
            VI.Animation.Transform.SetNext(minimapID, 0);
            VI.Text.Offset.Set(minimapID, textOffsetX, textOffsetY);
            VI.Text.Scale.Set(minimapID, textScale);
            VI.Animation.Transform.Start(minimapID);
            VI.Viewport.SetIsUI(minimapID, false);
            VI.Viewport.SetWidth(minimapID, (int)(MapX / 4));
            VI.Entity.Sprite.SetType(minimapID, 1);

            VI.Animation.Transform.SetNext(playerheadID, 0);
            VI.Animation.Transform.Start(playerheadID);
            VI.Entity.s_SetActive("blur", "MiniMap", false);
        }
        public void Dead(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }
    }
}
