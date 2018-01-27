#include "Bang/Behaviour.h"

USING_NAMESPACE_BANG

class Virus : public Behaviour
{
    COMPONENT(Virus);

public:
    Virus() = default;
    virtual ~Virus() = default;

    void OnStart() override;
    void OnUpdate() override;
    void OnDestroy() override;

private:
    bool isShiftVirus = false;
};

BANG_BEHAVIOUR_CLASS(Virus);
