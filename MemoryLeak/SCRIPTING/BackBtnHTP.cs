using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class BackBtnHTP : BaseScript
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
        bool init = false;
        
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
        }

        public void Init(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            
        }

        public void EarlyUpdate(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            if (!init)
            {
                Alive(_ENTITY);
                init = true;
            }
            if (VI.Input.Button.Released(BackBtnID))
            {
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
            }
            if (VI.Animation.Transform.GetCurrentIndex(ControlsID) == 6)
            {
                VI.Entity.SetActive(ForwardBtnID, false);
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

        }

        public void Dead(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }
    }
}
