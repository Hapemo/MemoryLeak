using System;
using System.Runtime.CompilerServices;

namespace BonVoyage {
  public class TestMonoScript {
    private bool starttalking = false;

    /* Some of these flags are here to optimise the code. Because checking this bool value is faster than button check function calls */
    private bool choiceFlag = false;      // This flag is true during choice selection dialogs
    private bool playerTalking = false;   // This flag is true when player is talking, aka P1 active
    private bool updateChat = false;      // This flag is true when dialog changes for anyone
    private bool RunlittleGirlDialog = true;
    private bool RunPassengerDialog = true;
    public void Init() {
      //InternalCalls.LoadDialogs("Dialogue LittleGirl 0");
      CameraZoomIn();
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

      #region Passenger 1 Dialogue (currently using Little Girl dialogue lines)
      if (InternalCalls.EntitiesCollided("Boat", "PassengerBox", "Level1")) {

        if (InternalCalls.EntityIsActive("LittleGirlBox", "Level1") && RunPassengerDialog) {
          LockPosition(-1240, 670);
          RunPassengerDialog = RunDialog("P1", "G1", "PP1", "PP2", "Dialogue", "Dialogue LittleGirl 0");
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
          Console.WriteLine("finished dialog");
          return false;
        }

        if (choiceFlag) {
          choiceFlag = false;
          if (InternalCalls.ButtonReleased(choice2, scene)) {
            MoveToNextDialog(2);
          } else MoveToNextDialog(1);

          InternalCalls.EntityDeactivate(choice1, scene);
          InternalCalls.EntityDeactivate(choice2, scene);
        }
        MoveToNextDialog(1);

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
          InternalCalls.EntityActivate(choice1, scene);
          InternalCalls.EntityActivate(choice2, scene);
          InternalCalls.UpdateText(choice1, scene, GetNextDialog(1));
          InternalCalls.UpdateText(choice1, scene, GetNextDialog(2));
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


    

  }
}
