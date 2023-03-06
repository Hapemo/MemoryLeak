using System;
using System.Dynamic;
using System.Runtime.CompilerServices;
using VI;

// INFO
// Intro Dialog zoom is x = 1200
// Static Dialog zoom is x = 960
// Normal zoom is x = 1600

namespace BonVoyage {
  public class Level1DialogManager : BaseScript {
    private const float textHeight = 50.0f;
    private const float dialogBoxWidth = 549.0f;
    private const float choiceWidth = 564.6f;
    private const float smallDialogBoxHeight = 109.8f;
    private const float midDialogBoxHeight = 178.8f;
    private const float bigDialogBoxHeight = 228.6f;
    private const float smallChoiceHeight = 61.8f;
    private const float midChoiceHeight = 87.6f;

    static public int passengerDialogProgress = 0; // Consists of 2 numbers in this format <passenger number><right or wrong>. 1 for right, 0 for wrong. eg passenger 1 right answer destination reached, it will be 11.
    private bool progressUpdate = false;
    static public bool runIntroDialog;
    //static public bool runGirlDialog;

    private int correctDestination_RenderLocation;
    private int wrongDestination_RenderLocation;

    static public bool runPassengerDialog;
    private int P1ColliderBox;
    
    static public bool runPassenger2Dialog;
    private int P2ColliderBox;

    private bool choiceFlag;            // This flag is true during choice selection dialogs
    private bool updateChat;            // This flag is true when dialog changes for anyone
    private bool dialogInit;            // THis flag is true when entering a dialog for the first line
    private bool normalZoom = true;
    private int latestChoiceChosen = 0; // 0 if no choice chosen, 1 if choice 1 chosen, 2 if choice 2 chosen. Resets every frame

    private int playerID;

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

    private int P1ID;
    private int PP1ID;
    private int PP2ID;
    private int G1ID;


    public void Alive(int _ENTITY) {
      THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
    }

    public void Init(int _ENTITY) {
      playerID = VI.Entity.GetId("Boat", VI.GameState.GetName());

      UIHPBarID = VI.Entity.GetId("hpbar", "Dialogue");
      UIMemoryFragmentID = VI.Entity.GetId("memoryfragment", "Dialogue");
      UIMemoryFragmentScreenID = VI.Entity.GetId("memoryfragmentscreen", "Dialogue");
      UIFragment1ObjID = VI.Entity.GetId("fragment1obj", "Dialogue");
      UICycleMapID = VI.Entity.GetId("toggleMap", "CrystalBalls");
      UIMiniMapID = VI.Entity.GetId("minimap", "Dialogue");
      UIEnemyMapID = VI.Entity.GetId("enemymap", "Dialogue");
      UIWeatherMapID = VI.Entity.GetId("weathermap", "Dialogue");
      UIWeatherTextID = VI.Entity.GetId("weathertext", "Dialogue");
      UIObjectiveTextID = VI.Entity.GetId("objectivetext", "Dialogue");

      P1ID = VI.Entity.GetId("P1", "Dialogue");
      PP1ID = VI.Entity.GetId("PP1", "Dialogue");
      PP2ID = VI.Entity.GetId("PP2", "Dialogue");
      G1ID = VI.Entity.GetId("G1", "Dialogue");

      P1ColliderBox = VI.Entity.GetId("Passenger1Box", "Level1");
      P2ColliderBox = VI.Entity.GetId("Passenger2Box", "Level1");

      dialogInit = true;

      VI.Entity.s_Deactivate("Passenger2");
      VI.Entity.Deactivate(P2ColliderBox);
    }

    public void EarlyUpdate(int _ENTITY) {

    }

