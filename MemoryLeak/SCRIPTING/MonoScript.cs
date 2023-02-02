/*!*****************************************************************************
\file MonoScript.cs
\author Jazz Teoh Yu Jue, Chen Jia Wen, Kew Yu Jun, Xiu Han, Huang Wei Jhin
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 27-01-2023
\brief
MonoScript contains multiple script components to run the Level1 of the game.
Part of which are:
- Dialog management Script
- Passenger delivery Script
- Camera updating script
- Enemy logic
- Memory fragment logic
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage
{
    public class MonoScript
    {
        private int fragment1;
        private bool starttalking;
        private float maxX, maxY, minX, minY, halfX, halfY;
        private float HitInterval;
        private float HitCounter;
        private int HitTaken;
        private float HealInterval;
        private float HealCounter;
        private int OctopusAttacked;
        private float OctopusDirection;
        private float PlayerRotation;
        private float PlayerSpeed;
        private float EnemySpeed;
        private bool EnemyLoiter;
        private float perlineScale;
        private const int MaxHealth = 12;
        private const float Epsilon = 1.192092896e-07F;
        private const double Pi = 3.141592653589793238f;
        private const float MiniAngle = (float)Pi / 8;
        private const float RightAngle = (float)Pi / 2;
        private const float RadToDeg = 180/(float)Pi;

        /* Some of these flags are here to optimise the code. Because checking this bool value is faster than button check function calls */
        private bool choiceFlag;            // This flag is true during choice selection dialogs
        private bool playerTalking;         // This flag is true when player is talking, aka P1 active
        private bool updateChat;            // This flag is true when dialog changes for anyone
        private bool RunIntroDialog;         // This flag is true if the dialog has not player and should play
        private bool RunlittleGirlDialog;    // This flag is true if the dialog has not player and should play
        private bool RunPassengerDialog;     // This flag is true if the dialog has not player and should play
        private bool AllowAdvance;

        private string currentobjective;
        private bool objectiveexpanded;

        private bool camZoomingIn;
        private bool camZoomingOut;
        private float camScaleX;

        private float CatPosX;
        private float CatPosY;
        private float CatFlyTime;
        private float CatSpeedX;
        private float CatSpeedY;
        private float oriFragScaleX;
        private int dialogueOrder;
    public void InitVariables() {
      fragment1 = 0;
      starttalking = false;
      maxX = maxY = minX = minY = halfX = halfY = 0;
      HitInterval = 0;
      HitCounter = 0;
      HitTaken = 0;
      HealInterval = 0;
      HealCounter = 0;
      OctopusAttacked = 0;
      OctopusDirection = 0;
      PlayerRotation = 0;
      PlayerSpeed = 500f;
      EnemySpeed = 40f;
      EnemyLoiter = true;
      perlineScale = 49.5f;

      choiceFlag = false;            
      playerTalking = false;         
      updateChat = false;            
      RunIntroDialog = true;         
      RunlittleGirlDialog = true;    
      RunPassengerDialog = true;     
      AllowAdvance = false;

      currentobjective = "";
      objectiveexpanded = false;

      camZoomingIn = false;
      camZoomingOut = false;
      camScaleX = 700;

      CatFlyTime = 1.2f;
      CatSpeedX = 0;
      CatSpeedY = 0;
      oriFragScaleX = 0;

    }
  public void Init()
      {
          //InternalCalls.LoadDialogs("Dialogue LittleGirl 0");
          InitVariables();
          halfX = InternalCalls.GetPosX("Water", "Level1");
          halfY = InternalCalls.GetPosY("Water", "Level1");
          maxX = (InternalCalls.GetScaleX("Water", "Level1") / 2) + halfX - InternalCalls.GetScaleX("Enemy", "Level1");
          maxY = (InternalCalls.GetScaleY("Water", "Level1") / 2) + halfY - InternalCalls.GetScaleY("Enemy", "Level1");
          minX = halfX - (InternalCalls.GetScaleX("Water", "Level1") / 2) + InternalCalls.GetScaleX("Enemy", "Level1");
          minY = halfY - (InternalCalls.GetScaleY("Water", "Level1") / 2) + InternalCalls.GetScaleY("Enemy", "Level1");
          CatPosX = InternalCalls.GetPosX("memoryfragment", "Dialogue");
          CatPosY = InternalCalls.GetPosY("memoryfragment", "Dialogue");
          dialogueOrder = 0;
          InternalCalls.PlaySoundOnLoop("EnemyTrigger", "Level1");
        }

      public void Update() {
          #region Intro Dialogue
          if (InternalCalls.EntitiesCollided("Boat", "IntroBox", "Level1")) {
              if (RunIntroDialog && InternalCalls.EntityIsActive("IntroBox", "Level1")) {
                LockPosition(160, 120);
                RunIntroDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialogue SceneIntro 1");
                if (!RunIntroDialog) {
                  InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Find the Little Girl");// for the start Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras fermentum est nec rutrum venenatis. Suspendisse facilisis lectus ornare nisi feugiat, sed eleifend nisi molestie. Vestibulum et malesuada tortor. Donec eget diam vel lorem consequat tempus. Maecenas at mollis tellus. Maecenas dolor nisl, scelerisque a eleifend ornare, rhoncus nec leo. Praesent ultricies vehicula placerat. Etiam ligula enim, tempus sed tempor at, congue in ante. Ut condimentum non mauris ac efficitur."); // hint
                }
              }
              if (!RunIntroDialog) TextAlignChoices("objectivetext", "Dialogue", 500, 350, 530, 51.0f, 20, 10);
          }
    #endregion

    //TextAlignChoices("objectivetext", "Dialogue", 400, 1800, 600);

    #region Little Girl Dialogue
    if (InternalCalls.EntitiesCollided("Boat", "LittleGirlBox", "Level1")&& dialogueOrder==0) {
      // I'll be using G1, P1, PP1 and PP2 for the refactored code
      if (InternalCalls.EntityIsActive("LittleGirlBox", "Level1") && RunlittleGirlDialog) {
        LockPosition(-295, -85);
        InternalCalls.SetSpriteSheetIndex("Boat", "Level1", 1);
        RunlittleGirlDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialogue LittleGirl 0");

        if (!RunlittleGirlDialog) {
            
            InternalCalls.EntityDeactivate("LittleGirlBox", "Level1");
            SetObjectiveText();
            dialogueOrder = 1;
        }
      }
    }
            #endregion
            if (dialogueOrder == 1)
            {
                if (InternalCalls.GetScaleX("Little Girl", "Level1") >0)
                {
                    InternalCalls.SetPosY("Little Girl", "Level1", InternalCalls.GetPosY("Little Girl", "Level1") + 200 * (float)InternalCalls.GetDeltaTime());
                    InternalCalls.SetScaleX("Little Girl", "Level1", InternalCalls.GetScaleX("Little Girl", "Level1") - 10.0f * (float)InternalCalls.GetDeltaTime());
                    InternalCalls.SetScaleY("Little Girl", "Level1", InternalCalls.GetScaleY("Little Girl", "Level1") - 10.0f * (float)InternalCalls.GetDeltaTime());
                }
                else
                    InternalCalls.EntityDeactivate("Little Girl", "Level1");

            }
          #region Passenger 1 Dialogue
          if (InternalCalls.EntitiesCollided("Boat", "PassengerBox", "Level1")&&(dialogueOrder==1))
          {
              if (RunPassengerDialog && !InternalCalls.EntityIsActive("LittleGirlBox", "Level1"))
              {
                  LockPosition(-1240, 670);
                  InternalCalls.SetSpriteSheetIndex("Boat", "Level1", 1);
                  RunPassengerDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialogue Passenger 1");

                  if (!RunPassengerDialog)
                  {
                      //SetPosition("Passenger_1", "Level1", -1240, 670);
                      InternalCalls.SetRotate("Passenger_1", "Level1", 0.5f);
                      SetObjectiveText();
                      AllowAdvance = true;
                        dialogueOrder = 2;
                  }
              }
          }
          #endregion

          #region Passenger 1 Delivered
          if (AllowAdvance && InternalCalls.EntitiesCollided("Boat", "destination", "Level1"))
          {
              InternalCalls.PlayScene("cutscene1");
              InternalCalls.EntityDeactivate("destination", "Level1");
          }
          #endregion

          #region Memory Fragment UI

          if (InternalCalls.EntitiesCollided("Boat", "fragment1drop", "Level1")&& fragment1==0)
          {
              Console.Write("COLLECTED");
              fragment1 = 1;
              InternalCalls.UpdateText("memoryfragmentscreen", "Dialogue", "Memory Fragments (1/1)");
              //InternalCalls.SetLayer("fragment1drop", "Level1", 100);///////////////////////////////////////////    need set layer higher
              InternalCalls.PlayEntitySound("fragment1drop", "Level1");
              //InternalCalls.EntityDeactivate("fragment1drop", "Level1");
          }

          if (fragment1 == 1)//cat rising up
          {

              if (InternalCalls.GetPosY("fragment1drop", "Level1") >  InternalCalls.GetScaleY("Boat", "Level1")/2 + InternalCalls.GetPosY("Boat", "Level1"))
                  fragment1 = 2;
              else
              { 
                  InternalCalls.SetPosY("fragment1drop", "Level1", InternalCalls.GetPosY("fragment1drop", "Level1") + 200 *(float)InternalCalls.GetDeltaTime());
                  InternalCalls.SetScaleX("fragment1drop", "Level1", InternalCalls.GetScaleX("fragment1drop", "Level1") + 100.0f * (float)InternalCalls.GetDeltaTime());
                  InternalCalls.SetScaleY("fragment1drop", "Level1", InternalCalls.GetScaleY("fragment1drop", "Level1") + 100.0f * (float)InternalCalls.GetDeltaTime());
              }
          }
          else if (fragment1 == 2)//make cat fly to memoryfragment
          {
              float uiPosX = InternalCalls.GetPosX("memoryfragment", "Dialogue") + InternalCalls.GetCurrentCameraPosX();
              float uiPosY = InternalCalls.GetPosY("memoryfragment", "Dialogue") + InternalCalls.GetCurrentCameraPosY();

              CatSpeedX = (uiPosX - InternalCalls.GetPosX("fragment1drop", "Level1")) / CatFlyTime;
              CatSpeedY = (uiPosY - InternalCalls.GetPosY("fragment1drop", "Level1")) / CatFlyTime;

              CatFlyTime -= (float)InternalCalls.GetDeltaTime();

              InternalCalls.SetPosX("fragment1drop", "Level1", InternalCalls.GetPosX("fragment1drop", "Level1") + CatSpeedX * (float)InternalCalls.GetDeltaTime());
              InternalCalls.SetPosY("fragment1drop", "Level1", InternalCalls.GetPosY("fragment1drop", "Level1") + CatSpeedY * (float)InternalCalls.GetDeltaTime());
              InternalCalls.SetScaleX("fragment1drop", "Level1", InternalCalls.GetScaleX("fragment1drop", "Level1") - 100.0f * (float)InternalCalls.GetDeltaTime());
              InternalCalls.SetScaleY("fragment1drop", "Level1", InternalCalls.GetScaleY("fragment1drop", "Level1") - 100.0f * (float)InternalCalls.GetDeltaTime());
              InternalCalls.SetRotate("fragment1drop", "Level1", InternalCalls.GetRotate("fragment1drop", "Level1") + 10.0f * (float)InternalCalls.GetDeltaTime());
              if (CatFlyTime < 0)
              {
                  InternalCalls.EntityDeactivate("fragment1drop", "Level1");
                  fragment1 = 4;
                  oriFragScaleX = InternalCalls.GetScaleX("memoryfragment", "Dialogue");
              }
          }
          else if (fragment1 == 4)
          {
              if (InternalCalls.GetScaleX("memoryfragment", "Dialogue") < oriFragScaleX+30)
              { 
                  InternalCalls.SetScaleX("memoryfragment", "Dialogue", InternalCalls.GetScaleX("memoryfragment", "Dialogue") + 100 * (float)InternalCalls.GetDeltaTime());
                  InternalCalls.SetScaleY("memoryfragment", "Dialogue", InternalCalls.GetScaleY("memoryfragment", "Dialogue") + 100 * (float)InternalCalls.GetDeltaTime());
              }
              else
                  fragment1 = 5;

          }
          else if (fragment1 == 5)
          {
              if (InternalCalls.GetScaleX("memoryfragment", "Dialogue") > oriFragScaleX)
              {
                  InternalCalls.SetScaleX("memoryfragment", "Dialogue", InternalCalls.GetScaleX("memoryfragment", "Dialogue") - 100 * (float)InternalCalls.GetDeltaTime());
                  InternalCalls.SetScaleY("memoryfragment", "Dialogue", InternalCalls.GetScaleY("memoryfragment", "Dialogue") - 100 * (float)InternalCalls.GetDeltaTime());
              }
              else
                  fragment1 = 6;

          }
          if ((InternalCalls.ButtonReleased("memoryfragment", "Dialogue")) == true) {
              if (InternalCalls.EntityIsActive("memoryfragmentscreen", "Dialogue") == false) {
                  InternalCalls.EntityActivate("memoryfragmentscreen", "Dialogue");
                  if (fragment1 != 0) { InternalCalls.EntityActivate("fragment1obj", "Dialogue"); }
              } else {
                  InternalCalls.EntityDeactivate("memoryfragmentscreen", "Dialogue");
                  if (fragment1 != 0) { InternalCalls.EntityDeactivate("fragment1obj", "Dialogue"); }
              }
          }
          #endregion

          #region Objective UI
          if ((InternalCalls.ButtonReleased("objectivetext", "Dialogue") && currentobjective != "") == true)
          {
              if (objectiveexpanded)
              {
                  objectiveexpanded = false;
              }
              else
              {
                  objectiveexpanded = true;
              }

              if (objectiveexpanded)
              {
                  InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: " + currentobjective); // hint
                  TextAlignChoices("objectivetext", "Dialogue", 500, 350, 530, 51.0f, 20, 10);

      }

      if (!objectiveexpanded)
              {
                  InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Click to view"); // hint
                  TextAlignChoices("objectivetext", "Dialogue", 500, 350, 530, 51.0f, 20, 10);

      }
    }
          #endregion

          #region Player
          float PlayerPosX = InternalCalls.GetPosX("Boat", "Level1");
          float PlayerPosY = InternalCalls.GetPosY("Boat", "Level1");
          float PlayerScaleX = InternalCalls.GetScaleX("Boat", "Level1");
          float PlayerScaleY = InternalCalls.GetScaleY("Boat", "Level1");
          if (!starttalking && InternalCalls.CheckKeyHold(349) && InternalCalls.EntityIsActive("DialogueText", "Level1") == false) { // Mouse click
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
              InternalCalls.PlayEntitySound("Boat", "Level1");
            }
            if (!InternalCalls.CheckKeyHold(349))
            {
                InternalCalls.StopSound("Boat", "Level1");
            }
            #endregion

            #region Camera Update
            UpdateCamera();
          #endregion

          #region Enemy
          //InternalCalls.SetCurrentCameraScaleX(5500);
          float EnemyChangeInX = 0;
          float EnemyChangeInY = 0;
          Random rand = new Random();
          float EnemyPosX = InternalCalls.GetPosX("Enemy", "Level1");
          float EnemyPosY = InternalCalls.GetPosY("Enemy", "Level1");
          float EnemyScaleX = InternalCalls.GetScaleX("Enemy", "Level1");
          float EnemyScaleY = InternalCalls.GetScaleY("Enemy", "Level1");
          float EnemyDisX = PlayerPosX - EnemyPosX;
          float EnemyDisY = PlayerPosY - EnemyPosY;
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
                //float EnemyRotation = GetRotation(EnemyNormDisX, EnemyNormDisY);
                /*
                if (EnemyRotation < 0) OctopusDirection = 1;
                else OctopusDirection = (int)(InternalCalls.Negate(EnemyRotation) / Pi);
                */
                //Console.Write(OctopusDirection + "\n");
                //Console.Write((EnemyRotation / Pi / 2) + "\n");
                OctopusDirection = GetRotation(EnemyNormDisX, EnemyNormDisY);
                //OctopusDirection = (int)(InternalCalls.Negate(EnemyRotation));
                //Console.Write(OctopusDirection + "\n");

                // Chasing player
                if (!starttalking && InternalCalls.Negate(EnemyDisX) <= InternalCalls.GetScaleX("EnemyTrigger", "Level1") && InternalCalls.Negate(EnemyDisY) <= InternalCalls.GetScaleY("EnemyTrigger", "Level1")) {
                    EnemyLoiter = false;
                    //if (InternalCalls.SqMagnitude(EnemyDisX, EnemyDisY) > Epsilon * Epsilon) {
                    //    ApplyForce("Enemy", "Level1", EnemyNormDisX, EnemyNormDisY, EnemySpeed);
                    //    ApplyForce("EnemyTrigger", "Level1", EnemyNormDisX, EnemyNormDisY, EnemySpeed);
                    //}
                    EnemyChangeInX = (EnemyDisX > -1 && EnemyDisX < 1 ? 0 : EnemySpeed);
                    EnemyChangeInY = (EnemyDisY > -1 && EnemyDisY < 1 ? 0 : EnemySpeed);
                    EnemyChangeInX = (EnemyDisX > 0 ? EnemyChangeInX : -EnemyChangeInX);
                    EnemyChangeInY = (EnemyDisY > 0 ? EnemyChangeInY : -EnemyChangeInY);
                }
                else EnemyLoiter = true;

                // Attacking player
                if (!starttalking && InternalCalls.EntitiesCollided("Boat", "EnemyTrigger", "Level1")) {
                    switch (OctopusAttacked) {
                        case 0:
                            OctopusAttacked = 1;
                            //InternalCalls.PlaySoundOnLoop("EnemyTrigger", "Level1");
                            SetCharRotation4(OctopusDirection, "Enemy", "Level1", "Rising");
                            InternalCalls.SetAnimationCurrentIndex("Enemy", "Level1", 0);
                            HitInterval = InternalCalls.GetAnimationSpeed("Enemy", "Level1") * InternalCalls.GetAnimationFrameCount("Enemy", "Level1");
                            HealInterval = HitInterval * 3.0f;
                            break;
                        case 1:
                            if (InternalCalls.GetAnimationCurrentIndex("Enemy", "Level1") == InternalCalls.GetAnimationFrameCount("Enemy", "Level1") - 1) {
                                SetCharRotation4(OctopusDirection, "Enemy", "Level1", "Attack1");
                                InternalCalls.SetAnimationCurrentIndex("Enemy", "Level1", 0);
                                OctopusAttacked = 2;
                            }
                            break;
                        case 2:
                            SetCharRotation4(OctopusDirection, "Enemy", "Level1", "Attack1");
                            break;
                        default:
                            SetCharRotation4(OctopusDirection, "Enemy", "Level1", "Idle");
                            break;
                    }
                } else {
                    OctopusAttacked = 0;
                    //InternalCalls.StopSound("EnemyTrigger", "Level1");
                    SetCharRotation4(OctopusDirection, "Enemy", "Level1", "Idle");
                }

                if (InternalCalls.CheckCollision("Boat", "Enemy", "Level1", true) && HitTaken != -1) {
                    //Console.Write("HitCounter!\n");
                    HitCounter += (float)InternalCalls.GetDeltaTime();
                    if (HitCounter >= HitInterval) {
                        //Console.Write("Attacking!\n");
                        HitCounter = 0;
                        ++HitTaken;
                        InternalCalls.PlayEntitySound("Enemy", "Level1");
                        InternalCalls.SetTexture("hpbar", "Dialogue", "Textures\\Icons\\healthbar-" + (HitTaken + 1) + ".png");
                    }
                    SetCharRotation(PlayerRotation, "Boat", "Level1", "Hit");

                    EnemyChangeInX = 0;
                    EnemyChangeInY = 0;
                }
                else{
                    SetCharRotation(PlayerRotation, "Boat", "Level1", "Idle");
                }

                // Player dies
                if(HitTaken == MaxHealth) {
                    SetCharRotation(PlayerRotation, "Boat", "Level1", "Death");
                    InternalCalls.SetAnimationCurrentIndex("Boat", "Level1", 0);
                    HitTaken = -1;
                }
                if (HitTaken == -1 && InternalCalls.GetAnimationCurrentIndex("Boat", "Level1") == InternalCalls.GetAnimationFrameCount("Boat", "Level1") - 1) {
                    InternalCalls.StopSound("EnemyTrigger", "Level1");
                    InternalCalls.PauseScene("Level1");
                    InternalCalls.PlayScene("Game Over");
                }
            }

            if (starttalking) EnemyLoiter = true;

            // Loitering
            if (EnemyLoiter) {
                switch (CheckRegion("Enemy", "Level1")) {
                    case 1:
                        EnemyChangeInX = EnemySpeed;
                        EnemyChangeInY = -EnemySpeed;
                        //Console.Write("Region 1!\n");
                        break;
                    case 2:
                        EnemyChangeInX = -EnemySpeed;
                        EnemyChangeInY = -EnemySpeed;
                        //Console.Write("Region 2!\n");
                        break;
                    case 3:
                        EnemyChangeInX = -EnemySpeed;
                        EnemyChangeInY = EnemySpeed;
                        //Console.Write("Region 3!\n");
                        break;
                    case 4:
                        EnemyChangeInX = EnemySpeed;
                        EnemyChangeInY = EnemySpeed;
                        //Console.Write("Region 4!\n");
                        break;
                    default:
                        break;
                }
            }

            // Updating enemy position
            EnemyChangeInX *= (float)InternalCalls.GetDeltaTime();
            EnemyChangeInY *= (float)InternalCalls.GetDeltaTime();
            EnemyChangeInX = (((EnemyPosX + EnemyChangeInX) < maxX) && ((EnemyPosX + EnemyChangeInX) > minX)) ? EnemyChangeInX : 0;
            EnemyChangeInY = (((EnemyPosY + EnemyChangeInY) < maxY) && ((EnemyPosY + EnemyChangeInY) > minY)) ? EnemyChangeInY : 0;
            InternalCalls.SetPosX("EnemyTrigger", "Level1", EnemyPosX + EnemyChangeInX);
            InternalCalls.SetPosY("EnemyTrigger", "Level1", EnemyPosY + EnemyChangeInY);
            InternalCalls.SetPosX("Enemy", "Level1", EnemyPosX + EnemyChangeInX);
            InternalCalls.SetPosY("Enemy", "Level1", EnemyPosY + EnemyChangeInY);

            // Healing player
            if (!InternalCalls.EntitiesCollided("Boat", "Enemy", "Level1") && HitTaken > 0) {
                HealCounter += (float)InternalCalls.GetDeltaTime();
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

        #region UI, Camera, Text Align, Objective Functions
        public void SetObjectiveText()
        {
            currentobjective = InternalCalls.GetDialogue(InternalCalls.GetCurrentDialogueID());
            InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: " + currentobjective); // hint
            TextAlignChoices("objectivetext", "Dialogue", 500, 350, 700, 51.0f, 20, 10);
            if (InternalCalls.GetLineCount("objectivetext", "Dialogue") > 2)
            {
                InternalCalls.UpdateText("objectivetext", "Dialogue", "Objective: Click to view");
                TextAlignChoices("objectivetext", "Dialogue", 500, 350, 530, 51.0f, 20, 10);
            }
        }

        public void DisableUI() {
            InternalCalls.EntityDeactivate("hpbar", "Dialogue");
            InternalCalls.EntityDeactivate("memoryfragment", "Dialogue");
            InternalCalls.EntityDeactivate("memoryfragmentscreen", "Dialogue");
            InternalCalls.EntityDeactivate("fragment1obj", "Dialogue");

            InternalCalls.EntityDeactivate("cyclemap", "Dialogue");

            InternalCalls.EntityDeactivate("minimap", "Dialogue");
            InternalCalls.EntityDeactivate("enemymap", "Dialogue");
            InternalCalls.EntityDeactivate("weathermap", "Dialogue");

            //InternalCalls.EntityDeactivate("minimapbig", "Dialogue");
            //InternalCalls.EntityDeactivate("enemymapbig", "Dialogue");
            //InternalCalls.EntityDeactivate("weathermapbig", "Dialogue");

            InternalCalls.EntityDeactivate("weathertext", "Dialogue");
            InternalCalls.EntityDeactivate("objectivetext", "Dialogue");
        }

        public void EnableUI() {
            InternalCalls.EntityActivate("hpbar", "Dialogue");
            InternalCalls.EntityActivate("memoryfragment", "Dialogue");

            InternalCalls.EntityActivate("cyclemap", "Dialogue");

            //InternalCalls.EntityActivate("minimap", "Dialogue");

            //InternalCalls.EntityActivate("weathertext", "Dialogue");
            InternalCalls.EntityActivate("objectivetext", "Dialogue");
        }

        public void UpdateCamera()
        {
            if (camZoomingIn)
            {
                camScaleX -= 500 * (float)InternalCalls.GetDeltaTime();
                InternalCalls.SetCurrentCameraScaleX(camScaleX);
                if (camScaleX < 700)
                {
                    camScaleX = 700;
                    InternalCalls.SetCurrentCameraScaleX(700);
                    camZoomingIn = false;
                }
            }
            if (camZoomingOut)
            {
                camScaleX += 500 * (float)InternalCalls.GetDeltaTime();
                InternalCalls.SetCurrentCameraScaleX(camScaleX);
                if (camScaleX > 1600)
                {
                    camScaleX = 1600;
                    InternalCalls.SetCurrentCameraScaleX(1600);
                    camZoomingOut = false;
                }
            }
        }

        // int scaleX           - This is the default width of button
        // int posX             - This is the center X coordinate of button (500)
        // int posY             - This is the center Y coordinate of button. If it's choice, it's the middle of both buttons (-25)
        // int spaceing         - Spacing between choice button edge from middle, useless for single button.
        // int perLineScaleY    - This is the increment for one additional line
        // int textXSpacing     - This is the spacing of the text from the left edge of the box 
        // int textYSpacing     - This is the spacing of the text from the top edge of the box 
        public void TextAlignChoices(string entityname, string scenename, float posX, float posY, float scaleX = 500, float perLineScaleY = 51, float textXSpacing = 50, float textYSpacing = 50, int choice = 0, float spacing = 15)
        {
            int additionalLines = InternalCalls.GetLineCount(entityname, scenename) - 1;
            //Console.WriteLine("lines: " + additionalLines);
            //float scaleY = perLineScaleY;         // This is the default height of button, will changing with respect to line count
            perLineScaleY *= InternalCalls.GetFontScale(entityname, scenename);

            InternalCalls.SetScaleX(entityname, scenename, scaleX);
            InternalCalls.SetScaleY(entityname, scenename, perLineScaleY * (1+additionalLines) + textYSpacing*2);
            
            // If it's a choice textbox, posY is the middle of both texts
            if (choice == 1) posY = posY + spacing + perLineScaleY * (additionalLines+1);
            else if (choice == 2) posY = posY - spacing - perLineScaleY * (additionalLines+1);

            float finalPosY = posY - (perLineScaleY * additionalLines) / 2;

            InternalCalls.SetPosX(entityname, scenename, posX);
            InternalCalls.SetPosY(entityname, scenename, finalPosY);

            float textY = perLineScaleY * additionalLines / 2 - perLineScaleY/2;
            float magicNumber = 10.0f * InternalCalls.GetFontScale(entityname, scenename);
            InternalCalls.SetTextOffset(entityname, scenename, -scaleX / 2 + textXSpacing, textY + magicNumber);
        }

        #endregion

        #region Dialogue helper functions
        // Based on the current dialog ID, move to the next one. Can input choice if there is a choice selection, by default it's 1
        public void MoveToNextDialog(int choice = 1)
        {
            if (choice == 1) InternalCalls.SetCurrentDialogueID(InternalCalls.GetNextDialogueID(InternalCalls.GetCurrentDialogueID()));
            else InternalCalls.SetCurrentDialogueID(InternalCalls.GetChoice2(InternalCalls.GetCurrentDialogueID()));
        }

        // Get the texts of the next dialog, able to input 1 or 2 to get the different choices
        public string GetNextDialog(int choice = 1)
        {
            int ID = 0;
            if (choice == 1)
            {
                ID = InternalCalls.GetNextDialogueID(InternalCalls.GetCurrentDialogueID());
                //Console.WriteLine("Choice 1 is: " + ID);
            }
            else
            {
                ID = InternalCalls.GetChoice2(InternalCalls.GetCurrentDialogueID());
                //Console.WriteLine("Choice 2 is: " + ID);
            }
            //Console.WriteLine("Resultant line is: " + InternalCalls.GetDialogue(ID));
            return InternalCalls.GetDialogue(ID);
        }

        /* For carrying on the dialog conversation logic. It will automatically zoom in and out, disabling and enabling UI too.
         * player - The chatbox entity of the player
         * notPlayer - The chatbox entity of the entity the player is talking to
         * choice1 - The chatbox entity of the first choice dialog
         * choice2 - The chatbox entity of the second choice dialog
         * scene - The scene of all the chatbox entities (All must be the same scene)
         * dialogFile - Dialog file name
         * return bool - True if dialog is still running. False if dialog has ended.
        */
        public bool RunDialog(string player, string notPlayer, string choice1, string choice2, string scene, string dialogFile)
        {
            if (!starttalking)
            {
                DisableUI();
                // Load Little Girl Talking
                InternalCalls.LoadDialogs(dialogFile);
                InternalCalls.SetCurrentDialogueID(1);

                // Setting default P1, PP1, PP2 positions
                InternalCalls.SetPosX(choice1, scene, 500);
                InternalCalls.SetPosY(choice1, scene, 46);
                InternalCalls.SetPosX(choice2, scene, 500);
                InternalCalls.SetPosY(choice2, scene, -90);
                InternalCalls.SetPosX(player, scene, 450);
                InternalCalls.SetPosY(player, scene, 5);

                // Activate little girl dialogue
                string firstSpeaker;
                if (InternalCalls.IsPlayerSpeaker(1)) firstSpeaker = player;
                else firstSpeaker = notPlayer;

                InternalCalls.EntityActivate(firstSpeaker, scene);
                InternalCalls.UpdateText(firstSpeaker, scene, InternalCalls.GetDialogue(InternalCalls.GetCurrentDialogueID()));

                if (InternalCalls.IsPlayerSpeaker(1)) TextAlignChoices(player, scene, 450, 5, 500, 51, 20, 20);
                else TextAlignChoices(notPlayer, scene, -387, 330, 740, 51, 20, 20);

                camZoomingIn = true;
                starttalking = true;
            }

            // Button click set flags
            if (choiceFlag)
            {
                if (InternalCalls.ButtonReleased(choice1, scene) || InternalCalls.ButtonReleased(choice2, scene)) updateChat = true;
            }
            else if (InternalCalls.ButtonReleased(player, scene) || InternalCalls.ButtonReleased(notPlayer, scene)) updateChat = true;

            // Logic done using those flags
            if (updateChat)
            {
                updateChat = false;

                // Finish dialog
                if (InternalCalls.GetNextDialogueID(InternalCalls.GetCurrentDialogueID()) == 0)
                {
                    DeactivateDialogBox(player, notPlayer, choice1, choice2, scene);
                    starttalking = false;
                    camZoomingOut = true;
                    EnableUI();
                    //Console.WriteLine("finished dialog");
                    return false;
                }

                //Console.WriteLine("Moving on from: " + InternalCalls.GetCurrentDialogueID());
                if (choiceFlag)
                {
                    //Console.WriteLine("It's a choice dialog");
                    choiceFlag = false;
                    if (InternalCalls.ButtonReleased(choice2, scene))
                    {
                        MoveToNextDialog(2);
                        //Console.WriteLine("Choice 2 selected, moving to: " + InternalCalls.GetCurrentDialogueID());
                    }
                    else
                    {
                        MoveToNextDialog(1);
                        //Console.WriteLine("Choice 1 selected, moving to: " + InternalCalls.GetCurrentDialogueID());
                    }
                    InternalCalls.EntityDeactivate(choice1, scene);
                    InternalCalls.EntityDeactivate(choice2, scene);
                }
                MoveToNextDialog(1);
                //Console.WriteLine("Moving to: " + InternalCalls.GetCurrentDialogueID());

                if (InternalCalls.IsPlayerSpeaker(InternalCalls.GetCurrentDialogueID()))
                {
                    InternalCalls.EntityActivate(player, scene);
                    InternalCalls.EntityDeactivate(notPlayer, scene);
                    InternalCalls.UpdateText(player, scene, InternalCalls.GetDialogue(InternalCalls.GetCurrentDialogueID()));
                    TextAlignChoices(player, scene, 450, 5, 500, 51, 20, 20);
                }
                else
                {
                    InternalCalls.EntityActivate(notPlayer, scene);
                    InternalCalls.EntityDeactivate(player, scene);
                    InternalCalls.UpdateText(notPlayer, scene, InternalCalls.GetDialogue(InternalCalls.GetCurrentDialogueID()));
                    TextAlignChoices(notPlayer, scene, -387, 330, 740, 51, 20, 20);
                }

                if (InternalCalls.GetChoice2(InternalCalls.GetCurrentDialogueID()) != 0)
                {
                    //Console.WriteLine("This dialog is a choice dialog: " + InternalCalls.GetCurrentDialogueID());
                    InternalCalls.EntityActivate(choice1, scene);
                    InternalCalls.EntityActivate(choice2, scene);
                    InternalCalls.UpdateText(choice1, scene, GetNextDialog(1));
                    InternalCalls.UpdateText(choice2, scene, GetNextDialog(2));
                    TextAlignChoices(choice1, scene, 500, -25, 500, 51, 40, 25, 1);
                    TextAlignChoices(choice2, scene, 500, -25, 500, 51, 40, 25, 2);
                    choiceFlag = true;
                }
            }
            return true;
        }

        public void DeactivateDialogBox(string player, string notPlayer, string choice1, string choice2, string scene)
        {
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

        #region Player & Enemy Helper Functions
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
                    InitialStatus = 16;
                    break;
                case "Death":
                    InitialStatus = 24;
                    break;
                default:
                    break;
            }
            if (_rotation < 0) _rotation += 2 * (float)Pi;
            if (_rotation >= 15f * MiniAngle || _rotation <= MiniAngle) InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus - 2);
            else if (_rotation <= 3f * MiniAngle) InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus - 3);
            else if (_rotation <= 5f * MiniAngle) InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus - 4);
            else if (_rotation <= 7f * MiniAngle) InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus - 5);
            else if (_rotation <= 9f * MiniAngle) InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus - 6);
            else if (_rotation <= 11f * MiniAngle) InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus - 7);
            else if (_rotation <= 13f * MiniAngle) InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus - 8);
            else InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus - 1);
        }

        public void SetCharRotation4(float _rotation, string _entityName, string _sceneName, string _status) {
            int InitialStatus = 0;
            switch (_status) {
                case "Idle":
                    InitialStatus = 0;
                    break;
                case "Rising":
                    InitialStatus = 4;
                    break;
                case "Attack1":
                    InitialStatus = 8;
                    break;
                case "Attack2":
                    InitialStatus = 12;
                    break;
                default:
                    break;
            }
            //Console.Write(OctopusDirection+"\n");
            //InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus + direction);
            if (0 <= _rotation && _rotation < RightAngle)                   // 1st Quadrant
              InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus + 2);
            else if (RightAngle <= _rotation && _rotation < Pi)           // 2nd Quadrant
              InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus + 1);
            else if (Pi <= _rotation && _rotation < 3f * RightAngle)       // 3rd Quadrant
              InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus);
            else    // 4th Quadrant
              InternalCalls.SetSpriteSheetIndex(_entityName, _sceneName, InitialStatus + 3);
             
        }

        public void ApplyForce(string _entityName, string _sceneName, float _x, float _y, float _multiplier) {
          InternalCalls.ApplyImpulse(_entityName, _sceneName,
              (_x * _multiplier * (float)InternalCalls.GetDeltaTime()),
              (_y * _multiplier * (float)InternalCalls.GetDeltaTime()), 0f, 0f);
        }
        #endregion
      }
}
