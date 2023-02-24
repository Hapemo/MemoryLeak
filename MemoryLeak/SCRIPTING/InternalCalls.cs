/*!*****************************************************************************
\file InternalCalls.cs
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 02-02-2023
\brief
This file contains the function declarations of the class InternalCalls in C#.
InternalCalls are where all functions that scripts need to use from the engine
is being stored.
*******************************************************************************/

using System;
using System.Runtime.CompilerServices;

namespace BonVoyage
{
	public class THIS
	{
		static int ENTITY = 0;
		internal static bool StoreId(int _ENTITY) {
			ENTITY = _ENTITY;
			return true;
		}

		public class Parent {
			internal static string Name() { return VI.Entity.Parent.Name(ENTITY); }
			internal static int Id() { return VI.Entity.Parent.Id(ENTITY); }
		}
		internal static int GetId() { return ENTITY; }
		internal static bool IsActive() { return VI.Entity.IsActive(ENTITY); }
		internal static void SetActive(bool _active = true) { VI.Entity.SetActive(ENTITY, _active); }
		internal static void Activate() { VI.Entity.Activate(ENTITY); }
		internal static void Deactivate() { VI.Entity.Deactivate(ENTITY); 
		}
		public class Input {
			public class Button {
				internal static bool Clicked() { return VI.Input.Button.Clicked(ENTITY); }
				internal static bool Released() { return VI.Input.Button.Released(ENTITY); }
				internal static bool Hover() { return VI.Input.Button.Hover(ENTITY); }
			}
		}

		public class Animation {
			public class SheetIndex {
				internal static void Set(int _index) { VI.Animation.SheetIndex.Set(ENTITY, _index); }
				internal static int Get() { return VI.Animation.SheetIndex.Get(ENTITY); }
			}
			public class Speed {
				internal static void Set(float _speed) { VI.Animation.Speed.Set(ENTITY, _speed); }
				internal static float Get() { return VI.Animation.Speed.Get(ENTITY); }
			}
			public class CurrentFrame {
				internal static void Set(int _index) { VI.Animation.CurrentFrame.Set(ENTITY, _index); }
				internal static int Get() { return VI.Animation.CurrentFrame.Get(ENTITY); }
			}
			public class FrameCount {
				internal static void Set(int _count) { VI.Animation.FrameCount.Set(ENTITY, _count); }
				internal static int Get() { return VI.Animation.FrameCount.Get(ENTITY); }
			}
		}
		public class Texture {
			internal static void Set(string _path) { VI.Texture.Set(ENTITY, _path); }
			internal static string Get() { return VI.Texture.Get(ENTITY); }
		}
		public class Audio {
			internal static void Play() { VI.Audio.Play(ENTITY); }
			internal static void PlayOnLoop() { VI.Audio.PlayOnLoop(ENTITY); }
			internal static void Stop() { VI.Audio.Stop(ENTITY); }
			internal static void SetLoop(bool _loop = true) { VI.Audio.SetLoop(ENTITY, _loop); }
		}
		public class Transform {
			public class Position {
				internal static float GetX() { return VI.Transform.Position.GetX(ENTITY); }
				internal static float GetY() { return VI.Transform.Position.GetY(ENTITY); }
				internal static void SetX(float _posX) { VI.Transform.Position.SetX(ENTITY, _posX); }
				internal static void SetY(float _posY) { VI.Transform.Position.SetY(ENTITY, _posY); }
			}
			public class Scale {
				internal static float GetX() { return VI.Transform.Scale.GetX(ENTITY); }
				internal static float GetY() { return VI.Transform.Scale.GetY(ENTITY); }
				internal static void SetX(float _scaleX) { VI.Transform.Scale.SetX(ENTITY, _scaleX); }
				internal static void SetY(float _scaleY) { VI.Transform.Scale.SetY(ENTITY, _scaleY); }
			}
			public class Rotate {
				internal static float Get() { return VI.Transform.Rotate.Get(ENTITY); }
				internal static void Set(float _rotate) { VI.Transform.Rotate.Set(ENTITY, _rotate); }
			}
		}
		public class Text {
			internal static void Update(string _text) { VI.Text.Update(ENTITY, _text); }
			internal static int GetLineCount() { return VI.Text.GetLineCount(ENTITY); }
			public class Offset {
				internal static void Set(float _xoffset, float _yoffset) { VI.Text.Offset.Set(ENTITY, _xoffset, _yoffset); }
				internal static float GetX() { return VI.Text.Offset.GetX(ENTITY); }
				internal static float GetY() { return VI.Text.Offset.GetY(ENTITY); }
			}
			public class Scale {
				internal static float Get() { return VI.Text.Scale.Get(ENTITY); }
				internal static void Set(float _scale) { VI.Text.Scale.Set(ENTITY, _scale); }
			}
		}
		public class LightSource {
			public class Radius {
				internal static float Get() { return VI.LightSource.Radius.Get(ENTITY); }
				internal static void Set(float _radius) { VI.LightSource.Radius.Set(ENTITY, _radius); }
			}
			public class SpriteColor {
				internal static void Set(int _r, int _g, int _b, int _a) { VI.LightSource.SpriteColor.Set(ENTITY, _r, _g, _b, _a); }
			}
		}
	}
}

