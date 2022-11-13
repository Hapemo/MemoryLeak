#include <Lighting.h>
#include "Input.h"
#include <VertexFetcher.h>
#include "Helper.h"

Entity lightsource;
bool check = false;
void Lighting::Load() 
{
    serializationManager->LoadScene("Scene_Lighting");
}

void Lighting::Init()
{
    renderManager->SetDebug(true);
    renderManager->RenderToScreen();
    editorManager->SetScenePaused(false);
   
    for (const Entity& e : mEntities)
    {
        if (e.HasComponent<General>())
        {
            if (e.GetComponent<General>().tag == TAG::PLAYER)
            {
                lightsource = e;
                check = true;
                break;
            }
        }
    }
}

void Lighting::Update()
{
    if (check == false)
    {
        //LOG_INFO("Cant find light source");
        return;
    }

    renderManager->GetGameCamera().SetPos(lightsource.GetComponent<Transform>().translation);
    shadowManager->MakeShadows(lightsource, renderManager);
    
}

void Lighting::Draw()
{
    renderManager->Render();
}

void Lighting::Free()
{
    for (auto& scenePtr : mScenes)
        scenePtr->Exit();
    renderManager->RenderToFrameBuffer();
}

void Lighting::Unload() {
    ECS::DestroyAllEntities();
    editorManager->SetScenePaused(false);
}
