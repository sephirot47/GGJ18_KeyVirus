#include "Bang/Behaviour.h"

USING_NAMESPACE_BANG

class Menu : public Behaviour
{
    COMPONENT(Menu);

public:
    Menu() = default;
    virtual ~Menu() = default;

    void OnStart() override;
    void OnUpdate() override;
};

BANG_BEHAVIOUR_CLASS(Menu);
