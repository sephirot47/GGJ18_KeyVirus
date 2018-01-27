#include "Splash.h"

void Splash::OnStart()
{
    Behaviour::OnStart();

    m_originalColor = isShiftVirus ? Color::White : Color::Green;   
    m_originalSize = GetGameObject()->GetTransform()->GetScale().Length();
    Debug_Peek( GetGameObject()->GetTransform()->GetLocalScale() );
}

void Splash::OnUpdate()
{
    Behaviour::OnUpdate();
 
    m_elapsedTime += Time::GetDeltaTime() * 0.1f;
    float size = 0.5f - m_elapsedTime;
    
    GetGameObject()->GetTransform()->SetScale(m_originalSize * size);
    
    if (size <= 0.0f) { GameObject::Destroy( GetGameObject() ); }
}

BANG_BEHAVIOUR_CLASS_IMPL(Splash);
