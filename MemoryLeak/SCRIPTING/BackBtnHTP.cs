/*!*****************************************************************************
\file BackBtnHTP.cs
\author Huang Wei Jhin
\par DP email: h.weijhin\@digipen.edu
\par Group: Memory Leak Studios
\date 10-03-2023
\brief
Script that runs logic to go back to the previous scene from How to Play scene
*******************************************************************************/

using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class BackBtnHTP : BaseScript
    {
        int time = 0;
        int ControlsID;
        int PlayerMovementID;
        int DialogueID;
        int CrystalBallID;
        int WeatherID;
        int MemeoryFragmentID;
        int EnemyID;
        int BackBtnID;
        int ForwardBtnID;
        //bool init = false;
        int c1;
        int c2;
        int c3;
        int c4;
        int pm1;
        int pm2;
        int pm3;
        int pm4;
        int pm5;
        int pm6;
        int pm7;
        int d1;
        int d2;
        int d3;
        int d4;
        int d5;
        int d6;
        int d7;
        int d8;
        int cb1;
        int cb2;
        int cb3;
        int w1;
        int w2;
        int w3;
        int w4;
        int w5;
        int w6;
        int w7;
        int w8;
        int mf1;
        int mf2;
        int mf3;
        int mf4;
        int e1;
        int e2;
        int e3;
        int e4;
        int e5;
        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            BackBtnID = VI.Entity.GetId("BackBtnHTP", "How_To_Play");
            ForwardBtnID = VI.Entity.GetId("ForwardBtnHTP", "How_To_Play");
            ControlsID = VI.Entity.GetId("Controls", "How_To_Play");
            PlayerMovementID = VI.Entity.GetId("PlayerMovement", "How_To_Play");
            DialogueID = VI.Entity.GetId("Dialogue", "How_To_Play");
            CrystalBallID = VI.Entity.GetId("CrystalBall", "How_To_Play");
            WeatherID = VI.Entity.GetId("Weather", "How_To_Play");
            MemeoryFragmentID = VI.Entity.GetId("MemeoryFragment", "How_To_Play");
            EnemyID = VI.Entity.GetId("Enemy", "How_To_Play");

            c1 = VI.Entity.GetId("C1", "How_To_Play");
            c2 = VI.Entity.GetId("C2", "How_To_Play");
            c3 = VI.Entity.GetId("C3", "How_To_Play");
            c4 = VI.Entity.GetId("C4", "How_To_Play");
            pm1 = VI.Entity.GetId("PM1", "How_To_Play");
            pm2 = VI.Entity.GetId("PM2", "How_To_Play");
            pm3 = VI.Entity.GetId("PM3", "How_To_Play");
            pm4 = VI.Entity.GetId("PM4", "How_To_Play");
            pm5 = VI.Entity.GetId("PM5", "How_To_Play");
            pm6 = VI.Entity.GetId("PM6", "How_To_Play");
            pm7 = VI.Entity.GetId("PM7", "How_To_Play");
            d1 = VI.Entity.GetId("D1", "How_To_Play");
            d2 = VI.Entity.GetId("D2", "How_To_Play");
            d3 = VI.Entity.GetId("D3", "How_To_Play");
            d4 = VI.Entity.GetId("D4", "How_To_Play");
            d5 = VI.Entity.GetId("D5", "How_To_Play");
            d6 = VI.Entity.GetId("D6", "How_To_Play");
            d7 = VI.Entity.GetId("D7", "How_To_Play");
            d8 = VI.Entity.GetId("D8", "How_To_Play");
            cb1 = VI.Entity.GetId("CB1", "How_To_Play");
            cb2 = VI.Entity.GetId("CB2", "How_To_Play");
            cb3 = VI.Entity.GetId("CB3", "How_To_Play");
            w1 = VI.Entity.GetId("W1", "How_To_Play");
            w2 = VI.Entity.GetId("W2", "How_To_Play");
            w3 = VI.Entity.GetId("W3", "How_To_Play");
            w4 = VI.Entity.GetId("W4", "How_To_Play");
            w5 = VI.Entity.GetId("W5", "How_To_Play");
            w6 = VI.Entity.GetId("W6", "How_To_Play");
            w7 = VI.Entity.GetId("W7", "How_To_Play");
            w8 = VI.Entity.GetId("W8", "How_To_Play");
            mf1 = VI.Entity.GetId("MF1", "How_To_Play");
            mf2 = VI.Entity.GetId("MF2", "How_To_Play");
            mf3 = VI.Entity.GetId("MF3", "How_To_Play");
            mf4 = VI.Entity.GetId("MF4", "How_To_Play");
            e1 = VI.Entity.GetId("E1", "How_To_Play");
            e2 = VI.Entity.GetId("E2", "How_To_Play");
            e3 = VI.Entity.GetId("E3", "How_To_Play");
            e4 = VI.Entity.GetId("E4", "How_To_Play");
            e5 = VI.Entity.GetId("E5", "How_To_Play");
            //init = true;
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            Alive(_ENTITY);
            //init = false;
            VI.Animation.Transform.SetNext(c1, 0);
            VI.Animation.Transform.SetNext(c2, 0);
            VI.Animation.Transform.SetNext(c3, 0);
            VI.Animation.Transform.SetNext(c4, 0);
            VI.Animation.Transform.SetNext(pm1,0 );
            VI.Animation.Transform.SetNext(pm2,0 );
            VI.Animation.Transform.SetNext(pm3,0 );
            VI.Animation.Transform.SetNext(pm4,0 );
            VI.Animation.Transform.SetNext(pm5,0 );
            VI.Animation.Transform.SetNext(pm6,0 );
            VI.Animation.Transform.SetNext(pm7,0 );
            VI.Animation.Transform.SetNext(d1, 0);
            VI.Animation.Transform.SetNext(d2, 0);
            VI.Animation.Transform.SetNext(d3, 0);
            VI.Animation.Transform.SetNext(d4, 0);
            VI.Animation.Transform.SetNext(d5, 0);
            VI.Animation.Transform.SetNext(d6, 0);
            VI.Animation.Transform.SetNext(d7, 0);
            VI.Animation.Transform.SetNext(d8, 0);
            VI.Animation.Transform.SetNext(cb1,0 );
            VI.Animation.Transform.SetNext(cb2,0 );
            VI.Animation.Transform.SetNext(cb3,0 );
            VI.Animation.Transform.SetNext(w1, 0);
            VI.Animation.Transform.SetNext(w2, 0);
            VI.Animation.Transform.SetNext(w3, 0);
            VI.Animation.Transform.SetNext(w4, 0);
            VI.Animation.Transform.SetNext(w5, 0);
            VI.Animation.Transform.SetNext(w6, 0);
            VI.Animation.Transform.SetNext(w7, 0);
            VI.Animation.Transform.SetNext(w8, 0);
            VI.Animation.Transform.SetNext(mf1,0 );
            VI.Animation.Transform.SetNext(mf2,0 );
            VI.Animation.Transform.SetNext(mf3,0 );
            VI.Animation.Transform.SetNext(mf4,0 );
            VI.Animation.Transform.SetNext(e1, 0);
            VI.Animation.Transform.SetNext(e2, 0);
            VI.Animation.Transform.SetNext(e3, 0);
            VI.Animation.Transform.SetNext(e4, 0);
            VI.Animation.Transform.SetNext(e5, 0);
        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            //if (!init)
            //{
            //    Alive(_ENTITY);
            //    init = true;
            //}
            BackBtnID = VI.Entity.GetId("BackBtnHTP", "How_To_Play");
            ForwardBtnID = VI.Entity.GetId("ForwardBtnHTP", "How_To_Play");
            ControlsID = VI.Entity.GetId("Controls", "How_To_Play");
            e3 = VI.Entity.GetId("E3", "How_To_Play");
            if (VI.Input.Button.Released(BackBtnID))
            {
                Alive(_ENTITY);
                VI.Animation.Transform.SetNext(ControlsID, VI.Animation.Transform.GetCurrentIndex(ControlsID)-1);
                VI.Animation.Transform.SetNext(PlayerMovementID, VI.Animation.Transform.GetCurrentIndex(PlayerMovementID) - 1);
                VI.Animation.Transform.SetNext(DialogueID, VI.Animation.Transform.GetCurrentIndex(DialogueID) - 1);
                VI.Animation.Transform.SetNext(CrystalBallID, VI.Animation.Transform.GetCurrentIndex(CrystalBallID) - 1);
                VI.Animation.Transform.SetNext(WeatherID, VI.Animation.Transform.GetCurrentIndex(WeatherID) - 1);
                VI.Animation.Transform.SetNext(MemeoryFragmentID, VI.Animation.Transform.GetCurrentIndex(MemeoryFragmentID) - 1);
                VI.Animation.Transform.SetNext(EnemyID, VI.Animation.Transform.GetCurrentIndex(EnemyID) - 1);
                VI.Animation.Transform.Run(ControlsID);
                VI.Animation.Transform.Run(PlayerMovementID);
                VI.Animation.Transform.Run(DialogueID);
                VI.Animation.Transform.Run(CrystalBallID);
                VI.Animation.Transform.Run(WeatherID);
                VI.Animation.Transform.Run(MemeoryFragmentID);
                VI.Animation.Transform.Run(EnemyID);



                VI.Animation.Transform.SetNext(c1, VI.Animation.Transform.GetCurrentIndex(c1) - 1);
                VI.Animation.Transform.SetNext(c2, VI.Animation.Transform.GetCurrentIndex(c2) - 1);
                VI.Animation.Transform.SetNext(c3, VI.Animation.Transform.GetCurrentIndex(c3) - 1);
                VI.Animation.Transform.SetNext(c4, VI.Animation.Transform.GetCurrentIndex(c4) - 1);
                VI.Animation.Transform.SetNext(pm1, VI.Animation.Transform.GetCurrentIndex(pm1) - 1);
                VI.Animation.Transform.SetNext(pm2, VI.Animation.Transform.GetCurrentIndex(pm2) - 1);
                VI.Animation.Transform.SetNext(pm3, VI.Animation.Transform.GetCurrentIndex(pm3) - 1);
                VI.Animation.Transform.SetNext(pm4, VI.Animation.Transform.GetCurrentIndex(pm4) - 1);
                VI.Animation.Transform.SetNext(pm5, VI.Animation.Transform.GetCurrentIndex(pm5) - 1);
                VI.Animation.Transform.SetNext(pm6, VI.Animation.Transform.GetCurrentIndex(pm6) - 1);
                VI.Animation.Transform.SetNext(pm7, VI.Animation.Transform.GetCurrentIndex(pm7) - 1);
                VI.Animation.Transform.SetNext(d1, VI.Animation.Transform.GetCurrentIndex(d1) - 1);
                VI.Animation.Transform.SetNext(d2, VI.Animation.Transform.GetCurrentIndex(d2) - 1);
                VI.Animation.Transform.SetNext(d3, VI.Animation.Transform.GetCurrentIndex(d3) - 1);
                VI.Animation.Transform.SetNext(d4, VI.Animation.Transform.GetCurrentIndex(d4) - 1);
                VI.Animation.Transform.SetNext(d5, VI.Animation.Transform.GetCurrentIndex(d5) - 1);
                VI.Animation.Transform.SetNext(d6, VI.Animation.Transform.GetCurrentIndex(d6) - 1);
                VI.Animation.Transform.SetNext(d7, VI.Animation.Transform.GetCurrentIndex(d7) - 1);
                VI.Animation.Transform.SetNext(d8, VI.Animation.Transform.GetCurrentIndex(d8) - 1);
                VI.Animation.Transform.SetNext(cb1, VI.Animation.Transform.GetCurrentIndex(cb1) - 1);
                VI.Animation.Transform.SetNext(cb2, VI.Animation.Transform.GetCurrentIndex(cb2) - 1);
                VI.Animation.Transform.SetNext(cb3, VI.Animation.Transform.GetCurrentIndex(cb3) - 1);
                VI.Animation.Transform.SetNext(w1, VI.Animation.Transform.GetCurrentIndex(w1) - 1);
                VI.Animation.Transform.SetNext(w2, VI.Animation.Transform.GetCurrentIndex(w2) - 1);
                VI.Animation.Transform.SetNext(w3, VI.Animation.Transform.GetCurrentIndex(w3) - 1);
                VI.Animation.Transform.SetNext(w4, VI.Animation.Transform.GetCurrentIndex(w4) - 1);
                VI.Animation.Transform.SetNext(w5, VI.Animation.Transform.GetCurrentIndex(w5) - 1);
                VI.Animation.Transform.SetNext(w6, VI.Animation.Transform.GetCurrentIndex(w6) - 1);
                VI.Animation.Transform.SetNext(w7, VI.Animation.Transform.GetCurrentIndex(w7) - 1);
                VI.Animation.Transform.SetNext(w8, VI.Animation.Transform.GetCurrentIndex(w8) - 1);
                VI.Animation.Transform.SetNext(mf1, VI.Animation.Transform.GetCurrentIndex(mf1) - 1);
                VI.Animation.Transform.SetNext(mf2, VI.Animation.Transform.GetCurrentIndex(mf2) - 1);
                VI.Animation.Transform.SetNext(mf3, VI.Animation.Transform.GetCurrentIndex(mf3) - 1);
                VI.Animation.Transform.SetNext(mf4, VI.Animation.Transform.GetCurrentIndex(mf4) - 1);
                VI.Animation.Transform.SetNext(e1, VI.Animation.Transform.GetCurrentIndex(e1) - 1);
                VI.Animation.Transform.SetNext(e2, VI.Animation.Transform.GetCurrentIndex(e2) - 1);
                VI.Animation.Transform.SetNext(e3, VI.Animation.Transform.GetCurrentIndex(e3) - 1);
                VI.Animation.Transform.SetNext(e4, VI.Animation.Transform.GetCurrentIndex(e4) - 1);
                VI.Animation.Transform.SetNext(e5, VI.Animation.Transform.GetCurrentIndex(e5) - 1);


                VI.Animation.Transform.Run(c1);
                VI.Animation.Transform.Run(c2);
                VI.Animation.Transform.Run(c3);
                VI.Animation.Transform.Run(c4);
                VI.Animation.Transform.Run(pm1);
                VI.Animation.Transform.Run(pm2);
                VI.Animation.Transform.Run(pm3);
                VI.Animation.Transform.Run(pm4);
                VI.Animation.Transform.Run(pm5);
                VI.Animation.Transform.Run(pm6);
                VI.Animation.Transform.Run(pm7);
                VI.Animation.Transform.Run(d1);
                VI.Animation.Transform.Run(d2);
                VI.Animation.Transform.Run(d3);
                VI.Animation.Transform.Run(d4);
                VI.Animation.Transform.Run(d5);
                VI.Animation.Transform.Run(d6);
                VI.Animation.Transform.Run(d7);
                VI.Animation.Transform.Run(d8);
                VI.Animation.Transform.Run(cb1);
                VI.Animation.Transform.Run(cb2);
                VI.Animation.Transform.Run(cb3);
                VI.Animation.Transform.Run(w1);
                VI.Animation.Transform.Run(w2);
                VI.Animation.Transform.Run(w3);
                VI.Animation.Transform.Run(w4);
                VI.Animation.Transform.Run(w5);
                VI.Animation.Transform.Run(w6);
                VI.Animation.Transform.Run(w7);
                VI.Animation.Transform.Run(w8);
                VI.Animation.Transform.Run(mf1);
                VI.Animation.Transform.Run(mf2);
                VI.Animation.Transform.Run(mf3);
                VI.Animation.Transform.Run(mf4);
                VI.Animation.Transform.Run(e1);
                VI.Animation.Transform.Run(e2);
                VI.Animation.Transform.Run(e3);
                VI.Animation.Transform.Run(e4);
                VI.Animation.Transform.Run(e5);



            }
            if (VI.Animation.Transform.GetCurrentIndex(ControlsID) == 6)
            {
                VI.Entity.SetActive(ForwardBtnID, false);
                time++;
                //animate health bar
                if (time > 100)
                {
                    time = 0;
                    if (VI.Animation.SpriteSheet.SheetIndex.Get(e3) < 5)
                        VI.Animation.SpriteSheet.SheetIndex.Set(e3, VI.Animation.SpriteSheet.SheetIndex.Get(e3) + 1);
                    else
                        VI.Animation.SpriteSheet.SheetIndex.Set(e3, 0);
                }
            }
            else
                VI.Entity.SetActive(ForwardBtnID, true);
        }

        public void FixedUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }

        public void LateUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public void Exit(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            //init = false;
        }

        public void Dead(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }
    }
}
