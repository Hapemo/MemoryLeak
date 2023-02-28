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
        float textOffsetX;
        float textOffsetY;
        float textbigOffsetX;
        float textbigOffsetY;
        float textScale;
        float textbigScale;
        public void Alive(int _ENTITY)
        {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            minimapID = VI.Entity.GetId("minimap", "MiniMap");
            textOffsetX = -59;// VI.Text.Offset.GetX(minimapID);
            textOffsetY = -170;// VI.Text.Offset.GetY(minimapID);
            textbigOffsetX = -100;
            textbigOffsetY = 360;
            textScale = VI.Text.Scale.Get(minimapID);
            textbigScale = 1.0f;
        }
        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

            VI.Entity.s_SetActive("minimapbig", "MiniMap", false);
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            //////////////////////////////////////////////init
            if ((VI.Input.Button.s_Released("minimap", "MiniMap")&&!big)||(VI.Input.Mouse.Press(349)&&big))
            {
                big = !big;
                if (big)
                {
                    //VI.Entity.s_SetActive("minimapbig", "MiniMap", true);
                    //VI.Animation.Transform.SetNext(VI.Entity.GetId("minimap", "MiniMap"), 1);
                    VI.Animation.Transform.Start(minimapID);
                    VI.Text.Offset.Set(minimapID, textbigOffsetX, textbigOffsetY);
                    VI.Text.Scale.Set(minimapID, textbigScale);
                }
                else
                {
                    //VI.Entity.s_SetActive("minimapbig", "MiniMap", false);
                    //VI.Animation.Transform.SetNext(VI.Entity.GetId("minimap", "MiniMap"), 0);
                    VI.Animation.Transform.Start(minimapID);
                    VI.Text.Offset.Set(minimapID, textOffsetX, textOffsetY);
                    VI.Text.Scale.Set(minimapID, textScale);

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
