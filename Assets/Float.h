#include "Bang/Behaviour.h"

USING_NAMESPACE_BANG

class Float : public Behaviour
{
    COMPONENT(Float);

public:
    Float() = default;
    virtual ~Float() = default;

    void OnStart() override;
    void OnUpdate() override;

private:
    float m_time = 0.0f;
    float m_freq = 0.0f;
    Vector3 m_originalPosition;
};

BANG_BEHAVIOUR_CLASS(Float);