namespace VI
{
	public class Test
	{
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static bool ArgString(string _thingToPrint);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static string ReturnString();
	}
	public class General
	{
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static double DeltaTime();
	}
	public class Input
	{
		public class Key
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool Press(int _key);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool Hold(int _key);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool Release(int _key);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool Idle(int _key);
		}
		public class Button
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool s_Clicked(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool s_Released(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool s_Hover(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool Clicked(int _id);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool Released(int _id);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool Hover(int _id);
		}
		public class Mouse
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float WorldPosX();

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float WorldPosY();

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool Press(int _key = 349); // right mouse click

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool Hold(int _key = 349); // right mouse click

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool Release(int _key = 349); // right mouse click

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool Idle(int _key = 349); // right mouse click
		}
	}
	public class Physics
	{
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void s_ApplyImpulse(string _entityName, string _sceneName, float _impulseX, float _impulseY, float _rotationX, float _rotationY);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static bool s_EntitiesCollided(string _entityName1, string _entityName2, string _sceneName);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static bool s_CheckCollision(string _entityName1, string _entityName2, string _sceneName, bool _dynamicCheck);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void ApplyImpulse(int _eId, float _impulseX, float _impulseY, float _rotationX, float _rotationY);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static bool EntitiesCollided(int _eId1, int _eId2);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static bool CheckCollision(int _eId1, int _eId2, bool _dynamicCheck);
	}
	public class Dialogue
	{
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void LoadScript(string _filename);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static string GetLine(int _id);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static bool HaveChoices(int _id);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void GetSelectedChoice(int _id);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static string GetNext(int _id);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static int GetNextId(int _id);
		public class Current
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static string GetLine();

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int GetId();

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool HaveChoices();

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool SetTo(int _id);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int GetFirstChoice();

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int GetSecondChoice();

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void SetSelectedChoice(int _selectedChoice);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void GetSelectedChoice();

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool PlayerSpeaking();
		}
		public class Next
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static string GetLine();

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int GetId();

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool HaveChoices();
			
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int GetFirstChoice();

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int GetSecondChoice();

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool PlayerSpeaking();
		}
		public class Choice
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int First(int _id);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int Second(int _id);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void Selected(int _id, int _selectedChoice);
		}
		public class Speaker
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool IsPlayer(int _id);
		}
	}
	public class GameState
	{
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void Go(string _name);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static string GetName();

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void Exit();
	}
	public class Entity
	{
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static int GetId(string _entityName, string _sceneName);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static bool s_IsActive(string _entityName, string _sceneName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static void s_SetActive(string _entityName, string _sceneName, bool _active = true);

        [MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void s_Activate(string _entityName, string _sceneName);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void s_Deactivate(string _entityName, string _sceneName);
		public class Parent
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static string s_Name(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static string Name(int _eId);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int s_Id(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int Id(int _eId);
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static bool IsActive(int _eId);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void SetActive(int _eId, bool _active = true);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void Activate(int _eId);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void Deactivate(int _eId);
	}
	public class Scene
	{
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void Pause(string _name);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void Play(string _name);
	}
	public class Camera
	{
		public class GetScale
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float X();

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float Y();
		}

		public class SetScale
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void X(float _x);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void Y(float _y);
		}
		public class GetPos
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float X();

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float Y();
		}

		public class SetPos
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void X(float _x);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void Y(float _y);
		}
	}
	public class Math
	{
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static float SqMagnitude(float _x, float _y);

		public class Normalize
        {
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float X(float _x, float _y);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float Y(float _x, float _y);
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static float ArcTangent(float _x, float _y);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static float Negate(float _value);
	}
	public class Animation
	{
		public class SheetIndex
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void s_Set(string _entityName, string _sceneName, int _index);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int s_Get(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void Set(int _eId, int _index);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int Get(int _eId);
		}
		public class Speed
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void s_Set(string _entityName, string _sceneName, float _speed);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float s_Get(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void Set(int _eId, float _speed);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float Get(int _eId);
		}
		public class CurrentFrame
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void s_Set(string _entityName, string _sceneName, int _index);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int s_Get(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void Set(int _eId, int _index);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int Get(int _eId);
		}
		public class FrameCount
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void s_Set(string _entityName, string _sceneName, int _count);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int s_Get(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void Set(int _eId, int _count);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static int Get(int _eId);
		}
		
		public class Transform
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void Start(int _eId);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static bool SetNext(int _eId, int _i); // return true if successful (withing 0 to the vector MAX)

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void Stop(int _eId, bool _next = true);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void StopAfterEndLoop(int _eId, bool _loop = true);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void ReverseOrder(int _eId, bool _reverse = true);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void SetLoopCycle(int _eId, bool _cycle = true);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void AddTransform(int _eId, float _scaleX, float _scaleY, float _rot, float _posX, float _posY, float _time = 1);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void AddTransformDifference(int _eId, float _scaleX, float _scaleY, float _rot, float _posX, float _posY, float _time = 1);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void SetCalculatedTimeFromPosition(int _eId, float _posX, float _posY, int _step = -1);
			
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void SetCalculatedTimeFromRotation(int _eId, float _rot, int _step = -1);
			
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void SetCalculatedTimeFromScale(int _eId, float _scaleX, float _scaleY, int _step = -1);
		}
	}
	public class Texture
	{
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void s_Set(string _entityName, string _sceneName, string _path);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static string s_Get(string _entityName, string _sceneName);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void Set(int _eId, string _path);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static string Get(int _eId);
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static int GetLayer(int _eId);
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void SetLayer(int _eId, int _layer);
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static int s_GetLayer(string _entityName, string _sceneName);
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void s_SetLayer(string _entityName, string _sceneName, int layer);
	}
	public class Audio
	{
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void s_Play(string _entityName, string _sceneName);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void s_PlayOnLoop(string _entityName, string _sceneName);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void s_SetLoop(string _entityName, string _sceneName, bool _loop = true);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void s_Stop(string _entityName, string _sceneName);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void Play(int _eId);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void PlayOnLoop(int _eId);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void PlayBGM(string _soundName);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static bool IsBgmPlaying();

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void Stop(int _eId);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void StopAll();

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void StopBGM();

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void StopSFX();

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void SetLoop(int _eId, bool _loop = true);
		public class Volume
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void SetVolume(float _vol);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void SetBGMVolume(float _vol);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void SetSFXVolume(float _vol);
		}
	}
	public class Transform
	{
		public class Position
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float s_GetX(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float s_GetY(string _entityName, string _sceneName);
			
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void s_SetX(string _entityName, string _sceneName, float _posX);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void s_SetY(string _entityName, string _sceneName, float _posY);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float GetX(int _eId);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float GetY(int _eId);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void SetX(int _eId, float _posX);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void SetY(int _eId, float _posY);
		}
		public class Scale
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float s_GetX(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float s_GetY(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void s_SetX(string _entityName, string _sceneName, float _scaleX);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void s_SetY(string _entityName, string _sceneName, float _scaleY);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float GetX(int _eId);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float GetY(int _eId);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void SetX(int _eId, float _scaleX);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void SetY(int _eId, float _scaleY);
		}
		public class Rotate
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float s_Get(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void s_Set(string _entityName, string _sceneName, float _rotate);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float Get(int _eId);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void Set(int _eId, float _rotate);
		}
	}
	public class Text
	{
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void s_Update(string _entityName, string _sceneName, string _text);
	
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static int s_GetLineCount(string _entityName, string _sceneName);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void Update(int _eId, string _text);

		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static int GetLineCount(int _eId);
		public class Offset
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void s_Set(string _entityName, string _sceneName, float _xoffset, float _yoffset);
			
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float s_GetX(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float s_GetY(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void Set(int _eId, float _xoffset, float _yoffset);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float GetX(int _eId);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float GetY(int _eId);
		}
		public class Scale
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float s_Get(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void s_Set(string _entityName, string _sceneName, float _scale);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float Get(int _eId);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void Set(int _eId, float _scale);
		}
	}
	public class Weather
	{
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static void Init(float _width, float _height);
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal extern static int GetCurrent(int _index, float _posX, float _posY);
	}
	public class LightSource
	{
		public class Radius
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float s_Get(string _entityName, string _sceneName);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void s_Set(string _entityName, string _sceneName, float _radius);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static float Get(int _eId);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void Set(int _eId, float _radius);
		}
		public class SpriteColor
		{
			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void s_Set(string _entityName, string _sceneName, int _r, int _g, int _b, int _a);

			[MethodImpl(MethodImplOptions.InternalCall)]
			internal extern static void Set(int _eId, int _r, int _g, int _b, int _a);
		}
	}
}