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
    double m_appearPeriod = 2.0;
    double m_timeSinceLastAppear = m_appearPeriod;
    double m_time = 0.0;
    double m_lostTime = 0.0;

    Map<Key, String> KeyCodesToKeyName;
    Map<String, Key> KeyNameToKeyCodes;
   
    RH<Prefab> m_virusPrefab;
    Map<String, GameObject*> m_keyToVirus;
};

BANG_BEHAVIOUR_CLASS(Core);
