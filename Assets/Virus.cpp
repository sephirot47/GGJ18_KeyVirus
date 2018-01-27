#include "Virus.h"

#include "Splash.h"

void Virus::OnStart()
{
    Behaviour::OnStart();

    isShiftVirus = Random::GetValue() > 0.5f;

    Color color = isShiftVirus ? Color::White : Color::Green;

    List<MeshRenderer*> mrs = GetGameObject()->GetComponents<MeshRenderer>();
    for (MeshRenderer *mr : mrs)
    {
        mr->GetMaterial()->SetDiffuseColor( color );
    }
}

void Virus::OnUpdate()
{
    Behaviour::OnUpdate();

    Quaternion rot = Quaternion::AngleAxis(Time::GetDeltaTime() * 3.0f, Vector3::Up);
    GetGameObject()->GetTransform()->RotateLocal(rot);
}

void Virus::OnDestroy()
{
    RH<Prefab> splashPrefab = Resources::Load<Prefab>("Splash.bprefab");

    GameObject *splashGO = splashPrefab.Get()->Instantiate();
    Splash *splash = splashGO->GetComponent<Splash>();
    if (splash)
    { 
        splash->isShiftVirus = isShiftVirus;
    }
}


BANG_BEHAVIOUR_CLASS_IMPL(Virus);
