#include "Splash.h"

void Splash::OnStart()
{
    Behaviour::OnStart();

    m_originalSize = GetGameObject()->GetTransform()->GetLocalScale().Length();

    List<MeshRenderer*> mrs = GetGameObject()->GetComponentsInChildren<MeshRenderer>();
    for  (MeshRenderer *mr : mrs)
    {
        mr->GetMaterial()->SetDiffuseColor(color);
        mr->SetEnabled(true);
    }

    GetGameObject()->SetVisible(true);
}

void Splash::OnUpdate()
{
    Behaviour::OnUpdate();

    m_elapsedTime += Time::GetDeltaTime() * 0.1f;
    float size = 0.5f - m_elapsedTime;
    
    GetGameObject()->GetTransform()->SetLocalScale(m_originalSize * size);
    
    if (size <= 0.0f) { GameObject::Destroy( GetGameObject() ); }
}

BANG_BEHAVIOUR_CLASS_IMPL(Splash);
