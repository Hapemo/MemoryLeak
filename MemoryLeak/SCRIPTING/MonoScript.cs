/*!*****************************************************************************
\file MonoScript.cs
\author Yip Xiu Han, Jazz Teoh Yu Jue, Chen Jia Wen, Kew Yu Jun, Lee Hsien Wei Joachim
\par DP email: xiuhan.yip@\digipen.edu, j.teoh\@digipen.edu, c.jiawen\@digipen.edu, k.yujun\@digipen.edu, l.hsienweijoachim@digipen.edu
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
        //private float perlineScale;
        private const int MaxHealth = 12;
        private const float Epsilon = 1.192092896e-07F;
        private const double Pi = 3.141592653589793238f;
        private const float MiniAngle = (float)Pi / 8;
        private const float RightAngle = (float)Pi / 2;
        private const float RadToDeg = 180/(float)Pi;

        /* Some of these flags are here to optimise the code. Because checking this bool value is faster than button check function calls */
        private bool choiceFlag;            // This flag is true during choice selection dialogs
        //private bool playerTalking;         // This flag is true when player is talking, aka P1 active
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
      //perlineScale = 49.5f;

      choiceFlag = false;            
      //playerTalking = false;         
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
  public void Init(int _id)
      {
            //VI.Dialogue.LoadScript("Dialogue LittleGirl 0");
            InitVariables();
          halfX = VI.Transform.Position.GetX("Water", "Level1");

          halfY = VI.Transform.Position.GetY("Water", "Level1");
          maxX = (VI.Transform.Scale.GetX("Water", "Level1") / 2) + halfX - VI.Transform.Scale.GetX("Enemy", "Level1");
          maxY = (VI.Transform.Scale.GetY("Water", "Level1") / 2) + halfY - VI.Transform.Scale.GetY("Enemy", "Level1");
          minX = halfX - (VI.Transform.Scale.GetX("Water", "Level1") / 2) + VI.Transform.Scale.GetX("Enemy", "Level1");
          minY = halfY - (VI.Transform.Scale.GetY("Water", "Level1") / 2) + VI.Transform.Scale.GetY("Enemy", "Level1");
          CatPosX = VI.Transform.Position.GetX("memoryfragment", "Dialogue");
          CatPosY = VI.Transform.Position.GetY("memoryfragment", "Dialogue");
          dialogueOrder = 0;
          VI.Audio.PlayOnLoop("EnemyTrigger", "Level1");
        }

      public void Update(int _id) {

      // Toggle fps printing box (press 'T')
      if (VI.Input.Key.Press(84)) {
        if (VI.Entity.IsActive("fpsDisplay", "FPS")) VI.Entity.Deactivate("fpsDisplay", "FPS");
        else VI.Entity.Activate("fpsDisplay", "FPS");
      }

          #region Intro Dialogue
          if (VI.Physics.EntitiesCollided("Boat", "IntroBox", "Level1")) {
              if (RunIntroDialog && VI.Entity.IsActive("IntroBox", "Level1")) {
                LockPosition(160, 120);
                RunIntroDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialogue SceneIntro 1");
                if (!RunIntroDialog) {
                  VI.Text.Update("objectivetext", "Dialogue", "Objective: Find the Little Girl");// for the start Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras fermentum est nec rutrum venenatis. Suspendisse facilisis lectus ornare nisi feugiat, sed eleifend nisi molestie. Vestibulum et malesuada tortor. Donec eget diam vel lorem consequat tempus. Maecenas at mollis tellus. Maecenas dolor nisl, scelerisque a eleifend ornare, rhoncus nec leo. Praesent ultricies vehicula placerat. Etiam ligula enim, tempus sed tempor at, congue in ante. Ut condimentum non mauris ac efficitur."); // hint
                }
              }
              if (!RunIntroDialog) TextAlignChoices("objectivetext", "Dialogue", 500, 380, 530, 51.0f, 20, 10);
          }
    #endregion

    //TextAlignChoices("objectivetext", "Dialogue", 400, 1800, 600);

    #region Little Girl Dialogue
    if (VI.Physics.EntitiesCollided("Boat", "LittleGirlBox", "Level1")&& dialogueOrder==0) {
      // I'll be using G1, P1, PP1 and PP2 for the refactored code
      if (VI.Entity.IsActive("LittleGirlBox", "Level1") && RunlittleGirlDialog) {
        LockPosition(-295, -85);
        VI.Animation.SheetIndex.Set("Boat", "Level1", 1);
        RunlittleGirlDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialogue LittleGirl 0");

        if (!RunlittleGirlDialog) {
            
            VI.Entity.Deactivate("LittleGirlBox", "Level1");
            SetObjectiveText();
            dialogueOrder = 1;
        }
      }
    }
            #endregion
            if (dialogueOrder == 1)
            {
                if (VI.Transform.Scale.GetX("Little Girl", "Level1") >0)
                {
                    //VI.Transform.Position.SetY("Little Girl", "Level1", VI.Transform.Position.GetY("Little Girl", "Level1") + 200 * (float)VI.General.DeltaTime());
                    VI.Transform.Scale.SetX("Little Girl", "Level1", VI.Transform.Scale.GetX("Little Girl", "Level1") / (1 + 2.0f * (float)VI.General.DeltaTime()));
                    VI.Transform.Scale.SetY("Little Girl", "Level1", VI.Transform.Scale.GetY("Little Girl", "Level1") / (1 + 2.0f * (float)VI.General.DeltaTime()));
                }
                else
                    VI.Entity.Deactivate("Little Girl", "Level1");

            }
          #region Passenger 1 Dialogue
          if (VI.Physics.EntitiesCollided("Boat", "PassengerBox", "Level1")&&(dialogueOrder==1))
          {
              if (RunPassengerDialog && !VI.Entity.IsActive("LittleGirlBox", "Level1"))
              {
                  LockPosition(-1240, 670);
                  VI.Animation.SheetIndex.Set("Boat", "Level1", 1);
                  RunPassengerDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialogue Passenger 1");

                  if (!RunPassengerDialog)
                  {
                      //SetPosition("Passenger_1", "Level1", -1240, 670);
                      VI.Transform.Rotate.Set("Passenger_1", "Level1", 0.5f);
                      SetObjectiveText();
                      AllowAdvance = true;
                        dialogueOrder = 2;
                  }
              }
          }
          #endregion

          #region Passenger 1 Delivered
          if (AllowAdvance && VI.Physics.EntitiesCollided("Boat", "destination", "Level1"))
          {
              VI.Scene.Play("cutscene1");
              VI.Entity.Deactivate("destination", "Level1");
          }
          #endregion

          #region Memory Fragment UI

          if (VI.Physics.EntitiesCollided("Boat", "fragment1drop", "Level1")&& fragment1==0)
          {
              Console.Write("COLLECTED");
              fragment1 = 1;
              VI.Text.Update("memoryfragmentscreen", "Dialogue", "Memory Fragments (1/1)");
              //InternalCalls.SetLayer("fragment1drop", "Level1", 100);///////////////////////////////////////////    need set layer higher
              VI.Audio.Play("fragment1drop", "Level1");
              //VI.Entity.Deactivate("fragment1drop", "Level1");
          }

          if (fragment1 == 1)//cat rising up
          {

              if (VI.Transform.Position.GetY("fragment1drop", "Level1") >  VI.Transform.Scale.GetY("Boat", "Level1")/2 + VI.Transform.Position.GetY("Boat", "Level1"))
                  fragment1 = 2;
              else
              { 
                  VI.Transform.Position.SetY("fragment1drop", "Level1", VI.Transform.Position.GetY("fragment1drop", "Level1") + 200 *(float)VI.General.DeltaTime());
                  VI.Transform.Scale.SetX("fragment1drop", "Level1", VI.Transform.Scale.GetX("fragment1drop", "Level1") + 100.0f * (float)VI.General.DeltaTime());
                  VI.Transform.Scale.SetY("fragment1drop", "Level1", VI.Transform.Scale.GetY("fragment1drop", "Level1") + 100.0f * (float)VI.General.DeltaTime());
              }
          }
          else if (fragment1 == 2)//make cat fly to memoryfragment
          {
              float uiPosX = VI.Transform.Position.GetX("memoryfragment", "Dialogue") + VI.Camera.GetPos.X();
              float uiPosY = VI.Transform.Position.GetY("memoryfragment", "Dialogue") + VI.Camera.GetPos.Y();

              CatSpeedX = (uiPosX - VI.Transform.Position.GetX("fragment1drop", "Level1")) / CatFlyTime;
              CatSpeedY = (uiPosY - VI.Transform.Position.GetY("fragment1drop", "Level1")) / CatFlyTime;

              CatFlyTime -= (float)VI.General.DeltaTime();

              VI.Transform.Position.SetX("fragment1drop", "Level1", VI.Transform.Position.GetX("fragment1drop", "Level1") + CatSpeedX * (float)VI.General.DeltaTime());
              VI.Transform.Position.SetY("fragment1drop", "Level1", VI.Transform.Position.GetY("fragment1drop", "Level1") + CatSpeedY * (float)VI.General.DeltaTime());
              VI.Transform.Scale.SetX("fragment1drop", "Level1", VI.Transform.Scale.GetX("fragment1drop", "Level1") - 100.0f * (float)VI.General.DeltaTime());
              VI.Transform.Scale.SetY("fragment1drop", "Level1", VI.Transform.Scale.GetY("fragment1drop", "Level1") - 100.0f * (float)VI.General.DeltaTime());
              VI.Transform.Rotate.Set("fragment1drop", "Level1", VI.Transform.Rotate.Get("fragment1drop", "Level1") + 10.0f * (float)VI.General.DeltaTime());
              if (CatFlyTime < 0)
              {
                  VI.Entity.Deactivate("fragment1drop", "Level1");
                  fragment1 = 4;
                  oriFragScaleX = VI.Transform.Scale.GetX("memoryfragment", "Dialogue");
              }
          }
          else if (fragment1 == 4)
          {
              if (VI.Transform.Scale.GetX("memoryfragment", "Dialogue") < oriFragScaleX+30)
              { 
                  VI.Transform.Scale.SetX("memoryfragment", "Dialogue", VI.Transform.Scale.GetX("memoryfragment", "Dialogue") + 100 * (float)VI.General.DeltaTime());
                  VI.Transform.Scale.SetY("memoryfragment", "Dialogue", VI.Transform.Scale.GetY("memoryfragment", "Dialogue") + 100 * (float)VI.General.DeltaTime());
              }
              else
                  fragment1 = 5;

          }
          else if (fragment1 == 5)
          {
              if (VI.Transform.Scale.GetX("memoryfragment", "Dialogue") > oriFragScaleX)
              {
                  VI.Transform.Scale.SetX("memoryfragment", "Dialogue", VI.Transform.Scale.GetX("memoryfragment", "Dialogue") - 100 * (float)VI.General.DeltaTime());
                  VI.Transform.Scale.SetY("memoryfragment", "Dialogue", VI.Transform.Scale.GetY("memoryfragment", "Dialogue") - 100 * (float)VI.General.DeltaTime());
              }
              else
                  fragment1 = 6;

          }
          if ((VI.Input.Button.Released("memoryfragment", "Dialogue")) == true) {
              if (VI.Entity.IsActive("memoryfragmentscreen", "Dialogue") == false) {
                  VI.Entity.Activate("memoryfragmentscreen", "Dialogue");
                  if (fragment1 != 0) { VI.Entity.Activate("fragment1obj", "Dialogue"); }
              } else {
                  VI.Entity.Deactivate("memoryfragmentscreen", "Dialogue");
                  if (fragment1 != 0) { VI.Entity.Deactivate("fragment1obj", "Dialogue"); }
              }
          }
          #endregion

          #region Objective UI
          if ((VI.Input.Button.Released("objectivetext", "Dialogue") && currentobjective != "") == true)
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
                  VI.Text.Update("objectivetext", "Dialogue", "Objective: " + currentobjective); // hint
                  TextAlignChoices("objectivetext", "Dialogue", 500, 380, 530, 51.0f, 20, 10);

      }

      if (!objectiveexpanded)
              {
                  VI.Text.Update("objectivetext", "Dialogue", "Objective: Click to view"); // hint
                  TextAlignChoices("objectivetext", "Dialogue", 500, 380, 530, 51.0f, 20, 10);

      }
    }
          #endregion

          #region Player
          float PlayerPosX = VI.Transform.Position.GetX("Boat", "Level1");
          float PlayerPosY = VI.Transform.Position.GetY("Boat", "Level1");
          float PlayerScaleX = VI.Transform.Scale.GetX("Boat", "Level1");
          float PlayerScaleY = VI.Transform.Scale.GetY("Boat", "Level1");
          if (!starttalking && VI.Input.Key.Hold(349) && VI.Entity.IsActive("DialogueText", "Level1") == false) { // Mouse click
              float DirX = VI.Input.Mouse.WorldPosX() + VI.Camera.GetPos.X() - PlayerPosX;
              float DirY = VI.Input.Mouse.WorldPosY() + VI.Camera.GetPos.Y() - PlayerPosY;
              float NormX = 0f, NormY = 0f;
              if (VI.Math.SqMagnitude(DirX, DirY) > Epsilon * Epsilon) {
                  NormX = VI.Math.Normalize.X(DirX, DirY);
                  NormY = VI.Math.Normalize.Y(DirX, DirY);
                  ApplyForce("Boat", "Level1", NormX, NormY, PlayerSpeed);
              }
              PlayerRotation = GetRotation(NormX, NormY);
              SetCharRotation(PlayerRotation, "Boat", "Level1", "Idle");
              VI.Audio.Play("Boat", "Level1");
            }
            if (!VI.Input.Key.Hold(349))
            {
                VI.Audio.Stop("Boat", "Level1");
            }
            #endregion

            #region Camera Update
            UpdateCamera();
          #endregion

          #region Enemy
          //VI.Camera.SetScale.X(5500);
          float EnemyChangeInX = 0;
          float EnemyChangeInY = 0;
          Random rand = new Random();
          float EnemyPosX = VI.Transform.Position.GetX("Enemy", "Level1");
          float EnemyPosY = VI.Transform.Position.GetY("Enemy", "Level1");
          float EnemyScaleX = VI.Transform.Scale.GetX("Enemy", "Level1");
          float EnemyScaleY = VI.Transform.Scale.GetY("Enemy", "Level1");
          float EnemyDisX = PlayerPosX - EnemyPosX;
          float EnemyDisY = PlayerPosY - EnemyPosY;
          float EnemyNormDisX = 0f, EnemyNormDisY = 0f;
          if (VI.Math.SqMagnitude(EnemyDisX, EnemyDisY) > Epsilon * Epsilon) {
              EnemyNormDisX = VI.Math.Normalize.X(EnemyDisX, EnemyDisY);
              EnemyNormDisY = VI.Math.Normalize.Y(EnemyDisX, EnemyDisY);
          }

          // Enemy is in screen
          if (EnemyPosX <= VI.Camera.GetPos.X() + (VI.Camera.GetScale.X() / 2) &&
              EnemyPosY <= VI.Camera.GetPos.Y() + (VI.Camera.GetScale.Y() / 2) &&
              EnemyPosX >= VI.Camera.GetPos.X() - (VI.Camera.GetScale.X() / 2) &&
              EnemyPosY >= VI.Camera.GetPos.Y() - (VI.Camera.GetScale.Y() / 2)) {
                //float EnemyRotation = GetRotation(EnemyNormDisX, EnemyNormDisY);
                /*
                if (EnemyRotation < 0) OctopusDirection = 1;
                else OctopusDirection = (int)(VI.Math.Negate(EnemyRotation) / Pi);
                */
                //Console.Write(OctopusDirection + "\n");
                //Console.Write((EnemyRotation / Pi / 2) + "\n");
                OctopusDirection = GetRotation(EnemyNormDisX, EnemyNormDisY);
                //OctopusDirection = (int)(VI.Math.Negate(EnemyRotation));
                //Console.Write(OctopusDirection + "\n");

                // Chasing player
                if (!starttalking && VI.Math.Negate(EnemyDisX) <= VI.Transform.Scale.GetX("EnemyTrigger", "Level1") && VI.Math.Negate(EnemyDisY) <= VI.Transform.Scale.GetY("EnemyTrigger", "Level1")) {
                    EnemyLoiter = false;
                    //if (VI.Math.SqMagnitude(EnemyDisX, EnemyDisY) > Epsilon * Epsilon) {
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
                if (!starttalking && VI.Physics.EntitiesCollided("Boat", "EnemyTrigger", "Level1")) {
                    switch (OctopusAttacked) {
                        case 0:
                            OctopusAttacked = 1;
                            //VI.Audio.PlayOnLoop("EnemyTrigger", "Level1");
                            SetCharRotation4(OctopusDirection, "Enemy", "Level1", "Rising");
                            VI.Animation.FrameCount.Set("Enemy", "Level1", 0);
                            HitInterval = VI.Animation.Speed.Get("Enemy", "Level1") * VI.Animation.FrameCount.Get("Enemy", "Level1");
                            HealInterval = HitInterval * 3.0f;
                            break;
                        case 1:
                            if (VI.Animation.CurrentFrame.Get("Enemy", "Level1") == VI.Animation.FrameCount.Get("Enemy", "Level1") - 1) {
                                SetCharRotation4(OctopusDirection, "Enemy", "Level1", "Attack1");
                                VI.Animation.FrameCount.Set("Enemy", "Level1", 0);
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
                    //VI.Audio.Stop("EnemyTrigger", "Level1");
                    SetCharRotation4(OctopusDirection, "Enemy", "Level1", "Idle");
                }

                if (VI.Physics.CheckCollision("Boat", "Enemy", "Level1", true) && HitTaken > -1)
                {
                    //Console.Write("HitCounter!\n");
                    HitCounter += (float)VI.General.DeltaTime();
                    if (HitCounter >= HitInterval)
                    {
                        //Console.Write("Attacking!\n");
                        HitCounter = 0;
                        ++HitTaken;
                        VI.Audio.Play("Enemy", "Level1");
                        VI.Texture.Set("hpbar", "Dialogue", "Textures\\Icons\\healthbar-" + (HitTaken + 1) + ".png");
                    }
                    SetCharRotation(PlayerRotation, "Boat", "Level1", "Hit");

                    EnemyChangeInX = 0;
                    EnemyChangeInY = 0;
                }
                else if (HitTaken > -1)
                {
                    SetCharRotation(PlayerRotation, "Boat", "Level1", "Idle");
                }
                else if (HitTaken <0)
                {
                    SetCharRotation(PlayerRotation, "Boat", "Level1", "Death");
                }

                // Player dies
                if(HitTaken == MaxHealth) {
                    SetCharRotation(PlayerRotation, "Boat", "Level1", "Death");
                    VI.Animation.FrameCount.Set("Boat", "Level1", 0);
                    HitTaken = -1;
                }
                if (HitTaken == -1 && VI.Animation.CurrentFrame.Get("Boat", "Level1") == VI.Animation.FrameCount.Get("Boat", "Level1") - 1) {
                    VI.Audio.Stop("EnemyTrigger", "Level1");
                    VI.Scene.Pause("Level1");
                    VI.Scene.Play("Game Over");
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
            EnemyChangeInX *= (float)VI.General.DeltaTime();
            EnemyChangeInY *= (float)VI.General.DeltaTime();
            EnemyChangeInX = (((EnemyPosX + EnemyChangeInX) < maxX) && ((EnemyPosX + EnemyChangeInX) > minX)) ? EnemyChangeInX : 0;
            EnemyChangeInY = (((EnemyPosY + EnemyChangeInY) < maxY) && ((EnemyPosY + EnemyChangeInY) > minY)) ? EnemyChangeInY : 0;
            VI.Transform.Position.SetX("EnemyTrigger", "Level1", EnemyPosX + EnemyChangeInX);
            VI.Transform.Position.SetY("EnemyTrigger", "Level1", EnemyPosY + EnemyChangeInY);
            VI.Transform.Position.SetX("Enemy", "Level1", EnemyPosX + EnemyChangeInX);
            VI.Transform.Position.SetY("Enemy", "Level1", EnemyPosY + EnemyChangeInY);

            // Healing player
            if (!VI.Physics.EntitiesCollided("Boat", "Enemy", "Level1") && HitTaken > 0) {
                HealCounter += (float)VI.General.DeltaTime();
                if (HealCounter >= HealInterval) {
                    //Console.Write("Regenerating!\n");
                    SetCharRotation(PlayerRotation, "Boat", "Level1", "Idle");
                    HealCounter = 0;
                    --HitTaken;
                    VI.Texture.Set("hpbar", "Dialogue", "Textures\\Icons\\healthbar-" + (HitTaken + 1) + ".png");
                }
            }
            #endregion

            #region cutscene1
            //if (InternalCalls.GetCurrentGameStateName() == "cutscene1state")
            {
                if ((VI.Input.Button.Released("cutscene1button", "cutscene1")) == true)
                {
                    VI.Scene.Pause("cutscene1");
                }
            }
            #endregion
        }

        #region UI, Camera, Text Align, Objective Functions
        public void SetObjectiveText()
        {
            currentobjective = VI.Dialogue.GetLine(VI.Dialogue.Current.GetId());
            VI.Text.Update("objectivetext", "Dialogue", "Objective: " + currentobjective); // hint
            TextAlignChoices("objectivetext", "Dialogue", 500, 380, 700, 51.0f, 20, 10);
            if (VI.Text.GetLineCount("objectivetext", "Dialogue") > 2)
            {
                VI.Text.Update("objectivetext", "Dialogue", "Objective: Click to view");
                TextAlignChoices("objectivetext", "Dialogue", 500, 380, 530, 51.0f, 20, 10);
            }
        }

        public void DisableUI() {
            VI.Entity.Deactivate("hpbar", "Dialogue");
            VI.Entity.Deactivate("memoryfragment", "Dialogue");
            VI.Entity.Deactivate("memoryfragmentscreen", "Dialogue");
            VI.Entity.Deactivate("fragment1obj", "Dialogue");

            VI.Entity.Deactivate("cyclemap", "Dialogue");

            VI.Entity.Deactivate("minimap", "Dialogue");
            VI.Entity.Deactivate("enemymap", "Dialogue");
            VI.Entity.Deactivate("weathermap", "Dialogue");

            //VI.Entity.Deactivate("minimapbig", "Dialogue");
            //VI.Entity.Deactivate("enemymapbig", "Dialogue");
            //VI.Entity.Deactivate("weathermapbig", "Dialogue");

            VI.Entity.Deactivate("weathertext", "Dialogue");
            VI.Entity.Deactivate("objectivetext", "Dialogue");
        }

        public void EnableUI() {
            VI.Entity.Activate("hpbar", "Dialogue");
            VI.Entity.Activate("memoryfragment", "Dialogue");

            VI.Entity.Activate("cyclemap", "Dialogue");

            //VI.Entity.Activate("minimap", "Dialogue");

            //VI.Entity.Activate("weathertext", "Dialogue");
            VI.Entity.Activate("objectivetext", "Dialogue");
        }

        public void UpdateCamera()
        {
            if (camZoomingIn)
            {
                camScaleX -= 500 * (float)VI.General.DeltaTime();
                VI.Camera.SetScale.X(camScaleX);
                if (camScaleX < 700)
                {
                    camScaleX = 700;
                    VI.Camera.SetScale.X(700);
                    camZoomingIn = false;
                }
            }
            if (camZoomingOut)
            {
                camScaleX += 500 * (float)VI.General.DeltaTime();
                VI.Camera.SetScale.X(camScaleX);
                if (camScaleX > 1600)
                {
                    camScaleX = 1600;
                    VI.Camera.SetScale.X(1600);
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
            int additionalLines = VI.Text.GetLineCount(entityname, scenename) - 1;
            //Console.WriteLine("lines: " + additionalLines);
            //float scaleY = perLineScaleY;         // This is the default height of button, will changing with respect to line count
            perLineScaleY *= VI.Text.Scale.Get(entityname, scenename);

            VI.Transform.Scale.SetX(entityname, scenename, scaleX);
            VI.Transform.Scale.SetY(entityname, scenename, perLineScaleY * (1+additionalLines) + textYSpacing*2);
            
            // If it's a choice textbox, posY is the middle of both texts
            if (choice == 1) posY = posY + spacing + perLineScaleY * (additionalLines+1);
            else if (choice == 2) posY = posY - spacing - perLineScaleY * (additionalLines+1);

            float finalPosY = posY - (perLineScaleY * additionalLines) / 2;

            VI.Transform.Position.SetX(entityname, scenename, posX);
            VI.Transform.Position.SetY(entityname, scenename, finalPosY);

            float textY = perLineScaleY * additionalLines / 2 - perLineScaleY/2;
            float magicNumber = 10.0f * VI.Text.Scale.Get(entityname, scenename);
            VI.Text.Offset.Set(entityname, scenename, -scaleX / 2 + textXSpacing, textY + magicNumber);
        }

        #endregion

        #region Dialogue helper functions
        // Based on the current dialog ID, move to the next one. Can input choice if there is a choice selection, by default it's 1
        public void MoveToNextDialog(int choice = 1)
        {
            if (choice == 1) VI.Dialogue.Current.SetTo(VI.Dialogue.Next.GetId2(VI.Dialogue.Current.GetId()));
            else VI.Dialogue.Current.SetTo(VI.Dialogue.Choice.Second(VI.Dialogue.Current.GetId()));
        }

        // Get the texts of the next dialog, able to input 1 or 2 to get the different choices
        public string GetNextDialog(int choice = 1)
        {
            int ID = 0;
            if (choice == 1)
            {
                ID = VI.Dialogue.Next.GetId2(VI.Dialogue.Current.GetId());
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
                VI.Dialogue.LoadScript(dialogFile);
                VI.Dialogue.Current.SetTo(1);

                // Setting default P1, PP1, PP2 positions
                VI.Transform.Position.SetX(choice1, scene, 500);
                VI.Transform.Position.SetY(choice1, scene, 46);
                VI.Transform.Position.SetX(choice2, scene, 500);
                VI.Transform.Position.SetY(choice2, scene, -90);
                VI.Transform.Position.SetX(player, scene, 450);
                VI.Transform.Position.SetY(player, scene, 5);

                // Activate little girl dialogue
                string firstSpeaker;
                if (VI.Dialogue.Speaker.IsPlayer(1)) firstSpeaker = player;
                else firstSpeaker = notPlayer;

                VI.Entity.Activate(firstSpeaker, scene);
                VI.Text.Update(firstSpeaker, scene, VI.Dialogue.GetLine(VI.Dialogue.Current.GetId()));

                if (VI.Dialogue.Speaker.IsPlayer(1)) TextAlignChoices(player, scene, 450, 5, 500, 51, 20, 20);
                else TextAlignChoices(notPlayer, scene, -387, 330, 740, 51, 20, 20);

                camZoomingIn = true;
                starttalking = true;
            }

            // Button click set flags
            if (choiceFlag)
            {
                if (VI.Input.Button.Released(choice1, scene) || VI.Input.Button.Released(choice2, scene)) updateChat = true;
            }
            else if (VI.Input.Button.Released(player, scene) || VI.Input.Button.Released(notPlayer, scene)) updateChat = true;

            // Logic done using those flags
            if (updateChat)
            {
                updateChat = false;

                // Finish dialog
                if (VI.Dialogue.Next.GetId2(VI.Dialogue.Current.GetId()) == 0)
                {
                    DeactivateDialogBox(player, notPlayer, choice1, choice2, scene);
                    starttalking = false;
                    camZoomingOut = true;
                    EnableUI();
                    //Console.WriteLine("finished dialog");
                    return false;
                }

                //Console.WriteLine("Moving on from: " + VI.Dialogue.Current.GetId());
                if (choiceFlag)
                {
                    //Console.WriteLine("It's a choice dialog");
                    choiceFlag = false;
                    if (VI.Input.Button.Released(choice2, scene))
                    {
                        MoveToNextDialog(2);
                        //Console.WriteLine("Choice 2 selected, moving to: " + VI.Dialogue.Current.GetId());
                    }
                    else
                    {
                        MoveToNextDialog(1);
                        //Console.WriteLine("Choice 1 selected, moving to: " + VI.Dialogue.Current.GetId());
                    }
                    VI.Entity.Deactivate(choice1, scene);
                    VI.Entity.Deactivate(choice2, scene);
                }
                MoveToNextDialog(1);
                //Console.WriteLine("Moving to: " + VI.Dialogue.Current.GetId());

                if (VI.Dialogue.Speaker.IsPlayer(VI.Dialogue.Current.GetId()))
                {
                    VI.Entity.Activate(player, scene);
                    VI.Entity.Deactivate(notPlayer, scene);
                    VI.Text.Update(player, scene, VI.Dialogue.GetLine(VI.Dialogue.Current.GetId()));
                    TextAlignChoices(player, scene, 450, 5, 500, 51, 20, 20);
                }
                else
                {
                    VI.Entity.Activate(notPlayer, scene);
                    VI.Entity.Deactivate(player, scene);
                    VI.Text.Update(notPlayer, scene, VI.Dialogue.GetLine(VI.Dialogue.Current.GetId()));
                    TextAlignChoices(notPlayer, scene, -387, 330, 740, 51, 20, 20);
                }

                if (VI.Dialogue.Choice.Second(VI.Dialogue.Current.GetId()) != 0)
                {
                    //Console.WriteLine("This dialog is a choice dialog: " + VI.Dialogue.Current.GetId());
                    VI.Entity.Activate(choice1, scene);
                    VI.Entity.Activate(choice2, scene);
                    VI.Text.Update(choice1, scene, GetNextDialog(1));
                    VI.Text.Update(choice2, scene, GetNextDialog(2));
                    TextAlignChoices(choice1, scene, 500, -25, 500, 51, 40, 25, 1);
                    TextAlignChoices(choice2, scene, 500, -25, 500, 51, 40, 25, 2);
                    choiceFlag = true;
                }
            }
            return true;
        }

        public void DeactivateDialogBox(string player, string notPlayer, string choice1, string choice2, string scene)
        {
            VI.Entity.Deactivate(player, scene);
            VI.Entity.Deactivate(notPlayer, scene);
            VI.Entity.Deactivate(choice1, scene);
            VI.Entity.Deactivate(choice2, scene);
        }
        #endregion

        public void LockPosition(float x, float y) {
          VI.Transform.Position.SetX("Boat", "Level1", x);
          VI.Transform.Position.SetY("Boat", "Level1", y);
        }

        public void SetPosition(string entityname, string scenename, float x, float y) {
            VI.Transform.Position.SetX(entityname, scenename, x);
            VI.Transform.Position.SetY(entityname, scenename, y);
        }

        #region Player & Enemy Helper Functions
        public int CheckRegion(string _entityName, string _sceneName)
        {
            if (VI.Transform.Position.GetX(_entityName, _sceneName) > maxX || VI.Transform.Position.GetY(_entityName, _sceneName) > maxY ||
                VI.Transform.Position.GetX(_entityName, _sceneName) < minX || VI.Transform.Position.GetY(_entityName, _sceneName) < minY) return 0;
            if (VI.Transform.Position.GetX(_entityName, _sceneName) > halfX && VI.Transform.Position.GetY(_entityName, _sceneName) > halfY) return 1;
            if (VI.Transform.Position.GetX(_entityName, _sceneName) > halfX && VI.Transform.Position.GetY(_entityName, _sceneName) < halfY) return 2;
            if (VI.Transform.Position.GetX(_entityName, _sceneName) < halfX && VI.Transform.Position.GetY(_entityName, _sceneName) < halfY) return 3;
            if (VI.Transform.Position.GetX(_entityName, _sceneName) < halfX && VI.Transform.Position.GetY(_entityName, _sceneName) > halfY) return 4;
            //Console.Write("Out of bounds!\n");
            return -1;
        }

        public float GetRotation(float _x, float _y) {
            float Rotation = 0;
            if (_y != 0f && _x >= 0f)
                Rotation = VI.Math.ArcTangent(_y, _x);
            else if (_y == 0f && _x > 0f)
                Rotation = (float)Pi / 2;
            else if (_y != 0f && _x < 0f) {
                Rotation = VI.Math.ArcTangent(_y, _x);
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
                    Console.WriteLine("DIEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n\n");
                    break;
                default:
                    break;
            }
            if (_rotation < 0) _rotation += 2 * (float)Pi;
            if (_rotation >= 15f * MiniAngle || _rotation <= MiniAngle) VI.Animation.SheetIndex.Set(_entityName, _sceneName, InitialStatus - 2);
            else if (_rotation <= 3f * MiniAngle) VI.Animation.SheetIndex.Set(_entityName, _sceneName, InitialStatus - 3);
            else if (_rotation <= 5f * MiniAngle) VI.Animation.SheetIndex.Set(_entityName, _sceneName, InitialStatus - 4);
            else if (_rotation <= 7f * MiniAngle) VI.Animation.SheetIndex.Set(_entityName, _sceneName, InitialStatus - 5);
            else if (_rotation <= 9f * MiniAngle) VI.Animation.SheetIndex.Set(_entityName, _sceneName, InitialStatus - 6);
            else if (_rotation <= 11f * MiniAngle) VI.Animation.SheetIndex.Set(_entityName, _sceneName, InitialStatus - 7);
            else if (_rotation <= 13f * MiniAngle) VI.Animation.SheetIndex.Set(_entityName, _sceneName, InitialStatus - 8);
            else VI.Animation.SheetIndex.Set(_entityName, _sceneName, InitialStatus - 1);
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
            //VI.Animation.SpriteSheet.Index.Set(_entityName, _sceneName, InitialStatus + direction);
            if (0 <= _rotation && _rotation < RightAngle)                   // 1st Quadrant
              VI.Animation.SheetIndex.Set(_entityName, _sceneName, InitialStatus + 2);
            else if (RightAngle <= _rotation && _rotation < Pi)           // 2nd Quadrant
              VI.Animation.SheetIndex.Set(_entityName, _sceneName, InitialStatus + 1);
            else if (Pi <= _rotation && _rotation < 3f * RightAngle)       // 3rd Quadrant
              VI.Animation.SheetIndex.Set(_entityName, _sceneName, InitialStatus);
            else    // 4th Quadrant
              VI.Animation.SheetIndex.Set(_entityName, _sceneName, InitialStatus + 3);
             
        }

        public void ApplyForce(string _entityName, string _sceneName, float _x, float _y, float _multiplier) {
          VI.Physics.ApplyImpulse(_entityName, _sceneName,
              (_x * _multiplier * (float)VI.General.DeltaTime()),
              (_y * _multiplier * (float)VI.General.DeltaTime()), 0f, 0f);
        }
        #endregion
      }
}
