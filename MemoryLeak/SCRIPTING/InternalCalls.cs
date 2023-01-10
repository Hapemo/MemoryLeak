using System;
using System.Runtime.CompilerServices;

namespace BonVoyage
{
    public class InternalCalls
	{
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool CheckKey();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static float GetWorldMousePosX();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static float GetWorldMousePosY();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void ApplyImpulse();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void LoadDialogs();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static string GetDialogue();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static int GetNextDialogueID();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool HasChoice();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static int GetChoice1();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static int GetChoice2();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static int GetNext();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void SetSelectedChoice();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool SetCurrentDialogueID();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static int GetCurrentDialogueID();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void ChangeGameState();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void PauseScene();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void PlayScene();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool EntityIsActive();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void EntityActivate();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void EntityDeactivate();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static string EntityGetParent();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static int EntityGetParentId();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void SetTexture();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static string GetTexture();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool EntitiesCollided();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void GameStateExit();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static double GetDeltaTime();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void InitScriptWindow();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void PlayAnySound();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool IsPlaying();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void PlayBGSound();
	}
}
