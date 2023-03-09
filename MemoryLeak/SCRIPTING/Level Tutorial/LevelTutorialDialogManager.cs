﻿using System;
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
    private int tutorialGuider;

    public override void Alive(int _ENTITY) {
        base.Alive(_ENTITY);
    }

    public override void Init(int _ENTITY) {
        base.Init(_ENTITY);

      girlColliderBox = VI.Entity.GetId("GirlBox");
      PColliderBox = VI.Entity.GetId("PassengerPickupBox");
      PEndColliderBox = VI.Entity.GetId("PassengerDropOffBox");
        tutorialGuider = VI.Entity.GetId("MoveToCatGuider");

      dialogInit = true;
      runIntroDialog = true;
    }

    public override void EarlyUpdate(int _ENTITY) {
        base.EarlyUpdate(_ENTITY);
    }

    public override void Update(int _ENTITY) {
        base.Update(_ENTITY);


      if (!normalZoom)
        normalZoom = Level1ManagerScript.ChangeZoom(1600, 300);

      // Dialog control

      if (runIntroDialog) {
        PlayerScript.PlayerInDialogue = true;
        runIntroDialog = RunDialog(P1ID, G1ID, PP1ID, PP2ID, "Dialogue SceneIntro 1");
        if (!runIntroDialog)
          EndIntroDialog();
      }

      if (runGirlDialog) {
        GeneralDialogStart(1);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, -250, -635);
        runGirlDialog = RunDialog(P1ID, G1ID, PP1ID, PP2ID, "Dialogue LittleGirl 0");
        if (!runGirlDialog)
          EndGirlDialog();
      }

      if (runCatDialog) {
        GeneralDialogStart(6);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, -770, 103);
        runCatDialog = RunDialog(P1ID, G1ID, PP1ID, PP2ID, "Dialogue CatTutorial");
        if (!runCatDialog)
          EndCatDialog();
      }

      if (runPassengerDialog) {
        GeneralDialogStart(1);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, 650, -1160); // Move him to better location
        runPassengerDialog = RunDialog(P1ID, G1ID, PP1ID, PP2ID, "Dialog NPC"); // Run the dialog
        if (!runPassengerDialog)
          EndPassengerDialog();
      }

      if (runPassengerEndDialog) {
        GeneralDialogStart(7);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(PEndColliderBox),
                                                 VI.Transform.Position.GetY(PEndColliderBox)); // Move him to better location
        runPassengerEndDialog = RunDialog(P1ID, G1ID, PP1ID, PP2ID, "Dialog NPC dropoff"); // Run the dialog
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

            VI.Entity.Activate(tutorialGuider);

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


    #endregion

  }
}
