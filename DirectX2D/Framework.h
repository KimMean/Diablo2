#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 960
#define WIN_HEIGHT 720

#define WIN_START_X 100
#define WIN_START_Y 100

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#define DELTA Timer::Get()->GetElapsedTime()

#define CAM Environment::Get()->GetMainCamera()

#define DIALOG ImGuiFileDialog::Instance()

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <list>
#include <unordered_set>
#include <functional>
#include <thread>
#include <mutex>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//DirectXTex
#include <DirectXTex.h>

#pragma comment(lib, "DirectXTex.lib")

//ImGui
#include <ImGui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <dirent/dirent.h>
#include <ImGuiFileDialog.h>
#include <ImGuiFileDialogConfig.h>

#pragma comment(lib, "ImGui.lib")

//DirectWrite
#include <d2d1_2.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

//FMOD Library
#include "Libraries/inc/fmod.hpp"
#pragma comment(lib, "Libraries/Lib/fmod_vc.lib")

using namespace std;
using namespace DirectX;

typedef unsigned int UINT;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;

typedef function<void()> Event;
typedef function<void(void*)> ParamEvent;
typedef function<void(int)> IntParamEvent;

//Framework Header

#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Keyboard.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Observer.h"
#include "Framework/Utilities/tinyxml2.h"
#include "Framework/Utilities/Font.h"
#include "Framework/Utilities/BinaryReader.h"
#include "Framework/Utilities/BinaryWriter.h"
#include "Framework/Utilities/Audio.h"

using namespace Utility;

#include "Framework/Math/Vector2.h"
#include "Framework/Math/GameMath.h"
#include "Framework/Math/Transform.h"

using namespace GameMath;

#include "Framework/System/Device.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/VertexLayouts.h"
#include "Framework/Buffer/GlobalBuffer.h"

#include "Framework/Render/Texture.h"
#include "Framework/Render/Frame.h"
#include "Framework/Render/Clip.h"
#include "Framework/Render/RenderTarget.h"

#include "Framework/Collision/Collider.h"
#include "Framework/Collision/RectCollider.h"
#include "Framework/Collision/CircleCollider.h"
#include "Framework/Collision/LineCollider.h"

#include "Framework/Environment/Camera.h"
#include "Framework/Environment/Environment.h"


#include "Objects/Algorithm/Node.h"
#include "Objects/Algorithm/Heap.h"
#include "Objects/Algorithm/AStar.h"

//Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Quad.h"
#include "Objects/Basic/Action.h"
#include "Objects/Basic/Effect.h"
#include "Objects/Basic/AnimObject.h"
#include "Objects/Basic/Particle.h"

#include "Objects/UI/Button.h"
#include "Objects/UI/Panel.h"
#include "Objects/UI/ImageFont.h"
#include "Objects/UI/ProgressBar.h"

#include "Objects/Manager/EffectManager.h"
#include "Objects/Manager/RenderManager.h"
#include "Objects/Manager/UIManager.h"

#include "Objects/Diablo/Tile.h"
#include "Objects/Diablo/Map.h"



#include "Objects/Diablo/Spells/Spell.h"
#include "Objects/Diablo/Spells/ColdSpell.h"
#include "Objects/Diablo/Spells/LightningSpell.h"
#include "Objects/Diablo/Spells/FireSpell.h"
#include "Objects/Diablo/Spells/FireBolt.h"
#include "Objects/Diablo/Spells/IceBolt.h"
#include "Objects/Diablo/Spells/FrozenOrb.h"
#include "Objects/Diablo/Spells/Spell_Icon.h"

#include "Objects/Diablo/Spells/DiaLightning.h"
#include "Objects/Diablo/Spells/DiaNova.h"

#include "Objects/Diablo/UI/ColdSpellTree.h"
#include "Objects/Diablo/UI/LightningSpellTree.h"
#include "Objects/Diablo/UI/FireSpellTree.h"
#include "Objects/Diablo/UI/SkillTree.h"

#include "Objects/Diablo/UI/Progress.h"
#include "Objects/Diablo/UI/Item.h"
#include "Objects/Diablo/UI/InventorySlot.h"
#include "Objects/Diablo/UI/Inventory.h"
#include "Objects/Diablo/UI/Status.h"
#include "Objects/Diablo/UI/BasicUI.h"


#include "Objects/Diablo/Monster/Monster.h"
#include "Objects/Diablo/Monster/Diablo/Diablo_Idle.h"
#include "Objects/Diablo/Monster/Diablo/Diablo_Walk.h"
#include "Objects/Diablo/Monster/Diablo/Diablo_Run.h"
#include "Objects/Diablo/Monster/Diablo/Diablo_Attack.h"
#include "Objects/Diablo/Monster/Diablo/Diablo_Lightning.h"
#include "Objects/Diablo/Monster/Diablo/Diablo_Fanaticism.h"
#include "Objects/Diablo/Monster/Diablo/Diablo_Hit.h"
#include "Objects/Diablo/Monster/Diablo/Diablo_Death.h"
#include "Objects/Diablo/Monster/Diablo/Diablo.h"

#include "Objects/Diablo/Character.h"
#include "Objects/Diablo/Sorceress/Sorceress_Idle.h"
#include "Objects/Diablo/Sorceress/Sorceress_Walk.h"
#include "Objects/Diablo/Sorceress/Sorceress_Run.h"
#include "Objects/Diablo/Sorceress/Sorceress_Cast.h"
#include "Objects/Diablo/Sorceress/Sorceress_Hit.h"
#include "Objects/Diablo/Sorceress/Sorceress.h"


#include "Objects/Diablo/Manager/SpellManager.h"


//Scene Header
#include "Scenes/Scene.h"
#include "Manager/GameManager.h"

extern HWND hWnd;
extern Vector2 mousePos;
extern float mouseWheel;
extern bool DebugMode;