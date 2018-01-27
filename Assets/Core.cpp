#include "Core.h"

#include "BangEditor/EditorPaths.h"

void Core::OnStart()
{
    Behaviour::OnStart();

    // This code is executed once when the Behaviour is started
    m_virusPrefab = Resources::Load<Prefab>( PPATH("Virus.bprefab") );

    GameObject *keysLocation = GameObject::Find("KeysLocation");
    for (GameObject *keyLocation : keysLocation->GetChildren())
    {
        GameObject *virus = m_virusPrefab.Get()->Instantiate();
        Vector3 keyPosition = keyLocation->GetTransform()->GetPosition();
        virus->GetTransform()->SetPosition( keyPosition );
        virus->SetParent( SceneManager::GetActiveScene() );
    }
}

void Core::OnUpdate()
{
    Behaviour::OnUpdate();

    // This code is executed every frame
}

BANG_BEHAVIOUR_CLASS_IMPL(Core);
