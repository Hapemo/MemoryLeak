using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class HowToPlayButton : BaseScript
    {
        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void Init(int _ENTITY) {

        }

        public void EarlyUpdate(int _ENTITY) {
        
        }

        public void Update(int _ENTITY) {
            THIS.StoreId(_ENTITY);
            if (THIS.Input.Button.Released())
            {
                VI.Scene.Pause("Menu_Main");
                VI.Scene.Pause("Settings");
                VI.Scene.Pause("Credits");
                VI.Scene.Pause("Quit Confirmation");
                VI.Scene.Pause("TransitionScene");

                VI.Scene.Play("How_To_Play");
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
