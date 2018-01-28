#include "Float.h"

void Float::OnStart()
{
    Behaviour::OnStart();

    m_originalPosition = GetGameObject()->GetTransform()->GetPosition();
    m_time = Random::GetValue() * 5.0f;
    m_freq = Random::GetValue() + 0.5f;
}

void Float::OnUpdate()
{
    Behaviour::OnUpdate();

    m_time += Time::GetDeltaTime();

    Vector3 disp = Vector3::Up;
    disp *= Math::Sin( m_time * m_freq );
    disp *= 0.7f;

    GetGameObject()->GetTransform()->SetPosition( m_originalPosition + disp );
}

BANG_BEHAVIOUR_CLASS_IMPL(Float);
