using System;
using System.Runtime.CompilerServices;

namespace BonVoyage
{
    public class InternalCalls
	{
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool CheckKey();

        //private extern class Math;

		//[MethodImplAttribute(MethodImplOptions.InternalCall)]
		//internal extern static Math::Vec2 GetWorldMousePos();

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

		//[MethodImplAttribute(MethodImplOptions.InternalCall)]
		//internal extern static pair<int, int> GetChoices();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void SetSelectedChoice();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool SetCurrentDialogueID();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static int GetCurrentDialogueID();

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void ChangeGameState();

		//[MethodImplAttribute(MethodImplOptions.InternalCall)]
		//internal extern static Entity GetEntity();

		//[MethodImplAttribute(MethodImplOptions.InternalCall)]
		//internal extern static Scene& SelectScene();

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
