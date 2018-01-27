#include "Core.h"

void Core::OnStart()
{
    Behaviour::OnStart();

    KeyCodesToKeyName.Add(Key::A, "A"); KeyNameToKeyCodes.Add("A", Key::A);
    KeyCodesToKeyName.Add(Key::B, "B"); KeyNameToKeyCodes.Add("B", Key::B);
    KeyCodesToKeyName.Add(Key::C, "C"); KeyNameToKeyCodes.Add("C", Key::C);
    KeyCodesToKeyName.Add(Key::D, "D"); KeyNameToKeyCodes.Add("D", Key::D);
    KeyCodesToKeyName.Add(Key::E, "E"); KeyNameToKeyCodes.Add("E", Key::E);
    KeyCodesToKeyName.Add(Key::F, "F"); KeyNameToKeyCodes.Add("F", Key::F);
    KeyCodesToKeyName.Add(Key::G, "G"); KeyNameToKeyCodes.Add("G", Key::G);
    KeyCodesToKeyName.Add(Key::H, "H"); KeyNameToKeyCodes.Add("H", Key::H);
    KeyCodesToKeyName.Add(Key::I, "I"); KeyNameToKeyCodes.Add("I", Key::I);
    KeyCodesToKeyName.Add(Key::J, "J"); KeyNameToKeyCodes.Add("J", Key::J);
    KeyCodesToKeyName.Add(Key::K, "K"); KeyNameToKeyCodes.Add("K", Key::K);
    KeyCodesToKeyName.Add(Key::L, "L"); KeyNameToKeyCodes.Add("L", Key::L);
    KeyCodesToKeyName.Add(Key::M, "M"); KeyNameToKeyCodes.Add("M", Key::M);
    KeyCodesToKeyName.Add(Key::N, "N"); KeyNameToKeyCodes.Add("N", Key::N);
    KeyCodesToKeyName.Add(Key::O, "O"); KeyNameToKeyCodes.Add("O", Key::O);
    KeyCodesToKeyName.Add(Key::P, "P"); KeyNameToKeyCodes.Add("P", Key::P);
    KeyCodesToKeyName.Add(Key::Q, "Q"); KeyNameToKeyCodes.Add("Q", Key::Q);
    KeyCodesToKeyName.Add(Key::R, "R"); KeyNameToKeyCodes.Add("R", Key::R);
    KeyCodesToKeyName.Add(Key::S, "S"); KeyNameToKeyCodes.Add("S", Key::S);
    KeyCodesToKeyName.Add(Key::T, "T"); KeyNameToKeyCodes.Add("T", Key::T);
    KeyCodesToKeyName.Add(Key::U, "U"); KeyNameToKeyCodes.Add("U", Key::U);
    KeyCodesToKeyName.Add(Key::V, "V"); KeyNameToKeyCodes.Add("V", Key::V);
    KeyCodesToKeyName.Add(Key::W, "W"); KeyNameToKeyCodes.Add("W", Key::W); 
    KeyCodesToKeyName.Add(Key::X, "X"); KeyNameToKeyCodes.Add("X", Key::X); 
    KeyCodesToKeyName.Add(Key::Y, "Y"); KeyNameToKeyCodes.Add("Y", Key::Y); 
    KeyCodesToKeyName.Add(Key::Z, "Z"); KeyNameToKeyCodes.Add("Z", Key::Z); 

    // This code is executed once when the Behaviour is started
    m_virusPrefab = Resources::Load<Prefab>("Virus.bprefab");

    GameObject *keysLocation = GameObject::Find("KeysLocation");
    for (GameObject *keyLocation : keysLocation->GetChildren())
    {
        if (Random::GetValue() > 0.2f) { continue; }

        GameObject *virus = m_virusPrefab.Get()->Instantiate();
        Vector3 keyPosition = keyLocation->GetTransform()->GetPosition();
        virus->GetTransform()->SetPosition( keyPosition );
        virus->SetParent( SceneManager::GetActiveScene() );
        m_keyToVirus.Add(keyLocation->GetName(), virus);
    }
}

void Core::OnUpdate()
{
    Behaviour::OnUpdate();

    // This code is executed every frame
    const Array<Key>& keysDown = Input::GetKeysDown();
    for (Key k : keysDown)
    { 
        if (!KeyCodesToKeyName.ContainsKey(k)) { continue; }
        
        String keyName = KeyCodesToKeyName[k];
        if (m_keyToVirus.ContainsKey(keyName))
        {
            GameObject *virus = m_keyToVirus.Get(keyName);
            GameObject::Destroy(virus);
            m_keyToVirus.Remove(keyName);
        }
    }
}

BANG_BEHAVIOUR_CLASS_IMPL(Core);
