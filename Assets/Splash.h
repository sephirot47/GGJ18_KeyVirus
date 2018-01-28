#include "Bang/Behaviour.h"

USING_NAMESPACE_BANG

class Splash : public Behaviour
{
    COMPONENT(Splash);

public:
    Color color;

    Splash() = default;
    virtual ~Splash() = default;

    void OnStart() override;
    void OnUpdate() override;

private:
    double m_originalSize;
    double m_elapsedTime = 0.0;
};

BANG_BEHAVIOUR_CLASS(Splash);
