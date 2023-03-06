using System;
using System.Dynamic;
using System.Runtime.CompilerServices;
using VI;

// INFO
// Intro Dialog zoom is x = 1200
// Static Dialog zoom is x = 960
// Normal zoom is x = 1600

namespace BonVoyage {
  public class LevelTutorialDialogManager : DialogManager {


    private bool progressUpdate = false;
    static public bool runIntroDialog;
    static public bool runGirlDialog;
    static public bool runPassengerDialog;
    static public bool runPassengerEndDialog;

    private int girlColliderBox;
    private int PColliderBox;
    private int PEndColliderBox;

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

      girlColliderBox = VI.Entity.GetId("GirlBox");
      PColliderBox = VI.Entity.GetId("PassengerPickupBox");
      PEndColliderBox = VI.Entity.GetId("TutorialEndCollider");

      dialogInit = true;
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

      if (runGirlDialog) {
        GeneralDialogStart(1);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(-280), 
                                                 VI.Transform.Position.GetY(-635));
        runGirlDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialogue LittleGirl 0");
        if (!runGirlDialog)
          EndGirlDialog();
      }

      if (runPassengerDialog) {
        GeneralDialogStart(1);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(650), 
                                                 VI.Transform.Position.GetY(-1160)); // Move him to better location
        runPassengerDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialog NPC"); // Run the dialog
        if (!runPassengerDialog)
          EndPassengerDialog();
      }

      if (runPassengerEndDialog) {
        GeneralDialogStart(1);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(PEndColliderBox),
                                                 VI.Transform.Position.GetY(PEndColliderBox)); // Move him to better location
        runPassengerEndDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialog NPC dropoff"); // Run the dialog
        if (!runPassengerEndDialog)
          EndPassengerDialog();
      }

    }

    public void FixedUpdate(int _ENTITY) {

    }

    public void LateUpdate(int _ENTITY) {

    }

    public void Exit(int _ENTITY) {
      runIntroDialog = false;
      runGirlDialog = false;
      runPassengerDialog = false;
      runPassengerEndDialog = false;
    }

    public void Dead(int _ENTITY) {

    }

    #region Dialog Endings

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

      // AllowAdvance = true; // TODO to update that player has talked to passenger already
      // dialogueOrder = 2;
    }

    public void EndGirlDialog() {
      GeneralEndDialog();

      UpdateObjective("Dialog Objective Passenger2 (Argus)");
      // AllowAdvance = true; // TODO to update that player has talked to passenger already
      // dialogueOrder = 2;
    }

    public void EndDropoffDialog() {
      GeneralEndDialog();
      VI.Text.Update(UIObjectiveTextID, "Continue Exploring...");
    }


    #endregion

  }
}
