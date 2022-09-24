#pragma once
#include "pch.h"
#include "Scene.h"
#include "Input.h"

class Start_background : public Scene, public Singleton<Start_background> {
public:
	virtual void Init();
	virtual void Update();
	virtual void Reset();
	virtual void Clear();

private:


};











