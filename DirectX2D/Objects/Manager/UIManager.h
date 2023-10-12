#pragma once

class UIManager : public Singleton<UIManager>
{
private:
    friend class Singleton;

    UIManager();
    ~UIManager();

public:
    void Update();
    void Render();

    void AddPanel(string key, Panel* panel);
    void AddPanel(string key, wstring panelTextureFile,
        wstring cancelBtnTextureFile = L"Textures/UI/Cancel.png");

    void Show(string key);
    void Hide(string key);

    Panel* GetFrontPanel() { return frontPanel; }

private:
    void CloseLastUI();

private:
    map<string, Panel*> panels;
    list<Panel*> popupList;

    Panel* frontPanel = nullptr;
};