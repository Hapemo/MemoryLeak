#include <Lighting.h>
#include "Input.h"
#include <VertexFetcher.h>
#include "Helper.h"

Entity lightsource;

void Lighting::Load() 
{
    LoadWithGUID(16673144311251204);
    //LoadWithGUID(16673157420351748);//with colider
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
                break;
            }
        }
    }
}

void Lighting::Update()
{
    renderManager->GetGameCamera().SetPos(lightsource.GetComponent<Transform>().translation);
    for (const Entity& e : mEntities)
    {
        if (e.HasComponent<Text>())
        {
        e.GetComponent<Text>().offset = -renderManager->GetGameCamera().GetPos();
        e.GetComponent<Text>().offset.x -= e.GetComponent<Text>().text.size() * 10;
        }
    }
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
    editorManager->SetScenePaused(false);
}
