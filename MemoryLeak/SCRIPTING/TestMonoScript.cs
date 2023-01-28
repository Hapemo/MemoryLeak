﻿using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class TestMonoScript
    {
        private bool starttalking = false;
        private float maxX, maxY, minX, minY, halfX, halfY;
        private float HitInterval = 0;
        private float HitCounter = 0;
        private int HitTaken = 0;
        private float HealInterval = 0;
        private float HealCounter = 0;
        private int OctopusAttacked = 0;
        private float PlayerSpeed = 500f;

        private const int MaxHealth = 12;
        private const float Epsilon = 1.192092896e-07F;
        private const double Pi = 3.141592653589793238f;

        /* Some of these flags are here to optimise the code. Because checking this bool value is faster than button check function calls */
        private bool choiceFlag = false;      // This flag is true during choice selection dialogs
        private bool playerTalking = false;   // This flag is true when player is talking, aka P1 active
        public void Init() {
            //InternalCalls.LoadDialogs("Dialogue LittleGirl 0");
            CameraZoomIn();
            halfX = InternalCalls.GetPosX("Water", "Level1");
            halfY = InternalCalls.GetPosY("Water", "Level1");
            maxX = (InternalCalls.GetScaleX("Water", "Level1") / 2) + halfX - InternalCalls.GetScaleX("Enemy", "Level1");
            maxY = (InternalCalls.GetScaleY("Water", "Level1") / 2) + halfY - InternalCalls.GetScaleY("Enemy", "Level1");
            minX = halfX - (InternalCalls.GetScaleX("Water", "Level1") / 2) + InternalCalls.GetScaleX("Enemy", "Level1");
            minY = halfY - (InternalCalls.GetScaleY("Water", "Level1") / 2) + InternalCalls.GetScaleY("Enemy", "Level1");
        }

        public void Update() {
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
            if (InternalCalls.EntitiesCollided("Boat", "LittleGirlBox", "Level1")) {
                LockPosition(-295, -85);

                // I'll be using G1, P1, PP1 and PP2 for the refactored code

                if (!starttalking && InternalCalls.EntityIsActive("LittleGirlBox", "Level1")) {
                    DisableUI();
                    Console.WriteLine("Start talking\n");
                    // Load Little Girl Talking
                    InternalCalls.LoadDialogs("Dialogue LittleGirl 0");
                    InternalCalls.SetCurrentDialogueID(1);

                    // Activate little girl dialogue
                    InternalCalls.EntityActivate("G1", "Dialogue");
                    InternalCalls.UpdateText("G1", "Dialogue", InternalCalls.GetDialogue(InternalCalls.GetCurrentDialogueID()));
                    TextAlign("G1", "Dialogue");

                    // Setting default P1, PP1, PP2 positions
                    InternalCalls.SetPosX("PP1", "Dialogue", 500);
                    InternalCalls.SetPosY("PP1", "Dialogue", 46);
                    InternalCalls.SetPosX("PP2", "Dialogue", 500);
                    InternalCalls.SetPosY("PP2", "Dialogue", -90);
                    InternalCalls.SetPosX("P1", "Dialogue", 450);
                    InternalCalls.SetPosY("P1", "Dialogue", 5);

                    starttalking = true;

                    CameraZoomIn();
                    starttalking = true;
                }

                // If button clicked, load next dialogue
                if (!choiceFlag) {
                    //Console.WriteLine("Choice Flag: " + choiceFlag + "\n");
                    if (playerTalking) {
                        if (InternalCalls.ButtonReleased("P1", "Dialogue")) {           // If click on player talking
                            Console.WriteLine("Player talking clicked\n");
                            InternalCalls.EntityDeactivate("P1", "Dialogue");
                            InternalCalls.EntityActivate("G1", "Dialogue");

                            MoveToNextDialog();
                            InternalCalls.UpdateText("G1", "Dialogue", InternalCalls.GetDialogue(InternalCalls.GetCurrentDialogueID()));
                            TextAlign("G1", "Dialogue");
                            playerTalking = false;
                        }
                    } else {
                        if (InternalCalls.ButtonReleased("G1", "Dialogue")) {           // If click on non-player talking
                            Console.WriteLine("Non-Player talking clicked\n");
                            MoveToNextDialog();
                            InternalCalls.UpdateText("G1", "Dialogue", InternalCalls.GetDialogue(InternalCalls.GetCurrentDialogueID()));

                            // If next dialog has second choice, load them
                            if (InternalCalls.GetChoice2(InternalCalls.GetCurrentDialogueID()) != 0) {
                                Console.WriteLine("Duo choices activated\n");
                                InternalCalls.EntityActivate("PP1", "Dialogue");
                                InternalCalls.EntityActivate("PP2", "Dialogue");

                                InternalCalls.UpdateText("PP1", "Dialogue", GetNextDialog(1));
                                InternalCalls.UpdateText("PP2", "Dialogue", GetNextDialog(2));

                                Console.WriteLine("PP1: " + InternalCalls.GetPosX("PP1", "Dialogue") + " | " + InternalCalls.GetPosY("PP1", "Dialogue"));
                                Console.WriteLine("PP2: " + InternalCalls.GetPosX("PP2", "Dialogue") + " | " + InternalCalls.GetPosY("PP2", "Dialogue"));

                                choiceFlag = true;
                            }
                        }
                    }
                }

                if (choiceFlag) {
                    if (InternalCalls.ButtonReleased("PP1", "Dialogue")) {          // Choice 1 selected
                        Console.WriteLine("Choice 1 clicked\n");
                        InternalCalls.EntityDeactivate("G1", "Dialogue");
                        InternalCalls.EntityDeactivate("PP1", "Dialogue");
                        InternalCalls.EntityDeactivate("PP2", "Dialogue");

                        MoveToNextDialog();
                        MoveToNextDialog();

                        InternalCalls.EntityActivate("P1", "Dialogue");
                        InternalCalls.UpdateText("P1", "Dialogue", InternalCalls.GetDialogue(InternalCalls.GetCurrentDialogueID()));
                        //TextAlign("P1", "Dialogue");

                        choiceFlag = false;
                        playerTalking = true;
                    } else if (InternalCalls.ButtonReleased("PP2", "Dialogue")) {   // Choice 2 selected
                        Console.WriteLine("Choice 2 clicked\n");
                        InternalCalls.EntityDeactivate("G1", "Dialogue");
                        InternalCalls.EntityDeactivate("PP1", "Dialogue");
                        InternalCalls.EntityDeactivate("PP2", "Dialogue");

                        MoveToNextDialog();
                        MoveToNextDialog(2); // This is the only difference with the code above

                        InternalCalls.EntityActivate("P1", "Dialogue");
                        InternalCalls.UpdateText("P1", "Dialogue", InternalCalls.GetDialogue(InternalCalls.GetCurrentDialogueID()));
                        //TextAlign("P1", "Dialogue");

                        choiceFlag = false;
                        playerTalking = true;
                    }
                }

                //if ((InternalCalls.ButtonReleased("G1", "Dialogue")) == true) {
                //  InternalCalls.EntityDeactivate("G1", "Dialogue");
                //  InternalCalls.EntityActivate("G2", "Dialogue");
                //  InternalCalls.UpdateText("G2", "Dialogue", "I've been waiting for you!");
                //  TextAlign("G2", "Dialogue");
                //  InternalCalls.LoadDialogs("Dialogue LittleGirl 0");
                //  InternalCalls.SetCurrentDialogueID(1);
                //  Console.WriteLine("Current dialogue ID: " + InternalCalls.GetCurrentDialogueID());
                //  Console.WriteLine("Current dialogue string: " + InternalCalls.GetDialogue(InternalCalls.GetCurrentDialogueID()) + "\n");
                //}

                //if ((InternalCalls.ButtonReleased("G2", "Dialogue")) == true) {
                //  InternalCalls.EntityDeactivate("G2", "Dialogue");
                //  InternalCalls.EntityActivate("G3", "Dialogue");
                //  InternalCalls.UpdateText("G3", "Dialogue", "What would you like to do? Maybe play or remininsce?");
                //  InternalCalls.EntityActivate("PP1", "Dialogue");
                //  InternalCalls.EntityActivate("PP2", "Dialogue");
                //  InternalCalls.UpdateText("PP1", "Dialogue", "Play...");
                //  InternalCalls.UpdateText("PP2", "Dialogue", "Reminisce...");
                //  TextAlign("G3", "Dialogue");
                //}

                ////first choice start
                //if ((InternalCalls.ButtonReleased("PP1", "Dialogue")) == true) {
                //  InternalCalls.EntityDeactivate("G3", "Dialogue");
                //  InternalCalls.EntityDeactivate("PP1", "Dialogue");
                //  InternalCalls.EntityDeactivate("PP2", "Dialogue");
                //  InternalCalls.EntityActivate("G4", "Dialogue");
                //  InternalCalls.UpdateText("G4", "Dialogue", "Let's play a game where you hold your hands out and I'll give you something!");
                //  TextAlign("G4", "Dialogue");
                //}

                //if ((InternalCalls.ButtonReleased("PP2", "Dialogue")) == true) {
                //  InternalCalls.EntityDeactivate("G3", "Dialogue");
                //  InternalCalls.EntityDeactivate("PP1", "Dialogue");
                //  InternalCalls.EntityDeactivate("PP2", "Dialogue");
                //  InternalCalls.EntityActivate("G6", "Dialogue");
                //  InternalCalls.UpdateText("G6", "Dialogue", "We have plenty of time to reminsce! There's something I want to show you!");
                //  TextAlign("G6", "Dialogue");
                //}
                ////first choice end

                //if ((InternalCalls.ButtonReleased("G4", "Dialogue")) == true) {
                //  InternalCalls.EntityDeactivate("G4", "Dialogue");
                //  InternalCalls.EntityActivate("G5", "Dialogue");
                //  InternalCalls.UpdateText("G5", "Dialogue", "Well, let's play together now! Or are you supposed to be doing something else now?");
                //  InternalCalls.EntityActivate("PP3", "Dialogue");
                //  InternalCalls.EntityActivate("PP4", "Dialogue");
                //  InternalCalls.UpdateText("PP3", "Dialogue", "Do what...");
                //  InternalCalls.UpdateText("PP4", "Dialogue", "Where am I...");
                //  TextAlign("G5", "Dialogue");
                //}

                //if ((InternalCalls.ButtonReleased("G6", "Dialogue")) == true) {
                //  InternalCalls.EntityDeactivate("G6", "Dialogue");
                //  InternalCalls.EntityActivate("G7", "Dialogue");
                //  InternalCalls.UpdateText("G7", "Dialogue", "Ain't it pretty? Have you seen one before? Do you know what it's called?");
                //  InternalCalls.EntityActivate("PP5", "Dialogue");
                //  InternalCalls.EntityActivate("PP6", "Dialogue");
                //  InternalCalls.UpdateText("PP5", "Dialogue", "Yes...");
                //  InternalCalls.UpdateText("PP6", "Dialogue", "No...");
                //  TextAlign("G7", "Dialogue");
                //}

                //// second choice from first choice
                //if ((InternalCalls.ButtonReleased("PP3", "Dialogue")) == true) {
                //  InternalCalls.EntityDeactivate("PP3", "Dialogue");
                //  InternalCalls.EntityDeactivate("PP4", "Dialogue");
                //  InternalCalls.EntityDeactivate("G5", "Dialogue");
                //  InternalCalls.EntityActivate("G8", "Dialogue");
                //  InternalCalls.UpdateText("G8", "Dialogue", "The people said you're a ferryman. Quick, a passenger is waiting! We will meet again...");
                //  InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find a passenger"); // hint
                //  TextAlign("G8", "Dialogue");
                //}

                //if ((InternalCalls.ButtonReleased("G8", "Dialogue")) == true) {
                //  InternalCalls.EntityDeactivate("G8", "Dialogue");
                //  InternalCalls.EntityDeactivate("LittleGirlBox", "Level1");
                //  CameraZoomOut();
                //  starttalking = false;
                //  EnableUI();
                //}

                //if ((InternalCalls.ButtonReleased("PP4", "Dialogue")) == true) {
                //  InternalCalls.EntityDeactivate("PP3", "Dialogue");
                //  InternalCalls.EntityDeactivate("PP4", "Dialogue");
                //  InternalCalls.EntityDeactivate("G5", "Dialogue");
                //  InternalCalls.EntityActivate("G9", "Dialogue");
                //  InternalCalls.UpdateText("G9", "Dialogue", "We're currently at Cordelia! It's said this place holds special memories, so explore around! We will meet again...");
                //  InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find a passenger"); // hint
                //  TextAlign("G9", "Dialogue");
                //}

                //if ((InternalCalls.ButtonReleased("G9", "Dialogue")) == true) {
                //  InternalCalls.EntityDeactivate("G9", "Dialogue");
                //  InternalCalls.EntityDeactivate("LittleGirlBox", "Level1");
                //  CameraZoomOut();
                //  starttalking = false;
                //  EnableUI();
                //}

                //// second choice from second choice
                //if ((InternalCalls.ButtonReleased("PP5", "Dialogue")) == true) {
                //  InternalCalls.EntityDeactivate("PP5", "Dialogue");
                //  InternalCalls.EntityDeactivate("PP6", "Dialogue");
                //  InternalCalls.EntityDeactivate("G7", "Dialogue");
                //  InternalCalls.EntityActivate("G10", "Dialogue");
                //  InternalCalls.UpdateText("G10", "Dialogue", "So you remember the sea conches! Don't forget them now! We will meet again...");
                //  InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find a passenger"); // hint
                //  TextAlign("G10", "Dialogue");
                //}

                //if ((InternalCalls.ButtonReleased("G10", "Dialogue")) == true) {
                //  InternalCalls.EntityDeactivate("G10", "Dialogue");
                //  InternalCalls.EntityDeactivate("LittleGirlBox", "Level1");
                //  CameraZoomOut();
                //  starttalking = false;
                //  EnableUI();
                //}

                //if ((InternalCalls.ButtonReleased("PP6", "Dialogue")) == true) {
                //  InternalCalls.EntityDeactivate("PP5", "Dialogue");
                //  InternalCalls.EntityDeactivate("PP6", "Dialogue");
                //  InternalCalls.EntityDeactivate("G7", "Dialogue");
                //  InternalCalls.EntityActivate("G11", "Dialogue");
                //  InternalCalls.UpdateText("G11", "Dialogue", "These are called sea conches, and are known to store important memories of the past. We will meet again...");
                //  InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find a passenger"); // hint
                //  TextAlign("G11", "Dialogue");
                //}

                //if ((InternalCalls.ButtonReleased("G11", "Dialogue")) == true) {
                //  InternalCalls.EntityDeactivate("G11", "Dialogue");
                //  InternalCalls.EntityDeactivate("LittleGirlBox", "Level1");
                //  CameraZoomOut();
                //  starttalking = false;
                //  EnableUI();
                //}
            }
            #endregion

            #region Passenger 1 Dialogue (currently using Little Girl dialogue lines)
            if (InternalCalls.EntitiesCollided("Boat", "PassengerBox", "Level1")) {
                LockPosition(-1240, 670);

                if (!starttalking && InternalCalls.EntityIsActive("PassengerBox", "Level1")) {
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
                        && InternalCalls.EntityIsActive("G11", "Dialogue") == false) {
                    InternalCalls.EntityActivate("G1", "Dialogue");
                    InternalCalls.UpdateText("G1", "Dialogue", "At last we meet again!");
                    TextAlign("G1", "Dialogue");
                    }
                    CameraZoomIn();
                    starttalking = true;
                }

                if ((InternalCalls.ButtonReleased("G1", "Dialogue")) == true) {
                    InternalCalls.EntityDeactivate("G1", "Dialogue");
                    InternalCalls.EntityActivate("G2", "Dialogue");
                    InternalCalls.UpdateText("G2", "Dialogue", "I've been waiting for you!");
                    TextAlign("G2", "Dialogue");
                }

                if ((InternalCalls.ButtonReleased("G2", "Dialogue")) == true) {
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
                if ((InternalCalls.ButtonReleased("PP1", "Dialogue")) == true) {
                    InternalCalls.EntityDeactivate("G3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP1", "Dialogue");
                    InternalCalls.EntityDeactivate("PP2", "Dialogue");
                    InternalCalls.EntityActivate("G4", "Dialogue");
                    InternalCalls.UpdateText("G4", "Dialogue", "Let's play a game where you hold your hands out and I'll give you something!");
                    TextAlign("G4", "Dialogue");
                }

                if ((InternalCalls.ButtonReleased("PP2", "Dialogue")) == true) {
                    InternalCalls.EntityDeactivate("G3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP1", "Dialogue");
                    InternalCalls.EntityDeactivate("PP2", "Dialogue");
                    InternalCalls.EntityActivate("G6", "Dialogue");
                    InternalCalls.UpdateText("G6", "Dialogue", "We have plenty of time to reminsce! There's something I want to show you!");
                    TextAlign("G6", "Dialogue");
                }
                //first choice end

                if ((InternalCalls.ButtonReleased("G4", "Dialogue")) == true) {
                    InternalCalls.EntityDeactivate("G4", "Dialogue");
                    InternalCalls.EntityActivate("G5", "Dialogue");
                    InternalCalls.UpdateText("G5", "Dialogue", "Well, let's play together now! Or are you supposed to be doing something else now?");
                    InternalCalls.EntityActivate("PP3", "Dialogue");
                    InternalCalls.EntityActivate("PP4", "Dialogue");
                    InternalCalls.UpdateText("PP3", "Dialogue", "Do what...");
                    InternalCalls.UpdateText("PP4", "Dialogue", "Where am I...");
                    TextAlign("G5", "Dialogue");
                }

                if ((InternalCalls.ButtonReleased("G6", "Dialogue")) == true) {
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
                if ((InternalCalls.ButtonReleased("PP3", "Dialogue")) == true) {
                    InternalCalls.EntityDeactivate("PP3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP4", "Dialogue");
                    InternalCalls.EntityDeactivate("G5", "Dialogue");
                    InternalCalls.EntityActivate("G8", "Dialogue");
                    InternalCalls.UpdateText("G8", "Dialogue", "The people said you're a ferryman. Quick, a passenger is waiting! We will meet again...");
                    InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find delivery point"); // hint
                    TextAlign("G8", "Dialogue");
                }

                if ((InternalCalls.ButtonReleased("G8", "Dialogue")) == true) {
                    InternalCalls.EntityDeactivate("G8", "Dialogue");
                    InternalCalls.EntityDeactivate("PassengerBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                    SetPosition("Passenger_1", "Level1", -1240, 670);
                }

                if ((InternalCalls.ButtonReleased("PP4", "Dialogue")) == true) {
                    InternalCalls.EntityDeactivate("PP3", "Dialogue");
                    InternalCalls.EntityDeactivate("PP4", "Dialogue");
                    InternalCalls.EntityDeactivate("G5", "Dialogue");
                    InternalCalls.EntityActivate("G9", "Dialogue");
                    InternalCalls.UpdateText("G9", "Dialogue", "We're currently at Cordelia! It's said this place holds special memories, so explore around! We will meet again...");
                    InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find delivery point"); // hint
                    TextAlign("G9", "Dialogue");
                }

                if ((InternalCalls.ButtonReleased("G9", "Dialogue")) == true) {
                    InternalCalls.EntityDeactivate("G9", "Dialogue");
                    InternalCalls.EntityDeactivate("PassengerBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                    SetPosition("Passenger_1", "Level1", -1240, 670);
                }

                // second choice from second choice
                if ((InternalCalls.ButtonReleased("PP5", "Dialogue")) == true) {
                    InternalCalls.EntityDeactivate("PP5", "Dialogue");
                    InternalCalls.EntityDeactivate("PP6", "Dialogue");
                    InternalCalls.EntityDeactivate("G7", "Dialogue");
                    InternalCalls.EntityActivate("G10", "Dialogue");
                    InternalCalls.UpdateText("G10", "Dialogue", "So you remember the sea conches! Don't forget them now! We will meet again...");
                    InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find delivery point"); // hint
                    TextAlign("G10", "Dialogue");
                }

                if ((InternalCalls.ButtonReleased("G10", "Dialogue")) == true) {
                    InternalCalls.EntityDeactivate("G10", "Dialogue");
                    InternalCalls.EntityDeactivate("PassengerBox", "Level1");
                    CameraZoomOut();
                    starttalking = false;
                    EnableUI();
                    SetPosition("Passenger_1", "Level1", -1240, 670);
                }

                if ((InternalCalls.ButtonReleased("PP6", "Dialogue")) == true) {
                    InternalCalls.EntityDeactivate("PP5", "Dialogue");
                    InternalCalls.EntityDeactivate("PP6", "Dialogue");
                    InternalCalls.EntityDeactivate("G7", "Dialogue");
                    InternalCalls.EntityActivate("G11", "Dialogue");
                    InternalCalls.UpdateText("G11", "Dialogue", "These are called sea conches, and are known to store important memories of the past. We will meet again...");
                    InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find delivery point"); // hint
                    TextAlign("G11", "Dialogue");
                }

                if ((InternalCalls.ButtonReleased("G11", "Dialogue")) == true) {
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
            if ((InternalCalls.ButtonReleased("memoryfragment", "Dialogue")) == true) {
                if (InternalCalls.EntityIsActive("memoryfragmentscreen", "Dialogue") == false) {
                    InternalCalls.EntityActivate("memoryfragmentscreen", "Dialogue");
                } else {
                    InternalCalls.EntityDeactivate("memoryfragmentscreen", "Dialogue");
                }
            }
            #endregion

            #region Crystalball

            if ((InternalCalls.ButtonReleased("cyclemap", "Dialogue")) == true) {
                if (InternalCalls.EntityIsActive("minimap", "Dialogue")) {
                    InternalCalls.EntityDeactivate("minimap", "Dialogue");
                    InternalCalls.EntityActivate("enemymap", "Dialogue");

                    if (InternalCalls.EntityIsActive("minimapbig", "Dialogue") || InternalCalls.EntityIsActive("enemymapbig", "Dialogue") || InternalCalls.EntityIsActive("weathermapbig", "Dialogue")) {
                    InternalCalls.EntityActivate("enemymapbig", "Dialogue");
                    InternalCalls.EntityDeactivate("minimapbig", "Dialogue");
                    InternalCalls.EntityDeactivate("weathermapbig", "Dialogue");
                    }
                } else if (InternalCalls.EntityIsActive("enemymap", "Dialogue")) {
                    InternalCalls.EntityDeactivate("enemymap", "Dialogue");
                    InternalCalls.EntityActivate("weathermap", "Dialogue");

                    if (InternalCalls.EntityIsActive("minimapbig", "Dialogue") || InternalCalls.EntityIsActive("enemymapbig", "Dialogue") || InternalCalls.EntityIsActive("weathermapbig", "Dialogue")) {
                    InternalCalls.EntityDeactivate("enemymapbig", "Dialogue");
                    InternalCalls.EntityDeactivate("minimapbig", "Dialogue");
                    InternalCalls.EntityActivate("weathermapbig", "Dialogue");
                    }
                } else if (InternalCalls.EntityIsActive("weathermap", "Dialogue")) {
                    InternalCalls.EntityDeactivate("weathermap", "Dialogue");
                    InternalCalls.EntityActivate("minimap", "Dialogue");

                    if (InternalCalls.EntityIsActive("minimapbig", "Dialogue") || InternalCalls.EntityIsActive("enemymapbig", "Dialogue") || InternalCalls.EntityIsActive("weathermapbig", "Dialogue")) {
                    InternalCalls.EntityDeactivate("enemymapbig", "Dialogue");
                    InternalCalls.EntityActivate("minimapbig", "Dialogue");
                    InternalCalls.EntityDeactivate("weathermapbig", "Dialogue");
                    }
                }
            }
            #endregion

            #region Big Maps
            if ((InternalCalls.ButtonReleased("minimap", "Dialogue")) == true) {
                if (InternalCalls.EntityIsActive("minimapbig", "Dialogue") == false) {
                    InternalCalls.EntityActivate("minimapbig", "Dialogue");
                } else {
                    InternalCalls.EntityDeactivate("minimapbig", "Dialogue");
                }
            }

            if ((InternalCalls.ButtonReleased("enemymap", "Dialogue")) == true) {
                if (InternalCalls.EntityIsActive("enemymapbig", "Dialogue") == false) {
                    InternalCalls.EntityActivate("enemymapbig", "Dialogue");
                } else {
                    InternalCalls.EntityDeactivate("enemymapbig", "Dialogue");
                }
            }

            if ((InternalCalls.ButtonReleased("weathermap", "Dialogue")) == true) {
                if (InternalCalls.EntityIsActive("weathermapbig", "Dialogue") == false) {
                    InternalCalls.EntityActivate("weathermapbig", "Dialogue");
                } else {
                    InternalCalls.EntityDeactivate("weathermapbig", "Dialogue");
                }
            }
            #endregion

            #region Player
            if (InternalCalls.CheckKeyHold(349)) { // Mouse click
                float DirX = InternalCalls.GetWorldMousePosX() + InternalCalls.GetCurrentCameraPosX() - InternalCalls.GetPosX("Boat", "Level1");
                float DirY = InternalCalls.GetWorldMousePosY() + InternalCalls.GetCurrentCameraPosY() - InternalCalls.GetPosY("Boat", "Level1");
                float NormX = 0f, NormY = 0f;
                if (InternalCalls.SqMagnitude(DirX, DirY) > Epsilon * Epsilon)
                {
                    NormX = InternalCalls.NormalizeX(DirX, DirY);
                    NormY = InternalCalls.NormalizeY(DirX, DirY);
                    InternalCalls.ApplyImpulse("Boat", "Level1",
                        (NormX * PlayerSpeed * (float)InternalCalls.GetDeltaTime()),
                        (NormY * PlayerSpeed * (float)InternalCalls.GetDeltaTime()), 0f, 0f);
                }

                float rotation = 0;
                if (NormY != 0f && NormX >= 0f)
                    rotation = InternalCalls.ArcTangent(NormY, NormX);
                else if (NormY == 0f && NormX > 0f)
                    rotation = (float)Pi / 2;
                else if (NormY != 0f && NormX < 0f)
                {
                    rotation = InternalCalls.ArcTangent(NormY, NormX);
                    rotation += rotation < 0f ? (float)Pi * 2f : 0f;
                }
                else rotation = 3f * (float)Pi / 2f;

                const float miniAngle = (float)Pi / 8;
                float tempRotation = rotation;
                if (tempRotation < 0) tempRotation += 2 * (float)Pi;

                if (tempRotation >= 15f * miniAngle || tempRotation <= miniAngle) InternalCalls.SetSpriteSheetIndex("Boat", "Level1", 6);
                else if (tempRotation <= 3f * miniAngle) InternalCalls.SetSpriteSheetIndex("Boat", "Level1", 5);
                else if (tempRotation <= 5f * miniAngle) InternalCalls.SetSpriteSheetIndex("Boat", "Level1", 4);
                else if (tempRotation <= 7f * miniAngle) InternalCalls.SetSpriteSheetIndex("Boat", "Level1", 3);
                else if (tempRotation <= 9f * miniAngle) InternalCalls.SetSpriteSheetIndex("Boat", "Level1", 2);
                else if (tempRotation <= 11f * miniAngle) InternalCalls.SetSpriteSheetIndex("Boat", "Level1", 1);
                else if (tempRotation <= 13f * miniAngle) InternalCalls.SetSpriteSheetIndex("Boat", "Level1", 0);
                else InternalCalls.SetSpriteSheetIndex("Boat", "Level1", 7);
            }
            #endregion

            #region Enemy
            //InternalCalls.SetCurrentCameraScaleX(5500);
            // Check in screen what region
            float posX = InternalCalls.GetPosX("Enemy", "Level1");
            float posY = InternalCalls.GetPosY("Enemy", "Level1");
            float changeInX = 0;
            float changeInY = 0;
            Random rand = new Random();
            switch (CheckRegion("Enemy", "Level1")) {
                case 1:
                    changeInX = rand.Next(0, 5);
                    changeInY = rand.Next(-4, 1);
                    Console.Write("Region 1!\n");
                    break;
                case 2:
                    changeInX = rand.Next(-4, 1);
                    changeInY = rand.Next(-4, 1);
                    Console.Write("Region 2!\n");
                    break;
                case 3:
                    changeInX = rand.Next(-4, 1);
                    changeInY = rand.Next(0, 5);
                    Console.Write("Region 3!\n");
                    break;
                case 4:
                    changeInX = rand.Next(0, 5);
                    changeInY = rand.Next(0, 5);
                    Console.Write("Region 4!\n");
                    break;
                default:
                    break;
            }
            changeInX = (((posX + changeInX) < maxX) && ((posX + changeInX) > minX)) ? changeInX : 0;
            changeInY = (((posY + changeInY) < maxY) && ((posY + changeInY) > minY)) ? changeInY : 0;
            InternalCalls.SetPosX("EnemyTrigger", "Level1", posX + changeInX);
            InternalCalls.SetPosY("EnemyTrigger", "Level1", posY + changeInY);
            InternalCalls.SetPosX("Enemy", "Level1", posX + changeInX);
            InternalCalls.SetPosY("Enemy", "Level1", posY + changeInY);

            if (InternalCalls.EntitiesCollided("Boat", "EnemyTrigger", "Level1")) {
                switch (OctopusAttacked) {
                    case 0:
                        OctopusAttacked = 1;
                        InternalCalls.PlaySoundOnLoop("EnemyTrigger", "Level1");
                        InternalCalls.SetSpriteSheetIndex("Enemy", "Level1", 1);
                        InternalCalls.SetAnimationCurrentIndex("Enemy", "Level1", 0);
                        HitInterval = 20 * InternalCalls.GetAnimationSpeed("Enemy", "Level1") * InternalCalls.GetAnimationFrameCount("Enemy", "Level1");
                        HealInterval = HitInterval * 4;
                        break;
                    case 1:
                        if (InternalCalls.GetAnimationCurrentIndex("Enemy", "Level1") == InternalCalls.GetAnimationFrameCount("Enemy", "Level1") - 1) {
                            InternalCalls.SetSpriteSheetIndex("Enemy", "Level1", 2);
                            InternalCalls.SetAnimationCurrentIndex("Enemy", "Level1", 0);
                            OctopusAttacked = 2;
                        }
                        break;
                    default:
                        break;
                }
            } else {
                OctopusAttacked = 0;
                InternalCalls.StopSound("EnemyTrigger", "Level1");
                InternalCalls.SetSpriteSheetIndex("Enemy", "Level1", 0);
            }

            if (InternalCalls.EntitiesCollided("Boat", "Enemy", "Level1")) {
                ++HitCounter;
                if (HitCounter >= HitInterval) {
                    Console.Write("Attacking!\n");
                    HitCounter = 0;
                    ++HitTaken;
                    InternalCalls.SetTexture("hpbar", "Dialogue", "Textures\\Icons\\healthbar-" + (HitTaken + 1) + ".png");
                }
            } else {
                ++HealCounter;
                if (HitTaken > 0 && HealCounter >= HealInterval) {
                    Console.Write("Regenerating!\n");
                    HealCounter = 0;
                    --HitTaken;
                    InternalCalls.SetTexture("hpbar", "Dialogue", "Textures\\Icons\\healthbar-" + (HitTaken + 1) + ".png");
                }
            }

            if(HitTaken == MaxHealth) {
                InternalCalls.SetSpriteSheetIndex("Boat", "Level1", 2);
                InternalCalls.SetAnimationCurrentIndex("Boat", "Level1", 0);
                HitTaken = -1;
            }
            if (HitTaken == -1 && InternalCalls.GetAnimationCurrentIndex("Boat", "Level1") == InternalCalls.GetAnimationFrameCount("Boat", "Level1") - 1)
            {
                InternalCalls.PauseScene("Level1");
                InternalCalls.PlayScene("Game Over");
            }
            #endregion
        }

        #region UI, Camera, Text Align Functions
        public void DisableUI() {
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

        public void EnableUI() {
            InternalCalls.EntityActivate("hpbar", "Dialogue");
            InternalCalls.EntityActivate("memoryfragment", "Dialogue");

            InternalCalls.EntityActivate("cyclemap", "Dialogue");

            InternalCalls.EntityActivate("minimap", "Dialogue");

            InternalCalls.EntityActivate("weathertext", "Dialogue");
            InternalCalls.EntityActivate("objectivetext", "Dialogue");
        }

        public void CameraZoomIn() {
            InternalCalls.SetCurrentCameraScaleX(700);
        }

        public void CameraZoomOut() {
            InternalCalls.SetCurrentCameraScaleX(1600);
        }

        public void TextAlign(string entityname, string scenename) {
            int lineCount = InternalCalls.GetLineCount(entityname, scenename);
            switch(lineCount) {
            case 1:
                InternalCalls.SetScaleX(entityname, scenename, 740);
                InternalCalls.SetScaleY(entityname, scenename, 100);

                InternalCalls.SetPosX(entityname, scenename, -387);
                InternalCalls.SetPosY(entityname, scenename, 200);

                InternalCalls.SetTextOffset(entityname, scenename, -340, -15);
            break;
            case 2:
                InternalCalls.SetScaleX(entityname, scenename, 740);
                InternalCalls.SetScaleY(entityname, scenename, 135);

                InternalCalls.SetPosX(entityname, scenename, -387);
                InternalCalls.SetPosY(entityname, scenename, 180);

                InternalCalls.SetTextOffset(entityname, scenename, -340, 7);
            break;
            case 3:
                InternalCalls.SetScaleX(entityname, scenename, 740);
                InternalCalls.SetScaleY(entityname, scenename, 215);

                InternalCalls.SetPosX(entityname, scenename, -387);
                InternalCalls.SetPosY(entityname, scenename, 133);

                InternalCalls.SetTextOffset(entityname, scenename, -340, 25);
            break;
            case 4:
                InternalCalls.SetScaleX(entityname, scenename, 740);
                InternalCalls.SetScaleY(entityname, scenename, 229);

                InternalCalls.SetPosX(entityname, scenename, -387);
                InternalCalls.SetPosY(entityname, scenename, 133);

                InternalCalls.SetTextOffset(entityname, scenename, -340, 50);
            break;
            case 5:
                InternalCalls.SetScaleX(entityname, scenename, 740);
                InternalCalls.SetScaleY(entityname, scenename, 277);

                InternalCalls.SetPosX(entityname, scenename, -387);
                InternalCalls.SetPosY(entityname, scenename, 108);

                InternalCalls.SetTextOffset(entityname, scenename, -340, 75);
            break;
            }
        }
        #endregion

        #region Dialogue helper functions
        // Based on the current dialog ID, move to the next one. Can input choice if there is a choice selection, by default it's 1
        public void MoveToNextDialog(int choice = 1) { 
            if (choice == 1) InternalCalls.SetCurrentDialogueID(InternalCalls.GetNextDialogueID(InternalCalls.GetCurrentDialogueID())); 
            else InternalCalls.SetCurrentDialogueID(InternalCalls.GetChoice2(InternalCalls.GetCurrentDialogueID())); 
        }
    
        // Get the texts of the next dialog, able to input 1 or 2 to get the different choices
        public string GetNextDialog(int choice = 1) {
            if (choice == 1) return InternalCalls.GetDialogue(InternalCalls.GetNextDialogueID(InternalCalls.GetCurrentDialogueID()));
            else return InternalCalls.GetDialogue(InternalCalls.GetChoice2(InternalCalls.GetCurrentDialogueID()));
        }
        #endregion
        public void LockPosition(float x, float y) {
            InternalCalls.SetPosX("Boat", "Level1", x);
            InternalCalls.SetPosY("Boat", "Level1", y);
        }

        public void SetPosition(string entityname, string scenename, float x, float y) {
            InternalCalls.SetPosX(entityname, scenename, x);
            InternalCalls.SetPosY(entityname, scenename, y);
        }

        public int CheckRegion(string _entityName, string _sceneName)
        {
            if (InternalCalls.GetPosX(_entityName, _sceneName) > maxX || InternalCalls.GetPosY(_entityName, _sceneName) > maxY ||
                InternalCalls.GetPosX(_entityName, _sceneName) < minX || InternalCalls.GetPosY(_entityName, _sceneName) < minY) return 0;
            if (InternalCalls.GetPosX(_entityName, _sceneName) > halfX && InternalCalls.GetPosY(_entityName, _sceneName) > halfY) return 1;
            if (InternalCalls.GetPosX(_entityName, _sceneName) > halfX && InternalCalls.GetPosY(_entityName, _sceneName) < halfY) return 2;
            if (InternalCalls.GetPosX(_entityName, _sceneName) < halfX && InternalCalls.GetPosY(_entityName, _sceneName) < halfY) return 3;
            if (InternalCalls.GetPosX(_entityName, _sceneName) < halfX && InternalCalls.GetPosY(_entityName, _sceneName) > halfY) return 4;
            Console.Write("Out of bounds!\n");
            return -1;
        }
    }
}
