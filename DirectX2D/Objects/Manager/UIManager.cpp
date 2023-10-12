#include "Framework.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
    for (pair<string, Panel*> panel : panels)
        delete panel.second;
}

void UIManager::Update()
{
    CloseLastUI();

    for (pair<string, Panel*> panel : panels)
        panel.second->Update();
}

void UIManager::Render()
{
    for (Panel* panel : popupList)
    {
        panel->Render();        
    }

    for (pair<string, Panel*> panel : panels)
        panel.second->RenderUI();
}

void UIManager::AddPanel(string key, Panel* panel)
{
    if (panels.count(key) > 0) return;

    panel->SetTag(key);
    panel->Load();
    panels[key] = panel;
}

void UIManager::AddPanel(string key, wstring panelTextureFile, wstring cancelBtnTextureFile)
{
    if (panels.count(key) > 0) return;

    Panel* panel = new Panel(panelTextureFile);
    panel->SetTag(key);
    panel->Load();

    panels[key] = panel;
}

void UIManager::Show(string key)
{
    if (panels.count(key) == 0) return;

    panels[key]->SetActive(true);

    popupList.push_back(panels[key]);

    frontPanel = panels[key];
}

void UIManager::Hide(string key)
{
    list<Panel*>::iterator iter = find(popupList.begin(), popupList.end(), panels[key]);

    if (iter == popupList.end())
        return;    

    popupList.erase(iter);    

    if (frontPanel == panels[key])
    {
        if (popupList.empty())
            frontPanel = nullptr;
        else
            frontPanel = popupList.back();
    }
}

void UIManager::CloseLastUI()
{
    if (KEY_DOWN(VK_ESCAPE))
    {
        if (!popupList.empty())
        {
            popupList.pop_back();

            if (popupList.empty())
                frontPanel = nullptr;
            else
                frontPanel = popupList.back();
        }
    }
}
