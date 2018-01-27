#include "Bang/Behaviour.h"

USING_NAMESPACE_BANG

class Core : public Behaviour
{
    COMPONENT(Core);

public:
    Core() = default;
    virtual ~Core() = default;

    void OnStart() override;
    void OnUpdate() override;
 
private:
    RH<Prefab> m_virusPrefab;
};

BANG_BEHAVIOUR_CLASS(Core);
