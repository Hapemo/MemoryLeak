﻿using System;
using System.Runtime.CompilerServices;

namespace BonVoyage
{
    public class TestMonoScript
    {
        private bool starttalking;

        public void Init()
        {
            starttalking = false;
            InternalCalls.LoadDialogs("Dialogue LittleGirl 0");
            CameraZoomIn();
        }

        public void Update()
        {
            #region Intro Dialogue
            if (InternalCalls.EntitiesCollided("Boat", "IntroBox", "Level1")) {
                LockPosition(160, 120);

                if (!starttalking && InternalCalls.EntityIsActive("IntroBox", "Level1")) {
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
                    InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Talk to the little girl"); // hint
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

                if (!starttalking && InternalCalls.EntityIsActive("LittleGirlBox", "Level1"))
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
                        && InternalCalls.EntityIsActive("G11", "Dialogue") == false)
                    {
                        InternalCalls.EntityActivate("G1", "Dialogue");
                        InternalCalls.UpdateText("G1", "Dialogue", "At last we meet again!");
                        TextAlign("G1", "Dialogue");
                    }
                    CameraZoomIn();
                    starttalking = true;
                }

                if ((InternalCalls.ButtonReleased("G1", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G1", "Dialogue");
                    InternalCalls.EntityActivate("G2", "Dialogue");
                    InternalCalls.UpdateText("G2", "Dialogue", "I've been waiting for you!");
                    TextAlign("G2", "Dialogue");
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
                    TextAlign("G3", "Dialogue");
                }

                //first choice start
                if ((InternalCalls.ButtonReleased("PP1", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP1", "Dialogue");
                    InternalCalls.EntityDeactivate("PP2", "Dialogue");
                    InternalCalls.EntityActivate("G4", "Dialogue");
                    InternalCalls.UpdateText("G4", "Dialogue", "Let's play a game where you hold your hands out and I'll give you something!");
                    TextAlign("G4", "Dialogue");
                }

                if ((InternalCalls.ButtonReleased("PP2", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP1", "Dialogue");
                    InternalCalls.EntityDeactivate("PP2", "Dialogue");
                    InternalCalls.EntityActivate("G6", "Dialogue");
                    InternalCalls.UpdateText("G6", "Dialogue", "We have plenty of time to reminsce! There's something I want to show you!");
                    TextAlign("G6", "Dialogue");
                }
                //first choice end

                if ((InternalCalls.ButtonReleased("G4", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G4", "Dialogue");
                    InternalCalls.EntityActivate("G5", "Dialogue");
                    InternalCalls.UpdateText("G5", "Dialogue", "Well, let's play together now! Or are you supposed to be doing something else now?");
                    InternalCalls.EntityActivate("PP3", "Dialogue");
                    InternalCalls.EntityActivate("PP4", "Dialogue");
                    InternalCalls.UpdateText("PP3", "Dialogue", "Do what...");
                    InternalCalls.UpdateText("PP4", "Dialogue", "Where am I...");
                    TextAlign("G5", "Dialogue");
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
                    TextAlign("G7", "Dialogue");
                }

                // second choice from first choice
                if ((InternalCalls.ButtonReleased("PP3", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("PP3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP4", "Dialogue");
                    InternalCalls.EntityDeactivate("G5", "Dialogue");
                    InternalCalls.EntityActivate("G8", "Dialogue");
                    InternalCalls.UpdateText("G8", "Dialogue", "The people said you're a ferryman. Quick, a passenger is waiting! We will meet again...");
                    InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find a passenger"); // hint
                    TextAlign("G8", "Dialogue");
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
                    InternalCalls.EntityDeactivate("G5", "Dialogue");
                    InternalCalls.EntityActivate("G9", "Dialogue");
                    InternalCalls.UpdateText("G9", "Dialogue", "We're currently at Cordelia! It's said this place holds special memories, so explore around! We will meet again...");
                    InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find a passenger"); // hint
                    TextAlign("G9", "Dialogue");
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
                    InternalCalls.EntityDeactivate("G7", "Dialogue");
                    InternalCalls.EntityActivate("G10", "Dialogue");
                    InternalCalls.UpdateText("G10", "Dialogue", "So you remember the sea conches! Don't forget them now! We will meet again...");
                    InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find a passenger"); // hint
                    TextAlign("G10", "Dialogue");
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
                    InternalCalls.EntityDeactivate("G7", "Dialogue");
                    InternalCalls.EntityActivate("G11", "Dialogue");
                    InternalCalls.UpdateText("G11", "Dialogue", "These are called sea conches, and are known to store important memories of the past. We will meet again...");
                    InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find a passenger"); // hint
                    TextAlign("G11", "Dialogue");
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

            #region Passenger 1 Dialogue (currently using Little Girl dialogue lines)
            if (InternalCalls.EntitiesCollided("Boat", "PassengerBox", "Level1"))
            {
                LockPosition(-1240, 670);

                if (!starttalking && InternalCalls.EntityIsActive("PassengerBox", "Level1"))
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
                        && InternalCalls.EntityIsActive("G11", "Dialogue") == false)
                    {
                        InternalCalls.EntityActivate("G1", "Dialogue");
                        InternalCalls.UpdateText("G1", "Dialogue", "At last we meet again!");
                        TextAlign("G1", "Dialogue");
                    }
                    CameraZoomIn();
                    starttalking = true;
                }

                if ((InternalCalls.ButtonReleased("G1", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G1", "Dialogue");
                    InternalCalls.EntityActivate("G2", "Dialogue");
                    InternalCalls.UpdateText("G2", "Dialogue", "I've been waiting for you!");
                    TextAlign("G2", "Dialogue");
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
                    TextAlign("G3", "Dialogue");
                }

                //first choice start
                if ((InternalCalls.ButtonReleased("PP1", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP1", "Dialogue");
                    InternalCalls.EntityDeactivate("PP2", "Dialogue");
                    InternalCalls.EntityActivate("G4", "Dialogue");
                    InternalCalls.UpdateText("G4", "Dialogue", "Let's play a game where you hold your hands out and I'll give you something!");
                    TextAlign("G4", "Dialogue");
                }

                if ((InternalCalls.ButtonReleased("PP2", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP1", "Dialogue");
                    InternalCalls.EntityDeactivate("PP2", "Dialogue");
                    InternalCalls.EntityActivate("G6", "Dialogue");
                    InternalCalls.UpdateText("G6", "Dialogue", "We have plenty of time to reminsce! There's something I want to show you!");
                    TextAlign("G6", "Dialogue");
                }
                //first choice end

                if ((InternalCalls.ButtonReleased("G4", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G4", "Dialogue");
                    InternalCalls.EntityActivate("G5", "Dialogue");
                    InternalCalls.UpdateText("G5", "Dialogue", "Well, let's play together now! Or are you supposed to be doing something else now?");
                    InternalCalls.EntityActivate("PP3", "Dialogue");
                    InternalCalls.EntityActivate("PP4", "Dialogue");
                    InternalCalls.UpdateText("PP3", "Dialogue", "Do what...");
                    InternalCalls.UpdateText("PP4", "Dialogue", "Where am I...");
                    TextAlign("G5", "Dialogue");
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
                    TextAlign("G7", "Dialogue");
                }

                // second choice from first choice
                if ((InternalCalls.ButtonReleased("PP3", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("PP3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP4", "Dialogue");
                    InternalCalls.EntityDeactivate("G5", "Dialogue");
                    InternalCalls.EntityActivate("G8", "Dialogue");
                    InternalCalls.UpdateText("G8", "Dialogue", "The people said you're a ferryman. Quick, a passenger is waiting! We will meet again...");
                    InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find delivery point"); // hint
                    TextAlign("G8", "Dialogue");
                }

                if ((InternalCalls.ButtonReleased("G8", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G8", "Dialogue");
                    InternalCalls.EntityDeactivate("PassengerBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                    SetPosition("Passenger_1", "Level1", -1240, 670);
                }

                if ((InternalCalls.ButtonReleased("PP4", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("PP3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP4", "Dialogue");
                    InternalCalls.EntityDeactivate("G5", "Dialogue");
                    InternalCalls.EntityActivate("G9", "Dialogue");
                    InternalCalls.UpdateText("G9", "Dialogue", "We're currently at Cordelia! It's said this place holds special memories, so explore around! We will meet again...");
                    InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find delivery point"); // hint
                    TextAlign("G9", "Dialogue");
                }

                if ((InternalCalls.ButtonReleased("G9", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G9", "Dialogue");
                    InternalCalls.EntityDeactivate("PassengerBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                    SetPosition("Passenger_1", "Level1", -1240, 670);
                }

                // second choice from second choice
                if ((InternalCalls.ButtonReleased("PP5", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("PP5", "Dialogue");
                    InternalCalls.EntityDeactivate("PP6", "Dialogue");
                    InternalCalls.EntityDeactivate("G7", "Dialogue");
                    InternalCalls.EntityActivate("G10", "Dialogue");
                    InternalCalls.UpdateText("G10", "Dialogue", "So you remember the sea conches! Don't forget them now! We will meet again...");
                    InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find delivery point"); // hint
                    TextAlign("G10", "Dialogue");
                }

                if ((InternalCalls.ButtonReleased("G10", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G10", "Dialogue");
                    InternalCalls.EntityDeactivate("PassengerBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                    SetPosition("Passenger_1", "Level1", -1240, 670);
                }

                if ((InternalCalls.ButtonReleased("PP6", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("PP5", "Dialogue");
                    InternalCalls.EntityDeactivate("PP6", "Dialogue");
                    InternalCalls.EntityDeactivate("G7", "Dialogue");
                    InternalCalls.EntityActivate("G11", "Dialogue");
                    InternalCalls.UpdateText("G11", "Dialogue", "These are called sea conches, and are known to store important memories of the past. We will meet again...");
                    InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find delivery point"); // hint
                    TextAlign("G11", "Dialogue");
                }

                if ((InternalCalls.ButtonReleased("G11", "Dialogue")) == true)
                {
                    InternalCalls.EntityDeactivate("G11", "Dialogue");
                    InternalCalls.EntityDeactivate("PassengerBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                    SetPosition("Passenger_1", "Level1", -1240, 670);
                }
            }
            #endregion

            #region Passenger 1 Delivered
            /*
            if (InternalCalls.EntitiesCollided("PassengerBox", "PassengerDeliver", "Level1"))
            {

            }
            */
            #endregion

            #region Memory Fragment UI
            if ((InternalCalls.ButtonReleased("memoryfragment", "Dialogue")) == true)
            {
                if (InternalCalls.EntityIsActive("memoryfragmentscreen", "Dialogue") == false)
                {
                    InternalCalls.EntityActivate("memoryfragmentscreen", "Dialogue");
                }
                else
                {
                    InternalCalls.EntityDeactivate("memoryfragmentscreen", "Dialogue");
                }
            }
            #endregion

            #region Crystalball
            
            if ((InternalCalls.ButtonReleased("cyclemap", "Dialogue")) == true)
            {
                if (InternalCalls.EntityIsActive("minimap", "Dialogue"))
                {
                    InternalCalls.EntityDeactivate("minimap", "Dialogue");
                    InternalCalls.EntityActivate("enemymap", "Dialogue");

                    if (InternalCalls.EntityIsActive("minimapbig", "Dialogue") || InternalCalls.EntityIsActive("enemymapbig", "Dialogue") || InternalCalls.EntityIsActive("weathermapbig", "Dialogue"))
                    {
                        InternalCalls.EntityActivate("enemymapbig", "Dialogue");
                        InternalCalls.EntityDeactivate("minimapbig", "Dialogue");
                        InternalCalls.EntityDeactivate("weathermapbig", "Dialogue");
                    }
                }

                else if (InternalCalls.EntityIsActive("enemymap", "Dialogue"))
                {
                    InternalCalls.EntityDeactivate("enemymap", "Dialogue");
                    InternalCalls.EntityActivate("weathermap", "Dialogue");

                    if (InternalCalls.EntityIsActive("minimapbig", "Dialogue") || InternalCalls.EntityIsActive("enemymapbig", "Dialogue") || InternalCalls.EntityIsActive("weathermapbig", "Dialogue"))
                    {
                        InternalCalls.EntityDeactivate("enemymapbig", "Dialogue");
                        InternalCalls.EntityDeactivate("minimapbig", "Dialogue");
                        InternalCalls.EntityActivate("weathermapbig", "Dialogue");
                    }
                }

                else if (InternalCalls.EntityIsActive("weathermap", "Dialogue"))
                {
                    InternalCalls.EntityDeactivate("weathermap", "Dialogue");
                    InternalCalls.EntityActivate("minimap", "Dialogue");

                    if (InternalCalls.EntityIsActive("minimapbig", "Dialogue") || InternalCalls.EntityIsActive("enemymapbig", "Dialogue") || InternalCalls.EntityIsActive("weathermapbig", "Dialogue"))
                    {
                        InternalCalls.EntityDeactivate("enemymapbig", "Dialogue");
                        InternalCalls.EntityActivate("minimapbig", "Dialogue");
                        InternalCalls.EntityDeactivate("weathermapbig", "Dialogue");
                    }
                }
            }
            #endregion

            #region Big Maps
            if ((InternalCalls.ButtonReleased("minimap", "Dialogue")) == true)
            {
                if (InternalCalls.EntityIsActive("minimapbig", "Dialogue") == false)
                {
                    InternalCalls.EntityActivate("minimapbig", "Dialogue");
                }
                else
                {
                    InternalCalls.EntityDeactivate("minimapbig", "Dialogue");
                }
            }

            if ((InternalCalls.ButtonReleased("enemymap", "Dialogue")) == true)
            {
                if (InternalCalls.EntityIsActive("enemymapbig", "Dialogue") == false)
                {
                    InternalCalls.EntityActivate("enemymapbig", "Dialogue");
                }
                else
                {
                    InternalCalls.EntityDeactivate("enemymapbig", "Dialogue");
                }
            }

            if ((InternalCalls.ButtonReleased("weathermap", "Dialogue")) == true)
            {
                if (InternalCalls.EntityIsActive("weathermapbig", "Dialogue") == false)
                {
                    InternalCalls.EntityActivate("weathermapbig", "Dialogue");
                }
                else
                {
                    InternalCalls.EntityDeactivate("weathermapbig", "Dialogue");
                }
            }
            #endregion
        }

        #region UI, Camera, Text Align Functions
        public void DisableUI()
        {
            InternalCalls.EntityDeactivate("hpbar", "Dialogue");
            InternalCalls.EntityDeactivate("memoryfragment", "Dialogue");
            InternalCalls.EntityDeactivate("memoryfragmentscreen", "Dialogue");

            InternalCalls.EntityDeactivate("cyclemap", "Dialogue");

            InternalCalls.EntityDeactivate("minimap", "Dialogue");
            InternalCalls.EntityDeactivate("enemymap", "Dialogue");
            InternalCalls.EntityDeactivate("weathermap", "Dialogue");

            InternalCalls.EntityDeactivate("minimapbig", "Dialogue");
            InternalCalls.EntityDeactivate("enemymapbig", "Dialogue");
            InternalCalls.EntityDeactivate("weathermapbig", "Dialogue");

            InternalCalls.EntityDeactivate("weathertext", "Dialogue");
            InternalCalls.EntityDeactivate("objectivetext", "Dialogue");
        }

        public void EnableUI()
        {
            InternalCalls.EntityActivate("hpbar", "Dialogue");
            InternalCalls.EntityActivate("memoryfragment", "Dialogue");

            InternalCalls.EntityActivate("cyclemap", "Dialogue");

            InternalCalls.EntityActivate("minimap", "Dialogue");

            InternalCalls.EntityActivate("weathertext", "Dialogue");
            InternalCalls.EntityActivate("objectivetext", "Dialogue");
        }

        public void CameraZoomIn()
        {
            InternalCalls.SetCurrentCameraScaleX(700);
        }

        public void CameraZoomOut()
        {
            InternalCalls.SetCurrentCameraScaleX(1600);
        }

        public void TextAlign(string entityname, string scenename)
        {
            if (InternalCalls.GetLineCount(entityname, scenename) == 1)
            {
                InternalCalls.SetScaleX(entityname, scenename, 740);
                InternalCalls.SetScaleY(entityname, scenename, 100);

                InternalCalls.SetPosX(entityname, scenename, -387);
                InternalCalls.SetPosY(entityname, scenename, 200);

                InternalCalls.SetTextOffset(entityname, scenename, -340, -15);
            }
            if (InternalCalls.GetLineCount(entityname, scenename) == 2) 
            {
                InternalCalls.SetScaleX(entityname, scenename, 740);
                InternalCalls.SetScaleY(entityname, scenename, 135);

                InternalCalls.SetPosX(entityname, scenename, -387);
                InternalCalls.SetPosY(entityname, scenename, 180);

                InternalCalls.SetTextOffset(entityname, scenename, -340, 7);
            }
            if (InternalCalls.GetLineCount(entityname, scenename) == 3)
            {
                InternalCalls.SetScaleX(entityname, scenename, 740);
                InternalCalls.SetScaleY(entityname, scenename, 215);

                InternalCalls.SetPosX(entityname, scenename, -387);
                InternalCalls.SetPosY(entityname, scenename, 133);

                InternalCalls.SetTextOffset(entityname, scenename, -340, 25);
            }
            if (InternalCalls.GetLineCount(entityname, scenename) == 4)
            {
                InternalCalls.SetScaleX(entityname, scenename, 740);
                InternalCalls.SetScaleY(entityname, scenename, 229);

                InternalCalls.SetPosX(entityname, scenename, -387);
                InternalCalls.SetPosY(entityname, scenename, 133);

                InternalCalls.SetTextOffset(entityname, scenename, -340, 50);
            }
            if (InternalCalls.GetLineCount(entityname, scenename) == 5)
            {
                InternalCalls.SetScaleX(entityname, scenename, 740);
                InternalCalls.SetScaleY(entityname, scenename, 277);

                InternalCalls.SetPosX(entityname, scenename, -387);
                InternalCalls.SetPosY(entityname, scenename, 108);

                InternalCalls.SetTextOffset(entityname, scenename, -340, 75);
            }
        }
        #endregion

        public void LockPosition(float x, float y)
        {
            InternalCalls.SetPosX("Boat", "Level1", x);
            InternalCalls.SetPosY("Boat", "Level1", y);
        }

        public void SetPosition(string entityname, string scenename, float x, float y)
        {
            InternalCalls.SetPosX(entityname, scenename, x);
            InternalCalls.SetPosY(entityname, scenename, y);
        }
    }
}
