#include "Bang/Behaviour.h"

USING_NAMESPACE_BANG

class Virus : public Behaviour
{
    COMPONENT(Virus);

public:
    Color color;
    int virusType = 0;
    float scaleFactor = 1.0f;

    Virus() = default;
    virtual ~Virus() = default;

    void OnStart() override;
    void OnUpdate() override;
    void OnDestroy() override;

private:
    Vector3 originalLocalScale = Vector3::Zero;
};

BANG_BEHAVIOUR_CLASS(Virus);
