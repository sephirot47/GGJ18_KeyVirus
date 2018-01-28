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
    Color color;
    int virusType = 0;
};

BANG_BEHAVIOUR_CLASS(Virus);
