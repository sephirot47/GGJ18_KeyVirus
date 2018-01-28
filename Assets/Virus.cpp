#include "Virus.h"

#include "Splash.h"

void Virus::OnStart()
{
    Behaviour::OnStart();

    virusType = Random::GetRange(0, 3);

    if (virusType == 0) { color = Color(1.0f, 0.55f, 0.6f);   }
    if (virusType == 1) { color = Color::Green; }
    if (virusType == 2) { color = Color(0.5f, 0.6f, 1.0f);  }

    List<MeshRenderer*> mrs = GetGameObject()->GetComponentsInChildren<MeshRenderer>();
    for (MeshRenderer *mr : mrs)
    {
        if (mr->GetMaterial()->GetTexture() != nullptr) // Only change body color
        {
            mr->GetMaterial()->SetDiffuseColor( color );
        }
    }

    originalLocalScale = GetGameObject()->GetTransform()->GetLocalScale();
}

void Virus::OnUpdate()
{
    Behaviour::OnUpdate();

    Quaternion rot = Quaternion::AngleAxis(Time::GetDeltaTime() * 3.0f, Vector3::Up);
    GetGameObject()->GetTransform()->RotateLocal(rot);
    GetGameObject()->GetTransform()->SetLocalScale(originalLocalScale * scaleFactor);
}

void Virus::OnDestroy()
{
    RH<Prefab> splashPrefab = Resources::Load<Prefab>("Splash.bprefab");

    GameObject *splashGO = splashPrefab.Get()->Instantiate();
    Splash *splash = splashGO->GetComponent<Splash>();
    if (splash)
    { 
        splashGO->SetVisible(false);
        splashGO->GetTransform()->SetPosition(
                    GetGameObject()->GetTransform()->GetPosition() );
        splash->color = color;
    }
}


BANG_BEHAVIOUR_CLASS_IMPL(Virus);
