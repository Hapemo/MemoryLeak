using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class Level1IntroBoxScript : BaseScript
    {
        private bool RunDialogue;

        private int PlayerID;

        private int UIHPBarID;
        private int UIMemoryFragmentID;
        private int UIMemoryFragmentScreenID;
        private int UIFragment1ObjID;
        private int UICycleMapID;
        private int UIMiniMapID;
        private int UIEnemyMapID;
        private int UIWeatherMapID;
        private int UIWeatherTextID;
        private int UIObjectiveTextID;

        private int DialogueUIP1ID;
        private int DialogueUIPP1ID;
        private int DialogueUIPP2ID;
        private int DialogueUIG1ID;

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void Init(int _ENTITY) {
            PlayerID = VI.Entity.s_GetId("Boat", VI.GameState.GetName());
            RunDialogue = true;

            UIHPBarID = VI.Entity.s_GetId("hpbar", "Dialogue");
            UIMemoryFragmentID = VI.Entity.s_GetId("memoryfragment", "Dialogue");
            UIMemoryFragmentScreenID = VI.Entity.s_GetId("memoryfragmentscreen", "Dialogue");
            UIFragment1ObjID = VI.Entity.s_GetId("fragment1obj", "Dialogue");
            UICycleMapID = VI.Entity.s_GetId("cyclemap", "Dialogue");
            UIMiniMapID = VI.Entity.s_GetId("minimap", "Dialogue");
            UIEnemyMapID = VI.Entity.s_GetId("enemymap", "Dialogue");
            UIWeatherMapID = VI.Entity.s_GetId("weathermap", "Dialogue");
            UIWeatherTextID = VI.Entity.s_GetId("weathertext", "Dialogue");
            UIObjectiveTextID = VI.Entity.s_GetId("objectivetext", "Dialogue");

            DialogueUIP1ID = VI.Entity.s_GetId("P1", "Dialogue");
            DialogueUIPP1ID = VI.Entity.s_GetId("PP1", "Dialogue");
            DialogueUIPP2ID = VI.Entity.s_GetId("PP2", "Dialogue");
            DialogueUIG1ID = VI.Entity.s_GetId("G1", "Dialogue"); 

        }

        public void Update(int _ENTITY) {
            if (VI.Physics.EntitiesCollided(PlayerID, _ENTITY))
            {
                if (RunDialogue)
                {
                    PlayerScript.PlayerInDialogue = true;
                    //RunIntroDialogue = RunDialog();
                }
            }
        }

        public void FixedUpdate(int _ENTITY) {

        }

        public void Exit(int _ENTITY) {

        }

        public void Dead(int _ENTITY) {

        }

        public void DisableUI()
        {
            VI.Entity.Deactivate(UIHPBarID);
            VI.Entity.Deactivate(UIMemoryFragmentID);
            VI.Entity.Deactivate(UIMemoryFragmentScreenID);
            VI.Entity.Deactivate(UIFragment1ObjID);
            VI.Entity.Deactivate(UICycleMapID);
            VI.Entity.Deactivate(UIMiniMapID);
            VI.Entity.Deactivate(UIEnemyMapID);
            VI.Entity.Deactivate(UIWeatherMapID);
            VI.Entity.Deactivate(UIWeatherTextID);
            VI.Entity.Deactivate(UIObjectiveTextID);
        }

        public void EnableUI()
        {
            VI.Entity.Activate(UIHPBarID);
            VI.Entity.Activate(UIMemoryFragmentID);
            VI.Entity.Activate(UICycleMapID);
            VI.Entity.Activate(UIObjectiveTextID);
        }

        // Based on the current dialog ID, move to the next one. Can input choice if there is a choice selection, by default it's 1
        public void MoveToNextDialog(int choice = 1)
        {
            if (choice == 1) 
                VI.Dialogue.Current.SetTo(VI.Dialogue.Next.GetId());
            else 
                VI.Dialogue.Current.SetTo(VI.Dialogue.Choice.Second(VI.Dialogue.Current.GetId()));
        }

        // Get the texts of the next dialog, able to input 1 or 2 to get the different choices
        public string GetNextDialog(int choice = 1)
        {
            int ID = 0;
            if (choice == 1)
            {
                ID = VI.Dialogue.Next.GetId();
                //Console.WriteLine("Choice 1 is: " + ID);
            }
            else
            {
                ID = VI.Dialogue.Choice.Second(VI.Dialogue.Current.GetId());
                //Console.WriteLine("Choice 2 is: " + ID);
            }
            //Console.WriteLine("Resultant line is: " + VI.Dialogue.GetLine(ID));
            return VI.Dialogue.GetLine(ID);
        }
    }
}
