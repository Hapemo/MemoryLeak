using System;
using System.Runtime.CompilerServices;
using VI;

namespace BonVoyage {

  public class Level1Passenger1Script : BaseScript {
    private int colliderBox;
    private int playerBoat;

    public void Alive(int _ENTITY) {
      THIS.StoreId(_ENTITY); // DO NOT REMOVE!!!
    }

    public void Init(int _ENTITY) {
      colliderBox = VI.Entity.GetId("PassengerBox", "Level1");
      playerBoat = VI.Entity.GetId("Boat", "Level1");
    }

    public void Update(int _ENTITY) {
      
      if (VI.Entity.IsActive(colliderBox))
      if (VI.Physics.EntitiesCollided(colliderBox, playerBoat)) {
        //Console.WriteLine("collided");
        //VI.Animation.SheetIndex.Set(_ENTITY, 1);
        if (!Level1DialogManager.runPassengerDialog) {
          Level1DialogManager.runPassengerDialog = true;
          VI.Entity.Deactivate(colliderBox);
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
