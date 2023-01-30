using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
    public class TestMonoScript
    {
        private bool fragment1 = false;
        private bool starttalking = false;
        private float maxX, maxY, minX, minY, halfX, halfY;
        private int HitInterval = 0;
        private int HitCounter = 0;
        private int HitTaken = 0;
        private int HealInterval = 0;
        private int HealCounter = 0;
        private int OctopusAttacked = 0;
        private float PlayerRotation = 0;
        private float PlayerSpeed = 500f;
        private float EnemySpeed = 420f;
        private bool EnemyLoiter = true;

        private const int MaxHealth = 12;
        private const float Epsilon = 1.192092896e-07F;
        private const double Pi = 3.141592653589793238f;
        private const float MiniAngle = (float)Pi / 8;

        /* Some of these flags are here to optimise the code. Because checking this bool value is faster than button check function calls */
        private bool choiceFlag = false;      // This flag is true during choice selection dialogs
        private bool playerTalking = false;   // This flag is true when player is talking, aka P1 active
        private bool updateChat = false;      // This flag is true when dialog changes for anyone
        private bool RunlittleGirlDialog = true;
        private bool RunPassengerDialog = true;
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

        // I'll be using G1, P1, PP1 and PP2 for the refactored code
        if (InternalCalls.EntityIsActive("LittleGirlBox", "Level1") && RunlittleGirlDialog) {
          LockPosition(-295, -85);
          RunlittleGirlDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialogue LittleGirl 0");
        }

      }
      #endregion

            #region Passenger 1 Dialogue
      if (InternalCalls.EntitiesCollided("Boat", "PassengerBox", "Level1")) {

        if (InternalCalls.EntityIsActive("LittleGirlBox", "Level1") && RunPassengerDialog) {
          LockPosition(-1240, 670);
          RunPassengerDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialogue Passenger 1");

                    if (InternalCalls.GetNextDialogueID(InternalCalls.GetCurrentDialogueID()) == 0)
                    {
                        SetPosition("Passenger_1", "Level1", -1240, 670);
                        InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find the destination"); // hint
                    }
        }

      }
            #endregion

            #region Passenger 1 Delivered
            if (InternalCalls.EntitiesCollided("Boat", "destination", "Level1"))
            {
                InternalCalls.PlayScene("cutscene1");
                InternalCalls.EntityDeactivate("destination", "Level1");
            }
            #endregion

            #region Memory Fragment UI

            if (InternalCalls.EntitiesCollided("Boat", "fragment1drop", "Level1"))
            {
                fragment1 = true;
                InternalCalls.UpdateText("memoryfragmentscreen", "Dialogue", "Memory Fragments (1/1)");
                InternalCalls.EntityDeactivate("fragment1drop", "Level1");
            }

            if ((InternalCalls.ButtonReleased("memoryfragment", "Dialogue")) == true) {
                if (InternalCalls.EntityIsActive("memoryfragmentscreen", "Dialogue") == false) {
                    InternalCalls.EntityActivate("memoryfragmentscreen", "Dialogue");
                    if (fragment1 == true) { InternalCalls.EntityActivate("fragment1obj", "Dialogue"); }
                } else {
                    InternalCalls.EntityDeactivate("memoryfragmentscreen", "Dialogue");
                    if (fragment1 == true) { InternalCalls.EntityDeactivate("fragment1obj", "Dialogue"); }
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
            float PlayerPosX = InternalCalls.GetPosX("Boat", "Level1");
            float PlayerPosY = InternalCalls.GetPosY("Boat", "Level1");
            if (InternalCalls.CheckKeyHold(349) && InternalCalls.EntityIsActive("DialogueText", "Level1") == false) { // Mouse click
                float DirX = InternalCalls.GetWorldMousePosX() + InternalCalls.GetCurrentCameraPosX() - PlayerPosX;
                float DirY = InternalCalls.GetWorldMousePosY() + InternalCalls.GetCurrentCameraPosY() - PlayerPosY;
                float NormX = 0f, NormY = 0f;
                if (InternalCalls.SqMagnitude(DirX, DirY) > Epsilon * Epsilon) {
                    NormX = InternalCalls.NormalizeX(DirX, DirY);
                    NormY = InternalCalls.NormalizeY(DirX, DirY);
                    ApplyForce("Boat", "Level1", NormX, NormY, PlayerSpeed);
                }
                PlayerRotation = GetRotation(NormX, NormY);
                SetCharRotation(PlayerRotation, "Boat", "Level1", "Idle");
            }
            #endregion

            #region Enemy
            //InternalCalls.SetCurrentCameraScaleX(5500);
            float EnemyChangeInX = 0;
            float EnemyChangeInY = 0;
            Random rand = new Random();
            float EnemyPosX = InternalCalls.GetPosX("Enemy", "Level1");
            float EnemyPosY = InternalCalls.GetPosY("Enemy", "Level1");
            float EnemyDisX = EnemyPosX - PlayerPosX;
            float EnemyDisY = EnemyPosY - PlayerPosY;
            float EnemyNormDisX = 0f, EnemyNormDisY = 0f;
            if (InternalCalls.SqMagnitude(EnemyDisX, EnemyDisY) > Epsilon * Epsilon) {
                EnemyNormDisX = InternalCalls.NormalizeX(EnemyDisX, EnemyDisY);
                EnemyNormDisY = InternalCalls.NormalizeY(EnemyDisX, EnemyDisY);
            }

            // Enemy is in screen
            if (EnemyPosX <= InternalCalls.GetCurrentCameraPosX() + (InternalCalls.GetCurrentCameraScaleX() / 2) &&
                EnemyPosY <= InternalCalls.GetCurrentCameraPosY() + (InternalCalls.GetCurrentCameraScaleY() / 2) &&
                EnemyPosX >= InternalCalls.GetCurrentCameraPosX() - (InternalCalls.GetCurrentCameraScaleX() / 2) &&
                EnemyPosY >= InternalCalls.GetCurrentCameraPosY() - (InternalCalls.GetCurrentCameraScaleY() / 2)) {
                float EnemyRotation = 0;
                EnemyRotation = GetRotation(EnemyNormDisX, EnemyNormDisY);
                //SetCharRotation(EnemyRotation, "Enemy", "Level1", "Idle");

                // Chasing player
                if (InternalCalls.Negate(EnemyDisX) <= InternalCalls.GetScaleX("EnemyTrigger", "Level1") && InternalCalls.Negate(EnemyDisY) <= InternalCalls.GetScaleY("EnemyTrigger", "Level1")) {
                    EnemyLoiter = false;
                    //if (InternalCalls.SqMagnitude(EnemyDisX, EnemyDisY) > Epsilon * Epsilon) {
                    //    ApplyForce("Enemy", "Level1", EnemyNormDisX, EnemyNormDisY, EnemySpeed);
                    //    ApplyForce("EnemyTrigger", "Level1", EnemyNormDisX, EnemyNormDisY, EnemySpeed);
                    //}
                    EnemyChangeInX = (EnemyDisX > -1 && EnemyDisX < 1 ? EnemyDisX : 1);
                    EnemyChangeInY = (EnemyDisY > -1 && EnemyDisY < 1 ? EnemyDisY : 1);
                    EnemyChangeInX = (EnemyDisX > 0 ? -EnemyChangeInX : EnemyChangeInX);
                    EnemyChangeInY = (EnemyDisY > 0 ? -EnemyChangeInY : EnemyChangeInY);
                }
                else EnemyLoiter = true;

                if (InternalCalls.EntitiesCollided("Boat", "EnemyTrigger", "Level1")) {
                    switch (OctopusAttacked) {
                        case 0:
                            OctopusAttacked = 1;
                            InternalCalls.PlaySoundOnLoop("EnemyTrigger", "Level1");
                            SetCharRotation(EnemyRotation, "Enemy", "Level1", "Rising");
                            InternalCalls.SetAnimationCurrentIndex("Enemy", "Level1", 0);
                            HitInterval = (int)(20 * InternalCalls.GetAnimationSpeed("Enemy", "Level1") * InternalCalls.GetAnimationFrameCount("Enemy", "Level1"));
                            HealInterval = HitInterval * 4;
                            break;
                        case 1:
                            if (InternalCalls.GetAnimationCurrentIndex("Enemy", "Level1") == InternalCalls.GetAnimationFrameCount("Enemy", "Level1") - 1) {
                                SetCharRotation(EnemyRotation, "Enemy", "Level1", "Attack1");
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
                    SetCharRotation(EnemyRotation, "Enemy", "Level1", "Idle");
                }

                if ((InternalCalls.EntitiesCollided("Boat", "Enemy", "Level1") || InternalCalls.EntitiesCollided("Enemy", "Boat", "Level1")) && HitTaken != -1) {
                    //Console.Write("HitCounter!\n");
                    ++HitCounter;
                    if (HitCounter >= HitInterval) {
                        //Console.Write("Attacking!\n");
                        HitCounter = 0;
                        ++HitTaken;
                        InternalCalls.SetTexture("hpbar", "Dialogue", "Textures\\Icons\\healthbar-" + (HitTaken + 1) + ".png");
                    }

                    SetCharRotation(PlayerRotation, "Boat", "Level1", "Hit");
                }

                if(HitTaken == MaxHealth) {
                    Console.Write("MaxHealth");
                    SetCharRotation(PlayerRotation, "Boat", "Level1", "Death");
                    InternalCalls.SetAnimationCurrentIndex("Boat", "Level1", 0);
                    HitTaken = -1;
                }
                if (HitTaken == -1 && InternalCalls.GetAnimationCurrentIndex("Boat", "Level1") == InternalCalls.GetAnimationFrameCount("Boat", "Level1") - 1) {
                    InternalCalls.PauseScene("Level1");
                    InternalCalls.PlayScene("Game Over");
                }
            }

            // Loitering
            if (EnemyLoiter) {
                switch (CheckRegion("Enemy", "Level1")) {
                    case 1:
                        EnemyChangeInX = rand.Next(0, 5);
                        EnemyChangeInY = rand.Next(-4, 1);
                        //Console.Write("Region 1!\n");
                        break;
                    case 2:
                        EnemyChangeInX = rand.Next(-4, 1);
                        EnemyChangeInY = rand.Next(-4, 1);
                        //Console.Write("Region 2!\n");
                        break;
                    case 3:
                        EnemyChangeInX = rand.Next(-4, 1);
                        EnemyChangeInY = rand.Next(0, 5);
                        //Console.Write("Region 3!\n");
                        break;
                    case 4:
                        EnemyChangeInX = rand.Next(0, 5);
                        EnemyChangeInY = rand.Next(0, 5);
                        //Console.Write("Region 4!\n");
                        break;
                    default:
                        break;
                }
            }

            // Updating enemy position
            EnemyChangeInX = (((EnemyPosX + EnemyChangeInX) < maxX) && ((EnemyPosX + EnemyChangeInX) > minX)) ? EnemyChangeInX : 0;
            EnemyChangeInY = (((EnemyPosY + EnemyChangeInY) < maxY) && ((EnemyPosY + EnemyChangeInY) > minY)) ? EnemyChangeInY : 0;
            InternalCalls.SetPosX("EnemyTrigger", "Level1", EnemyPosX + EnemyChangeInX);
            InternalCalls.SetPosY("EnemyTrigger", "Level1", EnemyPosY + EnemyChangeInY);
            InternalCalls.SetPosX("Enemy", "Level1", EnemyPosX + EnemyChangeInX);
            InternalCalls.SetPosY("Enemy", "Level1", EnemyPosY + EnemyChangeInY);

            // Healing player
            if (!InternalCalls.EntitiesCollided("Boat", "Enemy", "Level1") && HitTaken > 0) {
                ++HealCounter;
                if (HealCounter >= HealInterval) {
                    //Console.Write("Regenerating!\n");
                    SetCharRotation(PlayerRotation, "Boat", "Level1", "Idle");
                    HealCounter = 0;
                    --HitTaken;
                    InternalCalls.SetTexture("hpbar", "Dialogue", "Textures\\Icons\\healthbar-" + (HitTaken + 1) + ".png");
                }
            }
            #endregion

            #region cutscene1
            //if (InternalCalls.GetCurrentGameStateName() == "cutscene1state")
            {
                if ((InternalCalls.ButtonReleased("cutscene1button", "cutscene1")) == true)
                {
                    InternalCalls.PauseScene("cutscene1");
                }
            }
            #endregion
        }

        #region UI, Camera, Text Align Functions
        public void DisableUI() {
            InternalCalls.EntityDeactivate("hpbar", "Dialogue");
            InternalCalls.EntityDeactivate("memoryfragment", "Dialogue");
            InternalCalls.EntityDeactivate("memoryfragmentscreen", "Dialogue");
            InternalCalls.EntityDeactivate("fragment1obj", "Dialogue");

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
                case 6:
                    InternalCalls.SetScaleX(entityname, scenename, 740);
                    InternalCalls.SetScaleY(entityname, scenename, 320);

                    InternalCalls.SetPosX(entityname, scenename, -387);
                    InternalCalls.SetPosY(entityname, scenename, 89);

                    InternalCalls.SetTextOffset(entityname, scenename, -340, 100);
                    break;
            }
        }

    public void TextAlignChoices(string entityname, string scenename, int choice) {
      int additionalLines = InternalCalls.GetLineCount(entityname, scenename) - 1;
      int middle = -25;         // This is the center point of both texts
      int spaceing = 15;        // Spacing between edge from middle
      int scaleX = 500;         // This is the default width of button
      int scaleY = 100;         // This is the default height of button, will changing with respect to line count
      int buttonCenterX = 500;  // Center X coordinate of button
      int buttonCenterY = 0;    // This must be calculated, differs for different choices
      int perLineScaleY = 60;   // This is the increment for one additional line
      int textXSpacing = 50;    // This is the spacing of the text from the left edge of the box 
      int textYSpacing = 20;    // This is the spacing of the text from the top edge of the box 

      InternalCalls.SetScaleX(entityname, scenename, scaleX);
      InternalCalls.SetScaleY(entityname, scenename, scaleY + perLineScaleY* additionalLines);

      if (choice == 1) {
        buttonCenterY = middle + spaceing + scaleY/2 + perLineScaleY * additionalLines / 2;
      } else buttonCenterY = middle - spaceing - scaleY / 2 - perLineScaleY * additionalLines / 2;

      InternalCalls.SetPosX(entityname, scenename, buttonCenterX);
      InternalCalls.SetPosY(entityname, scenename, buttonCenterY);

      int textY = perLineScaleY * additionalLines / 2 - textYSpacing;

      InternalCalls.SetTextOffset(entityname, scenename, -scaleX/2 + textXSpacing, textY);
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
      int ID = 0;
      if (choice == 1) {
        ID = InternalCalls.GetNextDialogueID(InternalCalls.GetCurrentDialogueID());
        //Console.WriteLine("Choice 1 is: " + ID);
      } else {
        ID = InternalCalls.GetChoice2(InternalCalls.GetCurrentDialogueID());
        //Console.WriteLine("Choice 2 is: " + ID);
      }
      //Console.WriteLine("Resultant line is: " + InternalCalls.GetDialogue(ID));
      return InternalCalls.GetDialogue(ID);
    }

    /* For carrying on the dialog conversation logic
     * player - The chatbox entity of the player
     * notPlayer - The chatbox entity of the entity the player is talking to
     * choice1 - The chatbox entity of the first choice dialog
     * choice2 - The chatbox entity of the second choice dialog
     * scene - The scene of all the chatbox entities (All must be the same scene)
     * dialogFile - Dialog file name
     * return bool - True if dialog is still running. False if dialog has ended.
    */
    public bool RunDialog(string player, string notPlayer, string choice1, string choice2, string scene, string dialogFile) {
      if (!starttalking) {
        DisableUI();
        // Load Little Girl Talking
        InternalCalls.LoadDialogs(dialogFile);
        InternalCalls.SetCurrentDialogueID(1);

        // Activate little girl dialogue
        InternalCalls.EntityActivate(notPlayer, scene);
        InternalCalls.UpdateText(notPlayer, scene, InternalCalls.GetDialogue(InternalCalls.GetCurrentDialogueID()));
        TextAlign(notPlayer, scene);

        // Setting default P1, PP1, PP2 positions
        InternalCalls.SetPosX(choice1, scene, 500);
        InternalCalls.SetPosY(choice1, scene, 46);
        InternalCalls.SetPosX(choice2, scene, 500);
        InternalCalls.SetPosY(choice2, scene, -90);
        InternalCalls.SetPosX(player, scene, 450);
        InternalCalls.SetPosY(player, scene, 5);

        starttalking = true;

        CameraZoomIn();
        starttalking = true;
      }

      // Button click set flags
      if (choiceFlag) {
        if (InternalCalls.ButtonReleased(choice1, scene) || InternalCalls.ButtonReleased(choice2, scene)) updateChat = true;
      } else if (InternalCalls.ButtonReleased(player, scene) || InternalCalls.ButtonReleased(notPlayer, scene)) updateChat = true;

      // Logic done using those flags
      if (updateChat) {
        updateChat = false;

        // Finish dialog
        if (InternalCalls.GetNextDialogueID(InternalCalls.GetCurrentDialogueID()) == 0) {
          DeactivateDialogBox(player, notPlayer, choice1, choice2, scene);
          starttalking = false;
          CameraZoomOut();
          EnableUI();
          //Console.WriteLine("finished dialog");
          return false;
        }

        //Console.WriteLine("Moving on from: " + InternalCalls.GetCurrentDialogueID());
        if (choiceFlag) {
          //Console.WriteLine("It's a choice dialog");
          choiceFlag = false;
          if (InternalCalls.ButtonReleased(choice2, scene)) {
            MoveToNextDialog(2);
            //Console.WriteLine("Choice 2 selected, moving to: " + InternalCalls.GetCurrentDialogueID());
          } else {
            MoveToNextDialog(1);
            //Console.WriteLine("Choice 1 selected, moving to: " + InternalCalls.GetCurrentDialogueID());
          }
          InternalCalls.EntityDeactivate(choice1, scene);
          InternalCalls.EntityDeactivate(choice2, scene);
        }
        MoveToNextDialog(1);
        //Console.WriteLine("Moving to: " + InternalCalls.GetCurrentDialogueID());

        if (InternalCalls.IsPlayerSpeaker(InternalCalls.GetCurrentDialogueID())) {
          InternalCalls.EntityActivate(player, scene);
          InternalCalls.EntityDeactivate(notPlayer, scene);
          InternalCalls.UpdateText(player, scene, InternalCalls.GetDialogue(InternalCalls.GetCurrentDialogueID()));
        } else {
          InternalCalls.EntityActivate(notPlayer, scene);
          InternalCalls.EntityDeactivate(player, scene);
          InternalCalls.UpdateText(notPlayer, scene, InternalCalls.GetDialogue(InternalCalls.GetCurrentDialogueID()));
          TextAlign(notPlayer, scene);
        }

        if (InternalCalls.GetChoice2(InternalCalls.GetCurrentDialogueID()) != 0) {
          //Console.WriteLine("This dialog is a choice dialog: " + InternalCalls.GetCurrentDialogueID());
          InternalCalls.EntityActivate(choice1, scene);
          InternalCalls.EntityActivate(choice2, scene);
          InternalCalls.UpdateText(choice1, scene, GetNextDialog(1));
          InternalCalls.UpdateText(choice2, scene, GetNextDialog(2));
          TextAlignChoices(choice1, scene, 1);
          TextAlignChoices(choice2, scene, 2);
          choiceFlag = true;
        }
      }
      return true;
    }

    public void DeactivateDialogBox(string player, string notPlayer, string choice1, string choice2, string scene) {
      InternalCalls.EntityDeactivate(player, scene);
      InternalCalls.EntityDeactivate(notPlayer, scene);
      InternalCalls.EntityDeactivate(choice1, scene);
      InternalCalls.EntityDeactivate(choice2, scene);
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
            //Console.Write("Out of bounds!\n");
            return -1;
        }

        public float GetRotation(float _x, float _y) {
            float Rotation = 0;
            if (_y != 0f && _x >= 0f)
                Rotation = InternalCalls.ArcTangent(_y, _x);
            else if (_y == 0f && _x > 0f)
                Rotation = (float)Pi / 2;
            else if (_y != 0f && _x < 0f) {
                Rotation = InternalCalls.ArcTangent(_y, _x);
                Rotation += Rotation < 0f ? (float)Pi * 2f : 0f;
            } else Rotation = 3f * (float)Pi / 2f;
            return Rotation;
        }

        public void SetCharRotation(float _rotation, string _entityName, string _sceneName, string _status) {
            int InitialStatus = 0;
            switch (_status) {
                case "Idle":
                    InitialStatus = 8;
                    break;
                case "Hit":
                case "Rising":
                    InitialStatus = 16;
                    break;
                case "Death":
                case "Attack1":
                    InitialStatus = 24;
                    break;
                case "Attack2":
                    InitialStatus = 32;
                    break;
                default:
                    break;
            }
            if (_rotation < 0) _rotation += 2 * (float)Pi;
            if (_rotation >= 15f * MiniAngle || _rotation <= MiniAngle) InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus-2);
            else if (_rotation <= 3f * MiniAngle) InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus-3);
            else if (_rotation <= 5f * MiniAngle) InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus-4);
            else if (_rotation <= 7f * MiniAngle) InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus-5);
            else if (_rotation <= 9f * MiniAngle) InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus-6);
            else if (_rotation <= 11f * MiniAngle) InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus-7);
            else if (_rotation <= 13f * MiniAngle) InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus-8);
            else InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus-1);
        }

        public void ApplyForce(string _entityName, string _sceneName, float _x, float _y, float _multiplier) {
            InternalCalls.ApplyImpulse(_entityName, _sceneName,
                (_x * _multiplier * (float)InternalCalls.GetDeltaTime()),
                (_y * _multiplier * (float)InternalCalls.GetDeltaTime()), 0f, 0f);
        }
    }
}
