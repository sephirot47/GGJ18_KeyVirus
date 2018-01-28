#include "Bang/Behaviour.h"

USING_NAMESPACE_BANG

class Virus : public Behaviour
{
    COMPONENT(Virus);

public:
    Color color;
    bool dying = false;
    int virusType = 0;
    bool zombie = false;
    float scaleFactor = 1.0f;
    double deadTime = 0;
    Vector3 originalPosition = Vector3::Zero;

    Virus() = default;
    virtual ~Virus() = default;

    void OnStart() override;
    void OnUpdate() override;

    void DestroySelf();

private:
    Vector3 originalLocalScale = Vector3::Zero;
};

BANG_BEHAVIOUR_CLASS(Virus);
