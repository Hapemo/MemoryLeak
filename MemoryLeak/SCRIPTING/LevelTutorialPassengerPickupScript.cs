using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class LevelTutorialPassengerPickupScript : BaseScript
    {
        private int PlayerID;
        private bool RunDialogueFlag;

        private int DialogueUIP1ID;
        private int DialogueUIPP1ID;
        private int DialogueUIPP2ID;
        private int DialogueUIG1ID;
        private int UIObjectiveTextID;

        private bool DialogueChoiceFlag;
        private bool DialogueUpdateFlag;

        public void Alive(int _ENTITY) {
            THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
        }

        public void Init(int _ENTITY) {
            RunDialogueFlag = true;
            PlayerID = VI.Entity.GetId("Boat", VI.GameState.GetName());

            DialogueUIP1ID = VI.Entity.GetId("P1", "TutorialDialogue");
            DialogueUIPP1ID = VI.Entity.GetId("PP1", "TutorialDialogue");
            DialogueUIPP2ID = VI.Entity.GetId("PP2", "TutorialDialogue");
            DialogueUIG1ID = VI.Entity.GetId("G1", "TutorialDialogue");

            UIObjectiveTextID = VI.Entity.GetId("objectivetext", "TutorialDialogue");

            DialogueChoiceFlag = false;
            DialogueUpdateFlag = false;
        }

        public void Update(int _ENTITY) {
            if (VI.Physics.EntitiesCollided(PlayerID, _ENTITY))
            {
                if (RunDialogueFlag)
                {
                    PlayerScript.PlayerInDialogue = true;
                    RunDialogueFlag = RunDialog(DialogueUIP1ID, DialogueUIG1ID, DialogueUIPP1ID, DialogueUIPP2ID, "Dialogue SceneIntro 1");
                    if (!RunDialogueFlag)
                    {
                        VI.Text.Update(UIObjectiveTextID, "Objective: Push Forward & Explore");
                    }
                }

                if (!RunDialogueFlag)
                {
                    TextAlignChoices(UIObjectiveTextID, 500, 380, 530, 51.0f, 20, 10);
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

        }

        public void EnableUI()
        {

        }

        // int scaleX           - This is the default width of button
        // int posX             - This is the center X coordinate of button (500)
        // int posY             - This is the center Y coordinate of button. If it's choice, it's the middle of both buttons (-25)
        // int spaceing         - Spacing between choice button edge from middle, useless for single button.
        // int perLineScaleY    - This is the increment for one additional line
        // int textXSpacing     - This is the spacing of the text from the left edge of the box 
        // int textYSpacing     - This is the spacing of the text from the top edge of the box 
        public void TextAlignChoices(int entityname, float posX, float posY, float scaleX = 500, float perLineScaleY = 51, float textXSpacing = 50, float textYSpacing = 50, int choice = 0, float spacing = 15)
        {
            int additionalLines = VI.Text.GetLineCount(entityname) - 1;
            //Console.WriteLine("lines: " + additionalLines);
            //float scaleY = perLineScaleY;         // This is the default height of button, will changing with respect to line count
            perLineScaleY *= VI.Text.Scale.Get(entityname);

            VI.Transform.Scale.SetX(entityname, scaleX);
            VI.Transform.Scale.SetY(entityname, perLineScaleY * (1 + additionalLines) + textYSpacing * 2);

            // If it's a choice textbox, posY is the middle of both texts
            if (choice == 1) posY = posY + spacing + perLineScaleY * (additionalLines + 1);
            else if (choice == 2) posY = posY - spacing - perLineScaleY * (additionalLines + 1);

            float finalPosY = posY - (perLineScaleY * additionalLines) / 2;

            VI.Transform.Position.SetX(entityname, posX);
            VI.Transform.Position.SetY(entityname, finalPosY);

            float textY = perLineScaleY * additionalLines / 2 - perLineScaleY / 2;
            float magicNumber = 10.0f * VI.Text.Scale.Get(entityname);
            VI.Text.Offset.Set(entityname, -scaleX / 2 + textXSpacing, textY + magicNumber);
        }

        public bool RunDialog(int player, int notPlayer, int choice1, int choice2, string dialogFile)
        {
            if (!PlayerScript.PlayerInDialogue)
            {
                DisableUI();
                // Load Little Girl Talking
                VI.Dialogue.LoadScript(dialogFile);
                VI.Dialogue.Current.SetTo(1);

                // Setting default P1, PP1, PP2 positions
                VI.Transform.Position.SetX(choice1, 500);
                VI.Transform.Position.SetY(choice1, 46);
                VI.Transform.Position.SetX(choice2, 500);
                VI.Transform.Position.SetY(choice2, -90);
                VI.Transform.Position.SetX(player, 450);
                VI.Transform.Position.SetY(player, 5);

                // Activate dialogue
                int firstSpeaker;
                if (VI.Dialogue.Speaker.IsPlayer(1)) 
                    firstSpeaker = player;
                else 
                    firstSpeaker = notPlayer;

                VI.Entity.Activate(firstSpeaker);
                VI.Text.Update(firstSpeaker, VI.Dialogue.GetLine(VI.Dialogue.Current.GetId()));

                if (VI.Dialogue.Speaker.IsPlayer(1)) 
                    TextAlignChoices(player, 450, 5, 500, 51, 20, 20);
                else 
                    TextAlignChoices(notPlayer, -387, 330, 740, 51, 20, 20);

                //camZoomingIn = true;
                PlayerScript.PlayerInDialogue = true;
            }

            // Button click set flags
            if (DialogueChoiceFlag)
            {
                if (VI.Input.Button.Released(choice1) || VI.Input.Button.Released(choice2)) 
                    DialogueUpdateFlag = true;
            }
            else if (VI.Input.Button.Released(player) || VI.Input.Button.Released(notPlayer)) 
                DialogueUpdateFlag = true;

            // Logic done using those flags
            if (DialogueUpdateFlag)
            {
                DialogueUpdateFlag = false;

                // Finish dialog
                if (VI.Dialogue.Next.GetId() == 0)
                {
                    DeactivateDialogBox(player, notPlayer, choice1, choice2);
                    PlayerScript.PlayerInDialogue = false;
                    //camZoomingOut = true;
                    EnableUI();
                    //Console.WriteLine("finished dialog");
                    return false;
                }

                //Console.WriteLine("Moving on from: " + VI.Dialogue.Current.GetId());
                if (DialogueChoiceFlag)
                {
                    //Console.WriteLine("It's a choice dialog");
                    DialogueChoiceFlag = false;
                    if (VI.Input.Button.Released(choice2))
                    {
                        MoveToNextDialog(2);
                        //Console.WriteLine("Choice 2 selected, moving to: " + VI.Dialogue.Current.GetId());
                    }
                    else
                    {
                        MoveToNextDialog(1);
                        //Console.WriteLine("Choice 1 selected, moving to: " + VI.Dialogue.Current.GetId());
                    }
                    VI.Entity.Deactivate(choice1);
                    VI.Entity.Deactivate(choice2);
                }
                MoveToNextDialog(1);
                //Console.WriteLine("Moving to: " + VI.Dialogue.Current.GetId());

                if (VI.Dialogue.Speaker.IsPlayer(VI.Dialogue.Current.GetId()))
                {
                    VI.Entity.Activate(player);
                    VI.Entity.Deactivate(notPlayer);
                    VI.Text.Update(player, VI.Dialogue.GetLine(VI.Dialogue.Current.GetId()));
                    TextAlignChoices(player, 450, 5, 500, 51, 20, 20);
                }
                else
                {
                    VI.Entity.Activate(notPlayer);
                    VI.Entity.Deactivate(player);
                    VI.Text.Update(notPlayer, VI.Dialogue.GetLine(VI.Dialogue.Current.GetId()));
                    TextAlignChoices(notPlayer, -387, 330, 740, 51, 20, 20);
                }

                if (VI.Dialogue.Choice.Second(VI.Dialogue.Current.GetId()) != 0)
                {
                    //Console.WriteLine("This dialog is a choice dialog: " + VI.Dialogue.Current.GetId());
                    VI.Entity.Activate(choice1);
                    VI.Entity.Activate(choice2);
                    VI.Text.Update(choice1, GetNextDialog(1));
                    VI.Text.Update(choice2, GetNextDialog(2));
                    TextAlignChoices(choice1, 500, -25, 500, 51, 40, 25, 1);
                    TextAlignChoices(choice2, 500, -25, 500, 51, 40, 25, 2);
                    DialogueChoiceFlag = true;
                }
            }
            return true;
        }

        public void DeactivateDialogBox(int player, int notPlayer, int choice1, int choice2)
        {
            VI.Entity.Deactivate(player);
            VI.Entity.Deactivate(notPlayer);
            VI.Entity.Deactivate(choice1);
            VI.Entity.Deactivate(choice2);
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
