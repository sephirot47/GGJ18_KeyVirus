#include "Rotate.h"

void Rotate::OnStart()
{
    Behaviour::OnStart();

    // This code is executed once when the Behaviour is started
}

void Rotate::OnUpdate()
{
    Behaviour::OnUpdate();

    // This code is executed every frame
    Quaternion rot = Quaternion::AngleAxis(Time::GetDeltaTime() * 3.0f, Vector3::Up);
    GetGameObject()->GetTransform()->RotateLocal(rot);
}

BANG_BEHAVIOUR_CLASS_IMPL(Rotate);
