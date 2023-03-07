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
    static public bool runCatDialog;
    static public bool runGirlDialog;
    static public bool runPassengerDialog;
    static public bool runPassengerEndDialog;

    private int girlColliderBox;
    private int PColliderBox;
    private int PEndColliderBox;

    public override void Alive(int _ENTITY) {
        base.Alive(_ENTITY);
    }

    public override void Init(int _ENTITY) {
        base.Init(_ENTITY);

      playerID = VI.Entity.GetId("Boat");
      UIObjectiveTextID = VI.Entity.GetId("objectivetext");
      P1ID = VI.Entity.GetId("P1");
      PP1ID = VI.Entity.GetId("PP1");
      PP2ID = VI.Entity.GetId("PP2");
      G1ID = VI.Entity.GetId("G1");
      girlColliderBox = VI.Entity.GetId("GirlBox");
      PColliderBox = VI.Entity.GetId("PassengerPickupBox");
      PEndColliderBox = VI.Entity.GetId("PassengerDropOffBox");

      dialogInit = true;
      runIntroDialog = true;
    }

    public override void EarlyUpdate(int _ENTITY) {
        base.EarlyUpdate(_ENTITY);
    }

    public override void Update(int _ENTITY) {
        base.Update(_ENTITY);

      if (playerID == 0) LOG.WRITE("playerID========");
      if (UIHPBarID == 0) LOG.WRITE("UIHPBarID========");
      if (UIMemoryFragmentID == 0) LOG.WRITE("UIMemoryFragmentID========");
      if (UIMemoryFragmentScreenID == 0) LOG.WRITE("UIMemoryFragmentScreenID========");
      if (UIFragment1ObjID == 0) LOG.WRITE("UIFragment1ObjID========");
      if (UICycleMapID == 0) LOG.WRITE("UICycleMapID========");
      if (UIMiniMapID == 0) LOG.WRITE("UIMiniMapID========");
      if (UIEnemyMapID == 0) LOG.WRITE("UIEnemyMapID========");
      if (UIWeatherMapID == 0) LOG.WRITE("UIWeatherMapID========");
      if (UIWeatherTextID == 0) LOG.WRITE("UIWeatherTextID========");
      if (UIObjectiveTextID == 0) LOG.WRITE("UIObjectiveTextID========");
      if (P1ID == 0) LOG.WRITE("P1ID========");
      if (PP1ID == 0) LOG.WRITE("PP1ID========");
      if (PP2ID == 0) LOG.WRITE("PP2ID========");
      if (G1ID == 0) LOG.WRITE("G1ID========");
      if (girlColliderBox == 0) LOG.WRITE("girlColliderBox========");
      if (PColliderBox == 0) LOG.WRITE("PColliderBox========");
      if (PEndColliderBox == 0) LOG.WRITE("PEndColliderBox========");

      if (!normalZoom)
        normalZoom = Level1ManagerScript.ChangeZoom(1600, 300);

      // Dialog control

      if (runIntroDialog) {
        PlayerScript.PlayerInDialogue = true;
        runIntroDialog = RunDialog("P1", "G1", "PP1", "PP2", "TutorialDialogue", "Dialogue SceneIntro 1");
        if (!runIntroDialog)
          EndIntroDialog();
      }

      if (runGirlDialog) {
        GeneralDialogStart(1);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, -250, -635);
        runGirlDialog = RunDialog("P1", "G1", "PP1", "PP2", "TutorialDialogue", "Dialogue LittleGirl 0");
        if (!runGirlDialog)
          EndGirlDialog();
      }

      if (runCatDialog) {
        GeneralDialogStart(6);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, -770, 103);
        runCatDialog = RunDialog("P1", "G1", "PP1", "PP2", "TutorialDialogue", "Dialogue CatTutorial");
        if (!runCatDialog)
          EndCatDialog();
      }

      if (runPassengerDialog) {
        GeneralDialogStart(1);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, 650, -1160); // Move him to better location
        runPassengerDialog = RunDialog("P1", "G1", "PP1", "PP2", "TutorialDialogue", "Dialog NPC"); // Run the dialog
        if (!runPassengerDialog)
          EndPassengerDialog();
      }

      if (runPassengerEndDialog) {
        GeneralDialogStart(7);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(PEndColliderBox),
                                                 VI.Transform.Position.GetY(PEndColliderBox)); // Move him to better location
        runPassengerEndDialog = RunDialog("P1", "G1", "PP1", "PP2", "TutorialDialogue", "Dialog NPC dropoff"); // Run the dialog
        if (!runPassengerEndDialog)
          EndDropoffDialog();
      }

    }

    public override void FixedUpdate(int _ENTITY) {
        base.FixedUpdate(_ENTITY);
    }

    public override void LateUpdate(int _ENTITY) {
        base.LateUpdate(_ENTITY);
    }

    public override void Exit(int _ENTITY) {
        base.Exit(_ENTITY);

      runIntroDialog = false;
      runGirlDialog = false;
      runPassengerDialog = false;
      runPassengerEndDialog = false;
    }

    public override void Dead(int _ENTITY) {
        base.Dead(_ENTITY);
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
            
      VI.Text.Update(UIObjectiveTextID, "Objective: Get the lost soul home");

      // AllowAdvance = true; // TODO to update that player has talked to passenger already
      // dialogueOrder = 2;
    }

    public void EndCatDialog() {
      GeneralEndDialog();
    }

    public void EndGirlDialog() {
      GeneralEndDialog();
            
      VI.Text.Update(UIObjectiveTextID, "Objective: Find the lost soul");
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
