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
            if (!init)
            {
                Alive(_ENTITY);
                
                init = true;
            }
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
            //
            Console.WriteLine("FORWARDID:" + ForwardBtnID);
            if (VI.Input.Button.Released(ForwardBtnID))
            {
                VI.Animation.Transform.Run(ControlsID);
                VI.Animation.Transform.Run(PlayerMovementID);
                VI.Animation.Transform.Run(DialogueID);
                VI.Animation.Transform.Run(CrystalBallID);
                VI.Animation.Transform.Run(WeatherID);
                VI.Animation.Transform.Run(MemeoryFragmentID);
                VI.Animation.Transform.Run(EnemyID);
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

        }

        public void Dead(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!

        }
    }
}