    public void Update(int _ENTITY) {

      if (!normalZoom)
        normalZoom = Level1ManagerScript.ChangeZoom(1600, 300);

      // Dialog control

      if (runIntroDialog) {
        PlayerScript.PlayerInDialogue = true;
        runIntroDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialogue SceneIntro 1");
        if (!runIntroDialog)
          EndIntroDialog();
      }

      //if (runGirlDialog) {
      //  //VI.Animation.SheetIndex.Set(playerID, 1);
      //  runGirlDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialogue LittleGirl 0");
        
      //  if (!runGirlDialog)
      //    EndGirlDialog();
      //}

      if (runPassengerDialog) {
        GeneralDialogStart(1);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(P1ColliderBox), 
                                                 VI.Transform.Position.GetY(P1ColliderBox)); // Move him to better location
        runPassengerDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialogue Passenger 1"); // Run the dialog
        if (!runPassengerDialog)
          EndPassengerDialog();
      }

      if (runPassenger2Dialog) {
        GeneralDialogStart(1);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(P2ColliderBox), 
                                                 VI.Transform.Position.GetY(P2ColliderBox));
        runPassenger2Dialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialogue Passenger 2");
        if (!runPassenger2Dialog)
          EndPassenger2Dialog();
      }

      bool dialogEnded = false;
      switch (passengerDialogProgress) {
      case 10: // Passenger 1 wrong
        GeneralDialogStart(7);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(wrongDestination_RenderLocation),
                                                 VI.Transform.Position.GetY(wrongDestination_RenderLocation));
        if (!VI.Entity.IsActive(P2ColliderBox)) {
          VI.Entity.Activate(VI.Entity.GetId("Passenger2"));
          VI.Entity.Activate(P2ColliderBox);
        }
        dialogEnded = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialog Minerva (Lighthouse)");
        if (!dialogEnded) EndDropoffDialog();
        break;
      case 11: // Passenger 1 correct
        GeneralDialogStart(5);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(correctDestination_RenderLocation),
                                                 VI.Transform.Position.GetY(correctDestination_RenderLocation));
        if (!VI.Entity.IsActive(P2ColliderBox)) {
          VI.Entity.Activate(VI.Entity.GetId("Passenger2"));
          VI.Entity.Activate(P2ColliderBox);
        }
        dialogEnded = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialog Minerva (Multistory House)");
        if (!dialogEnded) EndDropoffDialog();
        break;
      case 20: // Passenger 2 wrong
        GeneralDialogStart(1);
        MoveCameraLeftToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(wrongDestination_RenderLocation),
                                                 VI.Transform.Position.GetY(wrongDestination_RenderLocation));
        dialogEnded = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialog Argus (Brown House)");
        if (!dialogEnded) EndDropoffDialog();
        break;
      case 21: // Passenger 2 correct
        GeneralDialogStart(7);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(correctDestination_RenderLocation),
                                                 VI.Transform.Position.GetY(correctDestination_RenderLocation));
        dialogEnded = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialog Argus (Water Fountain)");
        if (!dialogEnded) EndDropoffDialog();
        break;
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


    #region UIControl
    public void DisableUI() {
      VI.Entity.Deactivate(UIHPBarID);
      VI.Entity.Deactivate(UIMemoryFragmentID);
      VI.Entity.Deactivate(UIMemoryFragmentScreenID);
      VI.Entity.Deactivate(UIFragment1ObjID);
      VI.Entity.Deactivate(UICycleMapID);
      //VI.Entity.Deactivate(UIMiniMapID);
      //VI.Entity.Deactivate(UIEnemyMapID);
      //VI.Entity.Deactivate(UIWeatherMapID);
      VI.Entity.Deactivate(UIWeatherTextID);
      VI.Entity.Deactivate(UIObjectiveTextID);

      //VI.Scene.Pause("CrystalBalls");
      //VI.Scene.Pause("MiniMap");
      //VI.Scene.Pause("EnemyMap");
      //VI.Scene.Pause("WeatherMap");
    }

    public void EnableUI() {
      VI.Entity.Activate(UIHPBarID);
      VI.Entity.Activate(UIMemoryFragmentID);
      VI.Entity.Activate(UICycleMapID);
      VI.Entity.Activate(UIObjectiveTextID);
            VI.Entity.Activate(UICycleMapID);
            //VI.Scene.Play("CrystalBalls");
      //VI.Scene.Play("MiniMap");
      //VI.Scene.Play("EnemyMap");
      //VI.Scene.Play("WeatherMap");
    }
    #endregion

    // All the functions on the top of DialogHelper region are helper functions to assist RunDialog() at the bottom of the region
    #region DialogHelper
    // int scaleX           - This is the default width of button
    // int posX             - This is the center X coordinate of button (500)
    // int posY             - This is the center Y coordinate of button. If it's choice, it's the middle of both buttons (-25)
    // int spaceing         - Spacing between choice button edge from middle, useless for single button.
    // int perLineScaleY    - This is the increment for one additional line
    // int textXSpacing     - This is the spacing of the text from the left edge of the box 
    // int textYSpacing     - This is the spacing of the text from the top edge of the box 
    public void TextBoxAlign(string entityname, string scenename, float posX, float posY, float textXSpacing = 50, float textYSpacing = 50, int choice = 0, float spacing = 15) {
      int additionalLines = VI.Text.s_GetLineCount(entityname, scenename) - 1;

      // Selecting the dialog box texture and putting it into correct position
      if (choice == 0) {
        if (additionalLines < 2) {
          VI.Transform.Scale.s_SetY(entityname, scenename, smallDialogBoxHeight);
          VI.Transform.Scale.s_SetX(entityname, scenename, dialogBoxWidth);
          VI.Texture.s_Set(entityname, scenename, "Textures\\Icons\\dialogue\\UI_DialogueBox1.png");
        } else if (additionalLines < 4) {
          posY += (midDialogBoxHeight - smallDialogBoxHeight) / 2;
          VI.Transform.Scale.s_SetY(entityname, scenename, midDialogBoxHeight);
          VI.Transform.Scale.s_SetX(entityname, scenename, dialogBoxWidth);
          VI.Texture.s_Set(entityname, scenename, "Textures\\Icons\\dialogue\\UI_DialogueBox2.png");
        } else {
          posY += (bigDialogBoxHeight - smallDialogBoxHeight) / 2;
          VI.Transform.Scale.s_SetY(entityname, scenename, bigDialogBoxHeight);
          VI.Transform.Scale.s_SetX(entityname, scenename, dialogBoxWidth);
          VI.Texture.s_Set(entityname, scenename, "Textures\\Icons\\dialogue\\UI_DialogueBox3.png");
        }
      } else {
        if (additionalLines == 0) {
          textYSpacing = 0;
          VI.Transform.Scale.s_SetY(entityname, scenename, smallChoiceHeight);
          VI.Transform.Scale.s_SetX(entityname, scenename, choiceWidth);
          VI.Texture.s_Set(entityname, scenename, "Textures\\Icons\\dialogue\\UI_DialogueOption1.png");
        } else {
          VI.Transform.Scale.s_SetY(entityname, scenename, midChoiceHeight);
          VI.Transform.Scale.s_SetX(entityname, scenename, choiceWidth);
          VI.Texture.s_Set(entityname, scenename, "Textures\\Icons\\dialogue\\UI_DialogueOption2.png");
        }
      }

      // If it's a choice textbox, posY is the middle of both texts
      if (choice == 1)
        posY = posY + spacing + VI.Transform.Scale.s_GetY(entityname, scenename) / 2;
      else if (choice == 2)
        posY = posY - spacing - VI.Transform.Scale.s_GetY(entityname, scenename) / 2;

      VI.Transform.Position.s_SetX(entityname, scenename, posX);
      VI.Transform.Position.s_SetY(entityname, scenename, posY);

      float magicNumber = 10.0f * VI.Text.Scale.s_Get(entityname, scenename);
      VI.Text.Offset.s_Set(entityname, scenename, -VI.Transform.Scale.s_GetX(entityname) / 2 + textXSpacing, VI.Transform.Scale.s_GetY(entityname)/2 - textHeight + textYSpacing);
    }

    // Based on the current dialog ID, move to the next one. Can input choice if there is a choice selection, by default it's 1
    public void MoveToNextDialog(int choice = 1) {
      //VI.Test.ArgString("Current ID: " + Dialogue.Current.GetId());
      //VI.Test.ArgString("Next ID: " + Dialogue.Next.GetId());

      if (choice == 1)
        VI.Dialogue.Current.SetTo(VI.Dialogue.GetNextId(VI.Dialogue.Current.GetId()));
      else
        VI.Dialogue.Current.SetTo(VI.Dialogue.Choice.Second(VI.Dialogue.Current.GetId()));
    }

    // Get the texts of the next dialog, able to input 1 or 2 to get the different choices
    public string GetNextDialog(int choice = 1) {
      int ID = 0;
      if (choice == 1) {
        ID = VI.Dialogue.GetNextId(VI.Dialogue.Current.GetId());
        //Console.WriteLine("Choice 1 is: " + ID);
        //VI.Test.ArgString("Choice 1 is: " + ID);
      } else {
        ID = VI.Dialogue.Choice.Second(VI.Dialogue.Current.GetId());
        //Console.WriteLine("Choice 2 is: " + ID);
        //VI.Test.ArgString("Choice 2 is: " + ID);

      }
      //Console.WriteLine("Resultant line is: " + VI.Dialogue.GetLine(ID));
      //VI.Test.ArgString("Resultant line is: " + VI.Dialogue.GetLine(ID));
      return VI.Dialogue.GetLine(ID);
    }

    public void DeactivateDialogBox(string player, string notPlayer, string choice1, string choice2, string scene) {
      VI.Entity.s_Deactivate(player, scene);
      VI.Entity.s_Deactivate(notPlayer, scene);
      VI.Entity.s_Deactivate(choice1, scene);
      VI.Entity.s_Deactivate(choice2, scene);
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
    public bool RunDialog(string player, string notPlayer, string choice1, string choice2, string scene, string dialogFile) {
      if (dialogInit) {
        DisableUI();
        // Load Little Girl Talking
        VI.Dialogue.LoadScript(dialogFile);
        VI.Dialogue.Current.SetTo(1);

        // Setting default P1, PP1, PP2 positions
        VI.Transform.Position.SetX(PP1ID, 500);
        VI.Transform.Position.s_SetY(choice1, scene, 46);
        VI.Transform.Position.s_SetX(choice2, scene, 500);
        VI.Transform.Position.s_SetY(choice2, scene, -90);
        VI.Transform.Position.s_SetX(player, scene, 450);
        VI.Transform.Position.s_SetY(player, scene, 5);

        // Activate little girl dialogue
        string firstSpeaker;
        if (VI.Dialogue.Speaker.IsPlayer(1))
          firstSpeaker = player;
        else
          firstSpeaker = notPlayer;

        VI.Entity.s_Activate(firstSpeaker, scene);
        VI.Text.s_Update(firstSpeaker, scene, VI.Dialogue.GetLine(VI.Dialogue.Current.GetId()));

        if (VI.Dialogue.Speaker.IsPlayer(1))
          AlignPlayerText(player, scene); 
        else
          AlignNonPlayerText(notPlayer, scene);

        //camZoomingIn = true;
        dialogInit = false;
      }

      // Button click set flags
      if (choiceFlag) {
        if (VI.Input.Button.s_Released(choice1, scene) || VI.Input.Button.s_Released(choice2, scene))
          updateChat = true;
      } else if (VI.Input.Button.s_Released(player, scene) || VI.Input.Button.s_Released(notPlayer, scene))
        updateChat = true;

      // Logic done using those flags
      if (updateChat) {
        updateChat = false;

        //VI.Test.ArgString("CurrentID before check quit: " + VI.Dialogue.Current.GetId());
        //VI.Test.ArgString("NextID before check quit: " + VI.Dialogue.GetNextId(VI.Dialogue.Current.GetId()));
        // Finish dialog
        if (VI.Dialogue.GetNextId(VI.Dialogue.Current.GetId()) == 0) {
          DeactivateDialogBox(player, notPlayer, choice1, choice2, scene);
          dialogInit = true;
          //camZoomingOut = true;
          EnableUI();
          //Console.WriteLine("finished dialog");
          //VI.Test.ArgString("finished dialog");
          return false;
        }

        //Console.WriteLine("Moving on from: " + VI.Dialogue.Current.GetId());
        //VI.Test.ArgString("Moving on from: " + VI.Dialogue.Current.GetId());
        if (choiceFlag) {
          //Console.WriteLine("It's a choice dialog");
          //VI.Test.ArgString("It's a choice dialog");
          choiceFlag = false;
          if (VI.Input.Button.s_Released(choice2, scene)) {
            MoveToNextDialog(2);
            latestChoiceChosen = 2;
            LOG.WRITE("latestChoiceChosen = 2");
            //Console.WriteLine("Choice 2 selected, moving to: " + VI.Dialogue.Current.GetId());
            //VI.Test.ArgString("Choice 2 selected, moving to: " + VI.Dialogue.Current.GetId());
          } else {
            MoveToNextDialog(1);
            latestChoiceChosen = 1;
            LOG.WRITE("latestChoiceChosen = 1");
            //Console.WriteLine("Choice 1 selected, moving to: " + VI.Dialogue.Current.GetId());
            //VI.Test.ArgString("Choice 1 selected, moving to: " + VI.Dialogue.Current.GetId());
          }
          VI.Entity.s_Deactivate(choice1, scene);
          VI.Entity.s_Deactivate(choice2, scene);
        }
        MoveToNextDialog(1);
        //Console.WriteLine("Moving to: " + VI.Dialogue.Current.GetId());
        //VI.Test.ArgString("Moving to: " + VI.Dialogue.Current.GetId());

        if (VI.Dialogue.Speaker.IsPlayer(VI.Dialogue.Current.GetId())) {
          VI.Entity.s_Activate(player, scene);
          VI.Entity.s_Deactivate(notPlayer, scene);
          VI.Text.s_Update(player, scene, VI.Dialogue.GetLine(VI.Dialogue.Current.GetId()));
          AlignPlayerText(player, scene); 
        } else {
          VI.Entity.s_Activate(notPlayer, scene);
          VI.Entity.s_Deactivate(player, scene);
          VI.Text.s_Update(notPlayer, scene, VI.Dialogue.GetLine(VI.Dialogue.Current.GetId()));
          AlignNonPlayerText(notPlayer, scene);
        }

        if (VI.Dialogue.Choice.Second(VI.Dialogue.Current.GetId()) != 0) {
          //Console.WriteLine("This dialog is a choice dialog: " + VI.Dialogue.Current.GetId());
          //VI.Test.ArgString("This dialog is a choice dialog: " + VI.Dialogue.Current.GetId());
          VI.Entity.s_Activate(choice1, scene);
          VI.Entity.s_Activate(choice2, scene);
          VI.Text.s_Update(choice1, scene, GetNextDialog(1));
          VI.Text.s_Update(choice2, scene, GetNextDialog(2));
          TextBoxAlign(choice1, scene, 400, -280, 80, 15, 1);
          TextBoxAlign(choice2, scene, 400, -280, 80, 15, 2);
          choiceFlag = true;
        }
      }
      return true;
    }

    #endregion

#region minorHelpers
    void ZoomCameraToDialog() { Level1ManagerScript.ChangeZoom(960, 540); }
    void AlignPlayerText(string player, string scene) { TextBoxAlign(player, scene, 450, 5, 20, 0); }
    void AlignNonPlayerText(string nonplayer, string scene) { TextBoxAlign(nonplayer, scene, 0, 20, 20, 0); }

    #endregion

    // The General function for stand still dialogs
    void GeneralDialogStart(int direction) { // 1 to face left, 
      PlayerScript.CameraFollowPlayer = false;
      PlayerScript.PlayerInDialogue = true;
      ZoomCameraToDialog();
      VI.Animation.SpriteSheet.SheetIndex.Set(playerID, direction); // Make player face the other person
    }

    #region Dialog Endings

    void UpdateObjective(string objectiveFile) {
      VI.Dialogue.LoadScript(objectiveFile);
      if (latestChoiceChosen == 1) VI.Text.Update(UIObjectiveTextID, VI.Dialogue.GetLine(1));
      else if (latestChoiceChosen == 2) VI.Text.Update(UIObjectiveTextID, VI.Dialogue.GetLine(2));
      latestChoiceChosen = 0;
    }

    public void GeneralEndDialog() {
      PlayerScript.CameraFollowPlayer = true;
      //runPassenger2Dialog = false;
      normalZoom = false;
      PlayerScript.PlayerInDialogue = false;
    }
    public void EndIntroDialog() {
      GeneralEndDialog();

      VI.Text.Update(UIObjectiveTextID, "Objective: Find the Little Girl");
    }

    //public void EndGirlDialog() {
    //  runGirlDialog = false;
    //  PlayerScript.PlayerInDialogue = false;

    //  VI.Entity.s_Deactivate("LittleGirlBox", "Level1"); //Todo change to girl's ID or public static it's vvariable
    //  //ObjectiveTextScript.UpdateText("Finished talking to little girl"); // TODO Christy to update the text needed here
    //  //EndGirlExistance(); // TODO. after talking to girl, make her dissappear.
    //}

    public void EndPassengerDialog() {
      GeneralEndDialog();

      UpdateObjective("Dialog Objective Passenger1 (Minerva)");

      correctDestination_RenderLocation = VI.Entity.GetId("DoubleStoryHouseDropOffPoint");
      wrongDestination_RenderLocation = VI.Entity.GetId("LighthouseDropOffPoint");

      // AllowAdvance = true; // TODO to update that player has talked to passenger already
      // dialogueOrder = 2;
    }

    public void EndPassenger2Dialog() {
      GeneralEndDialog();

      UpdateObjective("Dialog Objective Passenger2 (Argus)");

      correctDestination_RenderLocation = VI.Entity.GetId("FountainDropOffPoint");
      wrongDestination_RenderLocation = VI.Entity.GetId("PortHouseDropOffPoint");
      // AllowAdvance = true; // TODO to update that player has talked to passenger already
      // dialogueOrder = 2;
    }

    public void EndDropoffDialog() {
      GeneralEndDialog();
      VI.Text.Update(UIObjectiveTextID, "Continue Exploring...");
      passengerDialogProgress = 0;
    }

    public void MoveCameraRightToDialog() {
      float playerHeight = VI.Transform.Scale.GetY(playerID);
      float playerWidth = VI.Transform.Scale.GetX(playerID);
      float screenHalfHeight = VI.Camera.GetScale.Y()/2;

      Level1ManagerScript.MoveCamera(VI.Transform.Position.GetX(playerID) + playerWidth/3,
                                     VI.Transform.Position.GetY(playerID) + screenHalfHeight - playerHeight/2);
    }

    public void MoveCameraLeftToDialog() {
      float playerHeight = VI.Transform.Scale.GetY(playerID);
      float playerWidth = VI.Transform.Scale.GetX(playerID);
      float screenHalfHeight = VI.Camera.GetScale.Y()/2;

      Level1ManagerScript.MoveCamera(VI.Transform.Position.GetX(playerID) - playerWidth / 3,
                                     VI.Transform.Position.GetY(playerID) + screenHalfHeight - playerHeight / 2);
    }

    #endregion

  }
}
