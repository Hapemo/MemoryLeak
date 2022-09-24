#include "AI.h"
#include "Start.h"
#include "Input.h"
#include "Helper.h"
#include "Start_1.h"
#include "Start_background.h"
#include "PerformanceVisualiser.h"
void Start::Load() {

}

void Start::Init() {
  Start_background::GetInstance()->Init();
  Start_1::GetInstance()->Init();
}

void Start::Update() {
  //lifespanManager->Update((float)Helper::dt);
  
  //Start_background::GetInstance()->PrimaryUpdate();
  Start_1::GetInstance()->PrimaryUpdate();
  animator->Animate();
  sheetAnimator->Animate();
    //TrackSystemPerformance("Physics");
    //physics2DManager->FirstUpdate(mEntities);
    //physics2DManager->FirstUpdate();
    //EndTrackSystemPerformance("Physics");

  //if (Input::CheckKey(PRESS, LEFT)) Start_background::GetInstance()->Pause(true);
  //else if (Input::CheckKey(PRESS, RIGHT)) Start_background::GetInstance()->Pause(false);
}

void Start::Draw() {
    //physics2DManager->Update(Helper::dt);
    renderManager->Render();
}

void Start::Free() {
  Start_1::GetInstance()->Clear();
  Start_background::GetInstance()->Clear();
}

void Start::Unload() {

}




