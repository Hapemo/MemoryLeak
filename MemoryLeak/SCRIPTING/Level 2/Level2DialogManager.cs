/*!*****************************************************************************
\file Level1DialogManager.cs
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 10-03-2023
\brief
Level1DialogManager contains the logic that handles the conversation between
the player and/or the different passengers in level 2 as well as the camera
transition
*******************************************************************************/

using System;
using System.Dynamic;
using System.Runtime.CompilerServices;
using VI;

// INFO
// Intro Dialog zoom is x = 1200
// Static Dialog zoom is x = 960
// Normal zoom is x = 1600

namespace BonVoyage {
  public class Level2DialogManager : DialogManager {
    public const string P1String                    = "Passenger_1";
    public const string P1BoxString                 = "Passenger1Box";
    public const string P1CorrectBoxString          = "FountainDropOffPoint";
    public const string P1WrongBoxString            = "LighthouseBox";
    public const string P1CorrectRenderString       = "FountainDestRender";
    public const string P1WrongRenderString         = "LighthouseDestRender";

    public const string P2String                    = "Passenger_2";
    public const string P2BoxString                 = "Passenger2Box";
    public const string P2CorrectBoxString          = "Porthouse5DropOffPoint";
    public const string P2WrongBoxString            = "LighthouseBox";
    public const string P2CorrectRenderString       = "Porthouse5DestRender";
    public const string P2WrongRenderString         = "LighthouseDestRender";

    //private bool progressUpdate = false;
    static public bool runIntroDialog;
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

      P1ColliderBox = VI.Entity.GetId(P1BoxString);
      P2ColliderBox = VI.Entity.GetId(P2BoxString);

      dialogInit = true;

      VI.Entity.s_Deactivate(P2String);
      VI.Entity.Deactivate(P2ColliderBox);
    }

    public override void EarlyUpdate(int _ENTITY) {
        base.EarlyUpdate(_ENTITY);
    }

    public override void Update(int _ENTITY) {
        base.Update(_ENTITY);

      if (!normalZoom)
        normalZoom = Level1ManagerScript.ChangeZoom(1600, 300);

      // Dialog control
      if (runPassengerDialog) {
        GeneralDialogStart(1);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(P1ColliderBox), 
                                                 VI.Transform.Position.GetY(P1ColliderBox)); // Move him to better location
        runPassengerDialog = RunDialog(P1ID, G1ID, PP1ID, PP2ID, "Dialog Prometheus"); // Run the dialog
        if (!runPassengerDialog)
          EndPassengerDialog();
      }

      if (runPassenger2Dialog) {
        GeneralDialogStart(5);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(P2ColliderBox), 
                                                 VI.Transform.Position.GetY(P2ColliderBox));
        runPassenger2Dialog = RunDialog(P1ID, G1ID, PP1ID, PP2ID, "Dialog Eleos");
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
          VI.Entity.Activate(VI.Entity.GetId(P2String));
          VI.Entity.Activate(P2ColliderBox);
        }
        EnemyController.EnemyActivated = true;
        VI.Entity.s_Activate("Enemy");

        dialogEnded = RunDialog(P1ID, G1ID, PP1ID, PP2ID, "Dialog Prometheus (Lighthouse)");
        if (!dialogEnded) EndDropoffDialog();
        break;
      case 11: // Passenger 1 correct
        GeneralDialogStart(5);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(correctDestination_RenderLocation),
                                                 VI.Transform.Position.GetY(correctDestination_RenderLocation));
        if (!VI.Entity.IsActive(P2ColliderBox)) {
          VI.Entity.Activate(VI.Entity.GetId(P2String));
          VI.Entity.Activate(P2ColliderBox);
        }
        dialogEnded = RunDialog(P1ID, G1ID, PP1ID, PP2ID, "Dialog Prometheus (Water Fountain)");
        if (!dialogEnded) EndDropoffDialog();
        break;
      case 20: // Passenger 2 wrong
        GeneralDialogStart(1);
        MoveCameraLeftToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(wrongDestination_RenderLocation),
                                                 VI.Transform.Position.GetY(wrongDestination_RenderLocation));
        allPassengerDelivered = true;
        EnemyController.EnemyActivated = true;
        VI.Entity.s_Activate("Enemy");

        dialogEnded = RunDialog(P1ID, G1ID, PP1ID, PP2ID, "Dialog Eleos (Lighthouse)");
        if (!dialogEnded) EndDropoffDialog();
        break;
      case 21: // Passenger 2 correct
        GeneralDialogStart(7);
        MoveCameraRightToDialog();
        Level1ManagerScript.MovePlayer(playerID, VI.Transform.Position.GetX(correctDestination_RenderLocation),
                                                 VI.Transform.Position.GetY(correctDestination_RenderLocation));
        allPassengerDelivered = true;
        EnemyController.EnemyActivated = true;
        VI.Entity.s_Activate("Enemy");

        dialogEnded = RunDialog(P1ID, G1ID, PP1ID, PP2ID, "Dialog Eleos (Island)");
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
      runIntroDialog = false;
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

      correctDestination_RenderLocation = VI.Entity.GetId(P1CorrectBoxString);
      wrongDestination_RenderLocation = VI.Entity.GetId(P1WrongBoxString);

      // AllowAdvance = true; // TODO to update that player has talked to passenger already
      // dialogueOrder = 2;

        // Activate drop off point entity based on the dialog chosen
      // Activate drop off point entity based on the dialog chosen
      if (base.latestChoiceChosen == 1) VI.Entity.Activate(correctDestination_RenderLocation);
      else if (base.latestChoiceChosen == 2) VI.Entity.Activate(wrongDestination_RenderLocation);

      UpdateObjective("Dialog Objective Passenger1 (Prometheus)");
    }

    public void EndPassenger2Dialog() {
      GeneralEndDialog();

      correctDestination_RenderLocation = VI.Entity.GetId(P2CorrectBoxString);
      wrongDestination_RenderLocation = VI.Entity.GetId(P2WrongBoxString);
      // AllowAdvance = true; // TODO to update that player has talked to passenger already
      // dialogueOrder = 2;

      // Activate drop off point entity based on the dialog chosen
      if (base.latestChoiceChosen == 1) VI.Entity.Activate(correctDestination_RenderLocation);
      else if (base.latestChoiceChosen == 2) VI.Entity.Activate(wrongDestination_RenderLocation);

      UpdateObjective("Dialog Objective Passenger2 (Eleos)");
    }

    #endregion

  }
}
