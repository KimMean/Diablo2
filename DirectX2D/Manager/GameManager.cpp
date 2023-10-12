#include "Framework.h"

#include "Scenes/DiabloScene.h"

GameManager::GameManager()
{
    Create();

    uiViewBuffer = new MatrixBuffer();

    scene = new DiabloScene();
}

GameManager::~GameManager()
{
    delete scene;
    delete uiViewBuffer;

    Delete();
}

void GameManager::Update()
{
    Keyboard::Get()->Update();
    Timer::Get()->Update();

    scene->Update();

    CAM->Update();

    mouseWheel = 0.0f;
}

void GameManager::Render()
{
    scene->PreRender();
    
    Device::Get()->Clear();
    Font::Get()->GetDC()->BeginDraw();

    Environment::Get()->SetViewport();
    Environment::Get()->SetProjection();

    scene->Render();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    //string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
    //Font::Get()->RenderText(fps, { 100, WIN_HEIGHT - 10 });

    CAM->RenderUI();

    uiViewBuffer->SetVS(1);
    scene->PostRender();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    Font::Get()->GetDC()->EndDraw();

    Device::Get()->Present();
}

void GameManager::Create()
{
    Keyboard::Get();
    Timer::Get();
    Device::Get();
    Environment::Get();
    Observer::Get();

    Font::Get()->AddColor("White", 1, 1, 1);
    Font::Get()->AddStyle("Default", L"배달의민족 주아");

    Font::Get()->SetColor("White");
    Font::Get()->SetStyle("Default");

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
    Keyboard::Delete();
    Timer::Delete();
    Device::Delete();
    Shader::Delete();
    Texture::Delete();
    Environment::Delete();    
    Observer::Delete();
    Font::Delete();

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();
}
