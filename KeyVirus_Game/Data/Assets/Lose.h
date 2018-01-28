#include "Bang/Behaviour.h"

USING_NAMESPACE_BANG

class Lose : public Behaviour
{
    COMPONENT(Lose);

public:
    static double s_lastedTime;

    Lose() = default;
    virtual ~Lose() = default;

    void OnStart() override;
    void OnUpdate() override;
};

BANG_BEHAVIOUR_CLASS(Lose);
