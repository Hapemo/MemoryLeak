using System;
using System.Runtime.CompilerServices;
using VI;

namespace BonVoyage {

  public class Level1Passenger2Script : BaseScript {
    private int colliderBox;
    private int playerBoat;

    public void Alive(int _ENTITY) {
      THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
    }

    public void Init(int _ENTITY) {
      colliderBox = VI.Entity.GetId("Passenger2Box", "Level1");
      playerBoat = VI.Entity.GetId("Boat", "Level1");
    }

    public void Update(int _ENTITY) {
      if (VI.Entity.IsActive(colliderBox)) {
        if (VI.Physics.EntitiesCollided(colliderBox, playerBoat)) {
          //Console.WriteLine("collided");
          VI.Test.ArgString("collided");
          if (!Level1DialogManager.runPassenger2Dialog) {
            Level1DialogManager.runPassenger2Dialog = true;
            VI.Entity.Deactivate(colliderBox);
          }
        }

      }


    }

    public void FixedUpdate(int _ENTITY) {

    }

    public void Exit(int _ENTITY) {

    }

    public void Dead(int _ENTITY) {

    }

  }
}
