﻿using System;
using System.Dynamic;
using System.Runtime.CompilerServices;
using VI;

// INFO
// Intro Dialog zoom is x = 1200
// Static Dialog zoom is x = 960
// Normal zoom is x = 1600

namespace BonVoyage {
  public class Level1DialogManager : DialogManager {


    static public int passengerDialogProgress = 0; // Consists of 2 numbers in this format <passenger number><right or wrong>. 1 for right, 0 for wrong. eg passenger 1 right answer destination reached, it will be 11.
    private bool progressUpdate = false;
    //static public bool runGirlDialog;

    private int correctDestination_RenderLocation;
    private int wrongDestination_RenderLocation;

    static public bool runPassengerDialog;
    private int P1ColliderBox;
    
    static public bool runPassenger2Dialog;
    private int P2ColliderBox;


    public override void Alive(int _ENTITY) {
        base.Alive(_ENTITY);
    }

    public override void Init(int _ENTITY) {
        base.Init(_ENTITY);

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
            UIPassengersLeftID = VI.Entity.GetId("PassengersLeft", "Dialogue");
            UIPassengerIcon1ID = VI.Entity.GetId("PassengerIcon1", "Dialogue");
            UIPassengerIcon2ID = VI.Entity.GetId("PassengerIcon2", "Dialogue");
      dialogInit = true;
      normalZoom = false;

      VI.Entity.s_Deactivate("Passenger2");
      VI.Entity.Deactivate(P2ColliderBox);
    }

    public override void EarlyUpdate(int _ENTITY) {
        base.EarlyUpdate(_ENTITY);
    }

    public override void Update(int _ENTITY) {
        base.Update(_ENTITY);

      if (!normalZoom)
        normalZoom = Level1ManagerScript.ChangeZoom(1600, 300);


      if (runPassengerDialog) {
        GeneralDialogStart(1);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(P1ColliderBox), 
                                                 VI.Transform.Position.GetY(P1ColliderBox)); // Move him to better location
        runPassengerDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialog Minerva"); // Run the dialog
        if (!runPassengerDialog)
          EndPassengerDialog();
      }

      if (runPassenger2Dialog) {
        GeneralDialogStart(1);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(P2ColliderBox), 
                                                 VI.Transform.Position.GetY(P2ColliderBox));
        runPassenger2Dialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialog Argus");
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
        MemoryFragmentExpand.ActivateFragment(0);
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
        MemoryFragmentExpand.ActivateFragment(0);
        if (!dialogEnded) EndDropoffDialog();
        break;
      case 20: // Passenger 2 wrong
        GeneralDialogStart(1);
        MoveCameraLeftToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(wrongDestination_RenderLocation),
                                                 VI.Transform.Position.GetY(wrongDestination_RenderLocation));
        dialogEnded = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialog Argus (Brown House)");
        MemoryFragmentExpand.ActivateFragment(1);
        if (!dialogEnded) EndDropoffDialog();
        break;
      case 21: // Passenger 2 correct
        GeneralDialogStart(7);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(correctDestination_RenderLocation),
                                                 VI.Transform.Position.GetY(correctDestination_RenderLocation));
        dialogEnded = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialog Argus (Water Fountain)");
        EnemyController.EnemyActivated = true;
        MemoryFragmentExpand.ActivateFragment(1);
        if (!dialogEnded) EndDropoffDialog();
        break;
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

      passengerDialogProgress = 0;
      runPassengerDialog = false;
      runPassenger2Dialog = false;
    }

    public override void Dead(int _ENTITY) {
        base.Dead(_ENTITY);
    }

    #region Dialog Endings

    public void EndIntroDialog() {
      GeneralEndDialog();

      VI.Text.Update(UIObjectiveTextID, "Objective: Find the Little Girl");
    }

    public void EndPassengerDialog() {
      GeneralEndDialog();

      correctDestination_RenderLocation = VI.Entity.GetId("DoubleStoryHouseDropOffPoint");
      wrongDestination_RenderLocation = VI.Entity.GetId("LighthouseDropOffPoint");

      // AllowAdvance = true; // TODO to update that player has talked to passenger already
      // dialogueOrder = 2;
      
        // Activate drop off point entity based on the dialog chosen
        switch (base.latestChoiceChosen) {
            case 1:
                VI.Entity.Activate(correctDestination_RenderLocation);
                break;
            case 2:
                VI.Entity.Activate(wrongDestination_RenderLocation);
                break;
            default:
                break;
        }

        UpdateObjective("Dialog Objective Passenger1 (Minerva)");
    }

    public void EndPassenger2Dialog() {
      GeneralEndDialog();

      correctDestination_RenderLocation = VI.Entity.GetId("FountainDropOffPoint");
      wrongDestination_RenderLocation = VI.Entity.GetId("PortHouseDropOffPoint");
      // AllowAdvance = true; // TODO to update that player has talked to passenger already
      // dialogueOrder = 2;

        // Activate drop off point entity based on the dialog chosen
        switch (base.latestChoiceChosen) {
            case 1:
                VI.Entity.Activate(correctDestination_RenderLocation);
                break;
            case 2:
                VI.Entity.Activate(wrongDestination_RenderLocation);
                break;
            default:
                break;
        }

      UpdateObjective("Dialog Objective Passenger2 (Argus)");
    }

    public void EndDropoffDialog() {
      GeneralEndDialog();
      VI.Text.Update(UIObjectiveTextID, "Continue Exploring...");
      passengerDialogProgress = 0;
    }


    #endregion

  }
}
