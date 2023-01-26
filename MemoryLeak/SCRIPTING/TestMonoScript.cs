using System;
using System.Runtime.CompilerServices;

namespace BonVoyage
{
    public class TestMonoScript
    {
        private bool starttalking;
        private int currentdialogueid;
        private int clickcount;

        public void Init()
        {
            starttalking = false;
            currentdialogueid = 1;

            InternalCalls.LoadDialogs("Dialogue LittleGirl 0"); // Loading dialogue file

            CameraZoomIn();
        }

        public void Update()
        {
            #region newdialoguewip
            /*
            if (InternalCalls.EntitiesCollided("Boat", "LittleGirlBox", "Level1")) // player enter girl collider
            {
                // freeze player
                if (!starttalking)
                {
                CameraZoomIn();
                InternalCalls.EntityActivate("LittleGirlDialogue", "Dialogue");
                InternalCalls.UpdateText("LittleGirlDialogue", "Dialogue", InternalCalls.GetDialogue(currentdialogueid));
                starttalking = true;
                }

                if (InternalCalls.HasChoice(currentdialogueid))
                {
                    InternalCalls.EntityActivate("I2", "Dialogue");
                    InternalCalls.EntityActivate("I2", "Dialogue");
                    InternalCalls.UpdateText("FirstChoice", "Dialogue", InternalCalls.GetDialogue(InternalCalls.GetChoice1(currentdialogueid)));
                    InternalCalls.UpdateText("SecondChoioe", "Dialogue", InternalCalls.GetDialogue(InternalCalls.GetChoice2(currentdialogueid)));

                    //if first choice click 
                }
                else
                {
                    if ((InternalCalls.ButtonReleased("LittleGirlDialogue", "Dialogue")) == true)
                    {
                        currentdialogueid = InternalCalls.GetNextDialogueID(currentdialogueid);
                        InternalCalls.UpdateText("LittleGirlDialogue", "Dialogue", InternalCalls.GetDialogue(currentdialogueid));
                    }
                }
            }

            if (InternalCalls.HasChoice(currentdialogueid))
            {
                
                // activate both button, update text for both\
                InternalCalls.UpdateText("FirstChoice", "Dialogue", InternalCalls.GetDialogue(InternalCalls.GetChoice1(currentdialogueid)));
                InternalCalls.UpdateText("SecondChoioe", "Dialogue", InternalCalls.GetDialogue(InternalCalls.GetChoice2(currentdialogueid)));

                //if first choice click 
            }

            //InternalCalls.UpdateText("I2", "Dialogue", InternalCalls.GetDialogue(currentdialogueid));

            */

            #endregion

            #region Intro Dialogue
            if (InternalCalls.EntitiesCollided("Boat", "IntroBox", "Level1")) {
                LockPosition(160, 120);

                if (!starttalking) {
                    DisableUI();
                    if (InternalCalls.EntityIsActive("I2", "Dialogue") == false) {
                        InternalCalls.EntityActivate("I1", "Dialogue");
                        InternalCalls.UpdateText("I1", "Dialogue", "Where am I?");
                    }
                    starttalking = true;
                }

                if ((InternalCalls.ButtonReleased("I1", "Dialogue")) == true) {
                    InternalCalls.EntityDeactivate("I1", "Dialogue");
                    InternalCalls.EntityActivate("I2", "Dialogue");
                    InternalCalls.UpdateText("I2", "Dialogue", "Maybe that girl knows...");
                }

                if ((InternalCalls.ButtonReleased("I2", "Dialogue")) == true) {
                    InternalCalls.EntityDeactivate("I2", "Dialogue");
                    InternalCalls.EntityDeactivate("IntroBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                }
            }
            #endregion

            #region Little Girl Dialogue
            if (InternalCalls.EntitiesCollided("Boat", "LittleGirlBox", "Level1"))
            {
                LockPosition(-295, -85);

                if (!starttalking)
                {
                    DisableUI();
                    if (InternalCalls.EntityIsActive("G2", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G3", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G4", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G5", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G6", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G7", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G8", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G9", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G10", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G11", "Dialogue") == false
                        && InternalCalls.EntityIsActive("P1", "Dialogue") == false
                        && InternalCalls.EntityIsActive("P2", "Dialogue") == false
                        && InternalCalls.EntityIsActive("P3", "Dialogue") == false
                        && InternalCalls.EntityIsActive("P4", "Dialogue") == false
                        && InternalCalls.EntityIsActive("P5", "Dialogue") == false
                        && InternalCalls.EntityIsActive("P6", "Dialogue") == false)
                    {
                        InternalCalls.EntityActivate("G1", "Dialogue");
                        InternalCalls.UpdateText("G1", "Dialogue", "At last we meet again!");
                    }
                    CameraZoomIn();
                    starttalking = true;
                }

                if ((InternalCalls.ButtonReleased("G1", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G1", "Dialogue");
                    InternalCalls.EntityActivate("G2", "Dialogue");
                    InternalCalls.UpdateText("G2", "Dialogue", "I've been waiting for you!");
                }

                if ((InternalCalls.ButtonReleased("G2", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G2", "Dialogue");
                    InternalCalls.EntityActivate("G3", "Dialogue");
                    InternalCalls.UpdateText("G3", "Dialogue", "What would you like to do? Maybe play or remininsce?");
                    InternalCalls.EntityActivate("PP1", "Dialogue");
                    InternalCalls.EntityActivate("PP2", "Dialogue");
                    InternalCalls.UpdateText("PP1", "Dialogue", "Play...");
                    InternalCalls.UpdateText("PP2", "Dialogue", "Reminisce...");
                }

                //first choice start
                if ((InternalCalls.ButtonReleased("PP1", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP1", "Dialogue");
                    InternalCalls.EntityDeactivate("PP2", "Dialogue");
                    InternalCalls.EntityActivate("P1", "Dialogue");
                    InternalCalls.UpdateText("P1", "Dialogue", "I'd like to play");
                }

                if ((InternalCalls.ButtonReleased("PP2", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP1", "Dialogue");
                    InternalCalls.EntityDeactivate("PP2", "Dialogue");
                    InternalCalls.EntityActivate("P2", "Dialogue");
                    InternalCalls.UpdateText("P2", "Dialogue", "I'd like to remininsce.");
                }
                //first choice end

                if ((InternalCalls.ButtonReleased("P1", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("P1", "Dialogue");
                    InternalCalls.EntityActivate("G4", "Dialogue");
                    InternalCalls.UpdateText("G4", "Dialogue", "Let's play a game where you hold your hands out and I'll give you something!");
                }

                if ((InternalCalls.ButtonReleased("P2", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("P2", "Dialogue");
                    InternalCalls.EntityActivate("G6", "Dialogue");
                    InternalCalls.UpdateText("G6", "Dialogue", "We have plenty of time to reminsce! There's something I want to show you!");
                }

                if ((InternalCalls.ButtonReleased("G4", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G4", "Dialogue");
                    InternalCalls.EntityActivate("G5", "Dialogue");
                    InternalCalls.UpdateText("G5", "Dialogue", "Well, let's play together now! Or are you supposed to be doing something else now?");
                    InternalCalls.EntityActivate("PP3", "Dialogue");
                    InternalCalls.EntityActivate("PP4", "Dialogue");
                    InternalCalls.UpdateText("PP3", "Dialogue", "Do what...");
                    InternalCalls.UpdateText("PP4", "Dialogue", "Where am I...");
                }

                if ((InternalCalls.ButtonReleased("G6", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G6", "Dialogue");
                    InternalCalls.EntityActivate("G7", "Dialogue");
                    InternalCalls.UpdateText("G7", "Dialogue", "Ain't it pretty? Have you seen one before? Do you know what it's called?");
                    InternalCalls.EntityActivate("PP5", "Dialogue");
                    InternalCalls.EntityActivate("PP6", "Dialogue");
                    InternalCalls.UpdateText("PP5", "Dialogue", "Yes...");
                    InternalCalls.UpdateText("PP6", "Dialogue", "No...");
                }

                // second choice from first choice
                if ((InternalCalls.ButtonReleased("PP3", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("PP3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP4", "Dialogue");
                    InternalCalls.EntityActivate("P3", "Dialogue");
                    InternalCalls.UpdateText("P3", "Dialogue", "What am I supposed to do?");
                }

                if ((InternalCalls.ButtonReleased("P3", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("P3", "Dialogue");
                    InternalCalls.EntityDeactivate("G5", "Dialogue");
                    InternalCalls.EntityActivate("G8", "Dialogue");
                    InternalCalls.UpdateText("G8", "Dialogue", "The people said you're a ferryman. Quick, a passenger is waiting! We will meet again...");
                }

                if ((InternalCalls.ButtonReleased("G8", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G8", "Dialogue");
                    InternalCalls.EntityDeactivate("LittleGirlBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                }

                if ((InternalCalls.ButtonReleased("PP4", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("PP3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP4", "Dialogue");
                    InternalCalls.EntityActivate("P4", "Dialogue");
                    InternalCalls.UpdateText("P4", "Dialogue", "I don't even know where I am.");
                }

                if ((InternalCalls.ButtonReleased("P4", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("P4", "Dialogue");
                    InternalCalls.EntityDeactivate("G5", "Dialogue");
                    InternalCalls.EntityActivate("G9", "Dialogue");
                    InternalCalls.UpdateText("G9", "Dialogue", "We're currently at Cordelia! It's said this place holds special memories, so explore around! We will meet again...");
                }

                if ((InternalCalls.ButtonReleased("G9", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G9", "Dialogue");
                    InternalCalls.EntityDeactivate("LittleGirlBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                }

                // second choice from second choice
                if ((InternalCalls.ButtonReleased("PP5", "Dialogue")) == true)
                {

                    InternalCalls.EntityDeactivate("PP5", "Dialogue");
                    InternalCalls.EntityDeactivate("PP6", "Dialogue");
                    InternalCalls.EntityActivate("P5", "Dialogue");
                    InternalCalls.UpdateText("P5", "Dialogue", "Yes, I think.");
                }

                if ((InternalCalls.ButtonReleased("P5", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("P5", "Dialogue");
                    InternalCalls.EntityDeactivate("G7", "Dialogue");
                    InternalCalls.EntityActivate("G10", "Dialogue");
                    InternalCalls.UpdateText("G10", "Dialogue", "So you remember the sea conches! Don't forget them now! We will meet again...");
                }

                if ((InternalCalls.ButtonReleased("G10", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G10", "Dialogue");
                    InternalCalls.EntityDeactivate("LittleGirlBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                }

                if ((InternalCalls.ButtonReleased("PP6", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("PP5", "Dialogue");
                    InternalCalls.EntityDeactivate("PP6", "Dialogue");
                    InternalCalls.EntityActivate("P6", "Dialogue");
                    InternalCalls.UpdateText("P6", "Dialogue", "No, I haven't.");
                }

                if ((InternalCalls.ButtonReleased("P6", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("P6", "Dialogue");
                    InternalCalls.EntityDeactivate("G7", "Dialogue");
                    InternalCalls.EntityActivate("G11", "Dialogue");
                    InternalCalls.UpdateText("G11", "Dialogue", "These are called sea conches, and are known to store important memories of the past. We will meet again...");
                }

                if ((InternalCalls.ButtonReleased("G11", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G11", "Dialogue");
                    InternalCalls.EntityDeactivate("LittleGirlBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                }
            }
            #endregion

            #region Passenger 1 Dialogue
            if (InternalCalls.EntitiesCollided("Boat", "PassengerBox", "Level1"))
            {
                InternalCalls.EntityDeactivate("hpbar", "Dialogue");
                InternalCalls.SetPosX("Boat", "Level1", -1240.0f);
                InternalCalls.SetPosY("Boat", "Level1", 670.0f);

                if (!starttalking)
                {
                    DisableUI();
                    if (InternalCalls.EntityIsActive("G2", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G3", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G4", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G5", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G6", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G7", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G8", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G9", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G10", "Dialogue") == false
                        && InternalCalls.EntityIsActive("G11", "Dialogue") == false
                        && InternalCalls.EntityIsActive("P1", "Dialogue") == false
                        && InternalCalls.EntityIsActive("P2", "Dialogue") == false
                        && InternalCalls.EntityIsActive("P3", "Dialogue") == false
                        && InternalCalls.EntityIsActive("P4", "Dialogue") == false
                        && InternalCalls.EntityIsActive("P5", "Dialogue") == false
                        && InternalCalls.EntityIsActive("P6", "Dialogue") == false)
                    {
                        InternalCalls.EntityActivate("G1", "Dialogue");
                        InternalCalls.UpdateText("G1", "Dialogue", "At last we meet again!");
                    }
                    CameraZoomIn();
                    starttalking = true;
                }

                if ((InternalCalls.ButtonReleased("G1", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G1", "Dialogue");
                    InternalCalls.EntityActivate("G2", "Dialogue");
                    InternalCalls.UpdateText("G2", "Dialogue", "I've been waiting for you!");
                }

                if ((InternalCalls.ButtonReleased("G2", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G2", "Dialogue");
                    InternalCalls.EntityActivate("G3", "Dialogue");
                    InternalCalls.UpdateText("G3", "Dialogue", "What would you like to do? Maybe play or remininsce?");
                    InternalCalls.EntityActivate("PP1", "Dialogue");
                    InternalCalls.EntityActivate("PP2", "Dialogue");
                    InternalCalls.UpdateText("PP1", "Dialogue", "Play...");
                    InternalCalls.UpdateText("PP2", "Dialogue", "Reminisce...");
                }

                //first choice start
                if ((InternalCalls.ButtonReleased("PP1", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP1", "Dialogue");
                    InternalCalls.EntityDeactivate("PP2", "Dialogue");
                    InternalCalls.EntityActivate("P1", "Dialogue");
                    InternalCalls.UpdateText("P1", "Dialogue", "I'd like to play");
                }

                if ((InternalCalls.ButtonReleased("PP2", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP1", "Dialogue");
                    InternalCalls.EntityDeactivate("PP2", "Dialogue");
                    InternalCalls.EntityActivate("P2", "Dialogue");
                    InternalCalls.UpdateText("P2", "Dialogue", "I'd like to remininsce.");
                }
                //first choice end

                if ((InternalCalls.ButtonReleased("P1", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("P1", "Dialogue");
                    InternalCalls.EntityActivate("G4", "Dialogue");
                    InternalCalls.UpdateText("G4", "Dialogue", "Let's play a game where you hold your hands out and I'll give you something!");
                }

                if ((InternalCalls.ButtonReleased("P2", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("P2", "Dialogue");
                    InternalCalls.EntityActivate("G6", "Dialogue");
                    InternalCalls.UpdateText("G6", "Dialogue", "We have plenty of time to reminsce! There's something I want to show you!");
                }

                if ((InternalCalls.ButtonReleased("G4", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G4", "Dialogue");
                    InternalCalls.EntityActivate("G5", "Dialogue");
                    InternalCalls.UpdateText("G5", "Dialogue", "Well, let's play together now! Or are you supposed to be doing something else now?");
                    InternalCalls.EntityActivate("PP3", "Dialogue");
                    InternalCalls.EntityActivate("PP4", "Dialogue");
                    InternalCalls.UpdateText("PP3", "Dialogue", "Do what...");
                    InternalCalls.UpdateText("PP4", "Dialogue", "Where am I...");
                }

                if ((InternalCalls.ButtonReleased("G6", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G6", "Dialogue");
                    InternalCalls.EntityActivate("G7", "Dialogue");
                    InternalCalls.UpdateText("G7", "Dialogue", "Ain't it pretty? Have you seen one before? Do you know what it's called?");
                    InternalCalls.EntityActivate("PP5", "Dialogue");
                    InternalCalls.EntityActivate("PP6", "Dialogue");
                    InternalCalls.UpdateText("PP5", "Dialogue", "Yes...");
                    InternalCalls.UpdateText("PP6", "Dialogue", "No...");
                }

                // second choice from first choice
                if ((InternalCalls.ButtonReleased("PP3", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("PP3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP4", "Dialogue");
                    InternalCalls.EntityActivate("P3", "Dialogue");
                    InternalCalls.UpdateText("P3", "Dialogue", "What am I supposed to do?");
                }

                if ((InternalCalls.ButtonReleased("P3", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("P3", "Dialogue");
                    InternalCalls.EntityDeactivate("G5", "Dialogue");
                    InternalCalls.EntityActivate("G8", "Dialogue");
                    InternalCalls.UpdateText("G8", "Dialogue", "The people said you're a ferryman. Quick, a passenger is waiting! We will meet again...");
                }

                if ((InternalCalls.ButtonReleased("G8", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G8", "Dialogue");
                    InternalCalls.EntityDeactivate("LittleGirlBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                }

                if ((InternalCalls.ButtonReleased("PP4", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("PP3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP4", "Dialogue");
                    InternalCalls.EntityActivate("P4", "Dialogue");
                    InternalCalls.UpdateText("P4", "Dialogue", "I don't even know where I am.");
                }

                if ((InternalCalls.ButtonReleased("P4", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("P4", "Dialogue");
                    InternalCalls.EntityDeactivate("G5", "Dialogue");
                    InternalCalls.EntityActivate("G9", "Dialogue");
                    InternalCalls.UpdateText("G9", "Dialogue", "We're currently at Cordelia! It's said this place holds special memories, so explore around! We will meet again...");
                }

                if ((InternalCalls.ButtonReleased("G9", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G9", "Dialogue");
                    InternalCalls.EntityDeactivate("LittleGirlBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                }

                // second choice from second choice
                if ((InternalCalls.ButtonReleased("PP5", "Dialogue")) == true)
                {

                    InternalCalls.EntityDeactivate("PP5", "Dialogue");
                    InternalCalls.EntityDeactivate("PP6", "Dialogue");
                    InternalCalls.EntityActivate("P5", "Dialogue");
                    InternalCalls.UpdateText("P5", "Dialogue", "Yes, I think.");
                }

                if ((InternalCalls.ButtonReleased("P5", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("P5", "Dialogue");
                    InternalCalls.EntityDeactivate("G7", "Dialogue");
                    InternalCalls.EntityActivate("G10", "Dialogue");
                    InternalCalls.UpdateText("G10", "Dialogue", "So you remember the sea conches! Don't forget them now! We will meet again...");
                }

                if ((InternalCalls.ButtonReleased("G10", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G10", "Dialogue");
                    InternalCalls.EntityDeactivate("LittleGirlBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                }

                if ((InternalCalls.ButtonReleased("PP6", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("PP5", "Dialogue");
                    InternalCalls.EntityDeactivate("PP6", "Dialogue");
                    InternalCalls.EntityActivate("P6", "Dialogue");
                    InternalCalls.UpdateText("P6", "Dialogue", "No, I haven't.");
                }

                if ((InternalCalls.ButtonReleased("P6", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("P6", "Dialogue");
                    InternalCalls.EntityDeactivate("G7", "Dialogue");
                    InternalCalls.EntityActivate("G11", "Dialogue");
                    InternalCalls.UpdateText("G11", "Dialogue", "These are called sea conches, and are known to store important memories of the past. We will meet again...");
                }

                if ((InternalCalls.ButtonReleased("G11", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G11", "Dialogue");
                    InternalCalls.EntityDeactivate("LittleGirlBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                }
            }
            #endregion

            #region Passenger 1 Delivered
            /*
            if (InternalCalls.EntitiesCollided("PassengerBox", "PassengerDeliver", "Level1")) {

            }
            */
            #endregion

            #region Memory Fragment UI
            if ((InternalCalls.ButtonReleased("memoryfragment", "Dialogue")) == true) {
                if (InternalCalls.EntityIsActive("memoryfragmentscreen", "Dialogue") == false) {
                    InternalCalls.EntityActivate("memoryfragmentscreen", "Dialogue");
                }
                else {
                    InternalCalls.EntityDeactivate("memoryfragmentscreen", "Dialogue");
                }
            }
            #endregion
        }

        public void LockPosition(float x, float y)
        {
            InternalCalls.SetPosX("Boat", "Level1", x);
            InternalCalls.SetPosY("Boat", "Level1", y);
        }

        public void DisableUI()
        {
            InternalCalls.EntityDeactivate("hpbar", "Dialogue");
            InternalCalls.EntityDeactivate("memoryfragment", "Dialogue");
            InternalCalls.EntityDeactivate("memoryfragmentscreen", "Dialogue");
        }

        public void EnableUI()
        {
            InternalCalls.EntityActivate("hpbar", "Dialogue");
            InternalCalls.EntityActivate("memoryfragment", "Dialogue");
        }

        public void Exit()
        {
            Console.WriteLine("Exiting...");
        }

        public void ClickCheck()
        {
            if (InternalCalls.CheckKeyRelease(349)) { clickcount++; } //left click
        }

        public void CameraZoomIn()
        {
            InternalCalls.SetCurrentCameraScaleX(700);
        }

        public void CameraZoomOut()
        {
            InternalCalls.SetCurrentCameraScaleX(1600);
        }
    }
}
