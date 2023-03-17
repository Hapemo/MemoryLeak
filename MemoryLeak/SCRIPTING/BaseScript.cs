/*!*****************************************************************************
\file BaseScript.cs
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Group: Memory Leak Studios
\date 15-02-2023
\brief
Base script to be inherited by other scripts.
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage
{
    public class BaseScript
    {
    public static void CamZoom33Percent() {
      VI.Camera.SetScale.X(1200);
      VI.Camera.SetScale.Y(675);
    }

    public static void CamZoomNormal() {
      VI.Camera.SetScale.X(1600);
      VI.Camera.SetScale.Y(900);
    }

    public static bool MovePlayer(int player, float x, float y) {
      float playerPosX = VI.Transform.Position.GetX(player);
      float playerPosY = VI.Transform.Position.GetY(player);
      if (((int)playerPosX == (int)x) && ((int)playerPosY == (int)y))
        return true;
      float DirX = x - playerPosX;
      float DirY = y - playerPosY;

      // Move if the vector is significant
      if (VI.Math.SqMagnitude(DirX, DirY) > float.Epsilon * float.Epsilon) {
        // Apply force
        float NormX = VI.Math.Normalize.X(DirX, DirY);
        float NormY = VI.Math.Normalize.Y(DirX, DirY);

        VI.Physics.ApplyImpulse(player,
            (NormX * 200) * (float)VI.General.DeltaTime(),
            (NormY * 200) * (float)VI.General.DeltaTime(), 0f, 0f);
        // Get new rotation and set sprite
        //PlayerRotation = GetRotation(NormX, NormY);
        //SetPlayerSprite(player, PlayerRotation, "Idle");

        // Play rowing boat audio
        VI.Audio.Play(player);
      }

      float tempX = playerPosX - x;
      float tempY = playerPosY - y;
      if (tempX < 0) { tempX = -tempX; }
      if (tempY < 0) { tempY = -tempY; }
      if (((int)tempX < 2) && ((int)tempY < 2)) {
        VI.Transform.Position.SetX(player, x);
        VI.Transform.Position.SetY(player, y);
      }

      return false;
    }

    public static void MoveCamera(float x, float y) {
      VI.Camera.SetPos.Y(VI.Camera.GetPos.Y() + (y - VI.Camera.GetPos.Y()) * (float)VI.General.DeltaTime() * 3.0f);
      VI.Camera.SetPos.X(VI.Camera.GetPos.X() + (x - VI.Camera.GetPos.X()) * (float)VI.General.DeltaTime() * 3.0f);
    }

    public static bool ChangeZoom(float x, float speed) {
      if (VI.Camera.GetScale.X() == x)
        return true;
      float currX = VI.Camera.GetScale.X();

      if (x > currX) {
        VI.Camera.SetScale.X(currX + speed * (float)VI.General.DeltaTime());
        if (VI.Camera.GetScale.X() > x)
          VI.Camera.SetScale.X(x);
      } else {
        VI.Camera.SetScale.X(currX - speed * (float)VI.General.DeltaTime());
        if (VI.Camera.GetScale.X() < x)
          VI.Camera.SetScale.X(x);
      }

      return false;
    }
  }
}
