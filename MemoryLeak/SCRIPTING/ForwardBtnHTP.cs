/*!*****************************************************************************
\file ForwardBtnHTP.cs
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 10-03-2023
\brief
Controls the forward button
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;
using VI;

namespace BonVoyage {
    public class ForwardBtnHTP : BaseScript
    {
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
            pm1= VI.Entity.GetId("PM1", "How_To_Play");
            pm2= VI.Entity.GetId("PM2", "How_To_Play");
            pm3= VI.Entity.GetId("PM3", "How_To_Play");
            pm4= VI.Entity.GetId("PM4", "How_To_Play");
            pm5= VI.Entity.GetId("PM5", "How_To_Play");
            pm6= VI.Entity.GetId("PM6", "How_To_Play");
            pm7= VI.Entity.GetId("PM7", "How_To_Play");
            d1 = VI.Entity.GetId("D1", "How_To_Play");
            d2 = VI.Entity.GetId("D2", "How_To_Play");
            d3 = VI.Entity.GetId("D3", "How_To_Play");
            d4 = VI.Entity.GetId("D4", "How_To_Play");
            d5 = VI.Entity.GetId("D5", "How_To_Play");
            d6 = VI.Entity.GetId("D6", "How_To_Play");
            d7 = VI.Entity.GetId("D7", "How_To_Play");
            d8 = VI.Entity.GetId("D8", "How_To_Play");
            cb1= VI.Entity.GetId("CB1", "How_To_Play");
            cb2= VI.Entity.GetId("CB2", "How_To_Play");
            cb3= VI.Entity.GetId("CB3", "How_To_Play");
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
            VI.Animation.Transform.SetNext(pm1, 0);
            VI.Animation.Transform.SetNext(pm2, 0);
            VI.Animation.Transform.SetNext(pm3, 0);
            VI.Animation.Transform.SetNext(pm4, 0);
            VI.Animation.Transform.SetNext(pm5, 0);
            VI.Animation.Transform.SetNext(pm6, 0);
            VI.Animation.Transform.SetNext(pm7, 0);
            VI.Animation.Transform.SetNext(d1, 0);
            VI.Animation.Transform.SetNext(d2, 0);
            VI.Animation.Transform.SetNext(d3, 0);
            VI.Animation.Transform.SetNext(d4, 0);
            VI.Animation.Transform.SetNext(d5, 0);
            VI.Animation.Transform.SetNext(d6, 0);
            VI.Animation.Transform.SetNext(d7, 0);
            VI.Animation.Transform.SetNext(d8, 0);
            VI.Animation.Transform.SetNext(cb1, 0);
            VI.Animation.Transform.SetNext(cb2, 0);
            VI.Animation.Transform.SetNext(cb3, 0);
            VI.Animation.Transform.SetNext(w1, 0);
            VI.Animation.Transform.SetNext(w2, 0);
            VI.Animation.Transform.SetNext(w3, 0);
            VI.Animation.Transform.SetNext(w4, 0);
            VI.Animation.Transform.SetNext(w5, 0);
            VI.Animation.Transform.SetNext(w6, 0);
            VI.Animation.Transform.SetNext(w7, 0);
            VI.Animation.Transform.SetNext(w8, 0);
            VI.Animation.Transform.SetNext(mf1, 0);
            VI.Animation.Transform.SetNext(mf2, 0);
            VI.Animation.Transform.SetNext(mf3, 0);
            VI.Animation.Transform.SetNext(mf4, 0);
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
            //if (!init)
            //{
            //    Alive(_ENTITY);
                
            //    init = true;
            //}
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            BackBtnID = VI.Entity.GetId("BackBtnHTP", "How_To_Play");
            ForwardBtnID = VI.Entity.GetId("ForwardBtnHTP", "How_To_Play");
            ControlsID = VI.Entity.GetId("Controls", "How_To_Play");
            if (VI.Input.Button.Released(ForwardBtnID))
            {
                Alive(_ENTITY);
                VI.Animation.Transform.Run(ControlsID);
                VI.Animation.Transform.Run(PlayerMovementID);
                VI.Animation.Transform.Run(DialogueID);
                VI.Animation.Transform.Run(CrystalBallID);
                VI.Animation.Transform.Run(WeatherID);
                VI.Animation.Transform.Run(MemeoryFragmentID);
                VI.Animation.Transform.Run(EnemyID);


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
            if (VI.Animation.Transform.GetCurrentIndex(ControlsID) == 0)
            {
                VI.Entity.SetActive(BackBtnID, false);
            }
            else
                VI.Entity.SetActive(BackBtnID, true);
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
