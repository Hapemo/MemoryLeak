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
        int playerID;
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
            playerID = VI.Entity.GetId("Boat", "Level1");
            playerheadID = VI.Entity.GetId("playerhead", "MiniMap");
            textOffsetX = -59;// VI.Text.Offset.GetX(minimapID);
            textOffsetY = -170;// VI.Text.Offset.GetY(minimapID);
            textbigOffsetX = -100;
            textbigOffsetY = 360;
            textScale = VI.Text.Scale.Get(minimapID);
            textbigScale = 1.0f;
        }
        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            MapX = VI.Transform.Scale.GetX(VI.Entity.GetId("Water", "Level1"));
            MapY = VI.Transform.Scale.GetY(VI.Entity.GetId("Water", "Level1"));
            miniMapX = VI.Transform.Scale.GetX(VI.Entity.GetId("minimapbig", "MiniMap"));
            miniMapY = VI.Transform.Scale.GetY(VI.Entity.GetId("minimapbig", "MiniMap"));
            VI.Entity.s_SetActive("minimapbig", "MiniMap", false);
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            if ((VI.Input.Mouse.Press(349) && big)||(VI.Input.Button.Clicked(minimapID) &&!big))
            {
                big = !big;
                
                if (big)
                {
                    //VI.Entity.s_SetActive("minimapbig", "MiniMap", true);
                    VI.Animation.Transform.SetNext(minimapID, 1);
                    VI.Text.Offset.Set(minimapID, textbigOffsetX, textbigOffsetY);
                    VI.Text.Scale.Set(minimapID, textbigScale);
                    VI.Animation.Transform.Start(minimapID);
                    VI.Viewport.SetIsUI(minimapID, true);
                    VI.Viewport.SetWidth(minimapID, (int)(MapX/2));
                    VI.Entity.Sprite.SetType(minimapID, 0);

                    float posx = VI.Transform.Position.GetX(playerID) * (miniMapX / MapX)*2;
                    float posy = VI.Transform.Position.GetY(playerID) * (miniMapY / MapY)*2;
                    VI.Animation.Transform.Add.Transform(playerheadID, 100,100,0, posx, posy, 0.5f);
                    
                    VI.Animation.Transform.SetNext(playerheadID, i++);
                    VI.Animation.Transform.Start(playerheadID);
                }
                else
                {
                    //VI.Entity.s_SetActive("minimapbig", "MiniMap", false);
                    VI.Animation.Transform.SetNext(minimapID, 0);
                    VI.Text.Offset.Set(minimapID, textOffsetX, textOffsetY);
                    VI.Text.Scale.Set(minimapID, textScale);
                    VI.Animation.Transform.Start(minimapID);
                    VI.Viewport.SetIsUI(minimapID, false);
                    VI.Viewport.SetWidth(minimapID, (int)(MapX/8));
                    VI.Entity.Sprite.SetType(minimapID, 1);

                    VI.Animation.Transform.SetNext(playerheadID, 0);
                    VI.Animation.Transform.Start(playerheadID);

                }
            }

        }

        public void Exit(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            big = false;
            VI.Entity.s_SetActive("minimapbig", "MiniMap", false);
        }
        public void Dead(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }
    }
}
