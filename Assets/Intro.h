#include "Bang/Behaviour.h"

USING_NAMESPACE_BANG

class Intro : public Behaviour
{
    COMPONENT(Intro);

public:
    Intro() = default;
    virtual ~Intro() = default;

    void OnStart() override;
    void OnUpdate() override;

private:
    double m_time = 0.0f;
    double IntroTime = 5.0f;
    UIImageRenderer *p_imgRend = nullptr;
};

BANG_BEHAVIOUR_CLASS(Intro);
