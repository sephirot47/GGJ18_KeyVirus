#include "Bang/Behaviour.h"

USING_NAMESPACE_BANG

class Rotate : public Behaviour
{
    COMPONENT(Rotate);

public:
    Rotate() = default;
    virtual ~Rotate() = default;

    void OnStart() override;
    void OnUpdate() override;
};

BANG_BEHAVIOUR_CLASS(Rotate);
