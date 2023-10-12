#include "Framework.h"

void RenderManager::Render()
{
    sort(objects.begin(), objects.end(), GameObject::CompareObject);

    for (GameObject* object : objects)
        object->Render();
}
