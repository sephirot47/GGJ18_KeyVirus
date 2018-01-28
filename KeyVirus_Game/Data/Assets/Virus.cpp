#include "Virus.h"

#include "Splash.h"
#include "Bang/AudioSource.h"

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

    if (originalPosition == Vector3::Zero)
    { originalPosition = GetGameObject()->GetTransform()->GetPosition(); }

    if (!zombie)
    {
        Quaternion rot = Quaternion::AngleAxis(Time::GetDeltaTime() * 3.0f, Vector3::Up);
        GetGameObject()->GetTransform()->RotateLocal(rot);
    }
    GetGameObject()->GetTransform()->SetLocalScale(originalLocalScale * scaleFactor);

    if (dying)
    {
        deadTime += Time::GetDeltaTime();
        if (deadTime >= 4.0f)
        {
            GameObject::Destroy( GetGameObject() );
        }
    }
}

void Virus::DestroySelf()
{
    RH<Prefab> splashPrefab = Resources::Load<Prefab>("Splash.bprefab");
    Resources::SetPermanent(splashPrefab.Get(), true);

    GameObject *splashGO = splashPrefab.Get()->Instantiate();
    Splash *splash = splashGO->GetComponent<Splash>();
    if (splash)
    {
        GetGameObject()->GetComponent<AudioSource>()->Play();
        GetGameObject()->SetVisible(false);

        splashGO->SetVisible(false);
        splashGO->GetTransform()->SetPosition(
                    GetGameObject()->GetTransform()->GetPosition() );
        splash->color = color;
        dying = true;
    }
}

BANG_BEHAVIOUR_CLASS_IMPL(Virus);
