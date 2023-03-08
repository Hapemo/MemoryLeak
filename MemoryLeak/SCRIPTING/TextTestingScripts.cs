using System;
using System.Dynamic;
using System.Runtime.CompilerServices;
using VI;



namespace BonVoyage {
  public class TextTestingScripts : DialogManager {

    private int currentID;
    private int currentFile;
    private bool isChoice;

    private string[] fileNames;

    public override void Alive(int _ENTITY) {
      base.Alive(_ENTITY);
      fileNames = new string[] { "Dialog NPC", 
                                 "Dialog Objective Passenger1 (Minerva)", 
                                 "Dialog Objective Passenger2 (Argus)", 
                                 "Dialog Prometheus (Lighthouse)" };
    }

    public override void Init(int _ENTITY) {
      base.Init(_ENTITY);
      currentID = 0;
      currentFile = 0;
      isChoice = false;

      VI.Dialogue.LoadScript(fileNames[currentFile]);
    }

    public override void EarlyUpdate(int _ENTITY) {
      base.EarlyUpdate(_ENTITY);
    }

    void UpdateText() {
      VI.Text.s_Update("P1", "Text", VI.Dialogue.GetLine(currentID));
      if (!isChoice) TextBoxAlign("P1", "Text", 0, 0, 20, 0);
      else TextBoxAlign("P1", "Text", 0, 0, 80, 15, 1);
    }

    public override void Update(int _ENTITY) {
      base.Update(_ENTITY);
      if (VI.Input.Key.Press(262)) {// Click right key
        ++currentID;
        LOG.WRITE("Current ID = " +  currentID);
        if (VI.Input.Key.Hold(340)) UpdateText(); // Hold shift key
      }

      if (VI.Input.Key.Press(263)) {// Click left key
        if (currentID == 0) {
          LOG.WRITE("Cannot decrement current text ID less than 0");
          return;
        }
        --currentID;
        LOG.WRITE("Current ID = " +  currentID);
        if (VI.Input.Key.Hold(340)) UpdateText(); // Hold shift key
      }

      if (VI.Input.Key.Press(32)) {// Click space key
        UpdateText();
      }

      if (VI.Input.Key.Press(67)) {
        //Click C key
        isChoice = !isChoice;
        UpdateText();
      }
      if (VI.Input.Key.Press(264)) {//Click down key
        if (currentFile == 0) {
          LOG.WRITE("Current file cannot decrement before 0");
          return;
        }
        currentFile--;
        LOG.WRITE("Current File ID: " + currentFile + " | New filename: " + fileNames[currentFile]);
        VI.Dialogue.LoadScript(fileNames[currentFile]);
        currentID = 0;
        UpdateText();
      }

      if (VI.Input.Key.Press(265)) {//Click up key
        if (currentFile == fileNames.Length-1) {
          LOG.WRITE("Current file cannot increment after " + (fileNames.Length-1));
          return;
        }
        currentFile++;
        LOG.WRITE("Current File ID: " + currentFile + " | New filename: " + fileNames[currentFile]);
        VI.Dialogue.LoadScript(fileNames[currentFile]);
        currentID = 0;
        UpdateText();
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

    }

    public override void Dead(int _ENTITY) {
      base.Dead(_ENTITY);
    }

  }
}
