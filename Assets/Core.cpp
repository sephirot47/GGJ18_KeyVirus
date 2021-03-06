#include "Core.h"

#include "Lose.h"
#include "Virus.h"

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

    m_virusPrefab = Resources::Load<Prefab>("Virus.bprefab");
    Resources::SetPermanent(m_virusPrefab.Get(), true);

    p_keyLocations = GameObject::Find("KeysLocation");
}

bool IsVirusColorOn(Virus *virus)
{
    bool isVirusColorOn = false;

    if (Input::GetKey(Key::LShift)) { isVirusColorOn = (virus->virusType == 1); }
    else if (Input::GetKey(Key::LCtrl)) { isVirusColorOn = (virus->virusType == 2); }
    else { isVirusColorOn = (virus->virusType == 0); }

    return isVirusColorOn;
}

void Core::OnUpdate()
{
    Behaviour::OnUpdate();

    m_timeSinceLastAppear += Time::GetDeltaTime();

    if (m_keyToVirus.Size() >= KeyNameToKeyCodes.Size())
    {
        Lose::s_lastedTime = m_time;
        m_lostTime += Time::GetDeltaTime();
        if (m_lostTime >= MaxLostTime)
        {
            SceneManager::LoadScene( PPATH("Lose.bscene") );
        }
        else
        {
            for (const auto &pair : m_keyToVirus)
            {
                GameObject *virusGO = pair.second;
                Virus *virus = virusGO->GetComponent<Virus>();
                virus->zombie = true;
                virus->scaleFactor = 1.0f;

                GameObject *camGo = Camera::GetActive()->GetGameObject();
                Vector3 camFwd = camGo->GetTransform()->GetForward();
                Quaternion nowQuat = virusGO->GetTransform()->GetRotation();
                Quaternion destQuat = Quaternion::LookDirection(camFwd);
                virusGO->GetTransform()->SetRotation(
                    Quaternion::SLerp(nowQuat, destQuat, Time::GetDeltaTime() * 1.2f));

                if (m_lostTime >= LostRotTime)
                {
                    Vector3 moveVector = (camGo->GetTransform()->GetPosition() -
                                          virus->originalPosition);
                    virusGO->GetTransform()->SetPosition(
                        virus->originalPosition +
                        moveVector * float((m_lostTime - LostRotTime) /
                                           (MaxLostTime - LostRotTime + 0.2f)));
                }
            }
        }
        return;
    }

    GameObject *timeTextGO = GameObject::Find("TimeText");
    if (timeTextGO)
    {
        UITextRenderer *timeText = timeTextGO->GetComponent<UITextRenderer>();
        m_time += Time::GetDeltaTime();
        timeText->SetContent( String::ToString(m_time, 2) );
    }

    if (m_timeSinceLastAppear >= m_appearPeriod)
    {
        m_appearPeriod = Math::Max(float(m_appearPeriod) * 0.95f, 0.3f);
        m_timeSinceLastAppear = 0.0;

        int i = 0;
        Array<int> freeKeyLocations;
        for (GameObject *kl : p_keyLocations->GetChildren())
        {
            if (!m_keyToVirus.ContainsKey(kl->GetName()))
            {
                freeKeyLocations.PushBack(i);
            }
            ++i;
        }

        if (!freeKeyLocations.IsEmpty())
        {
            int idx = freeKeyLocations[Random::GetRange(0, int(freeKeyLocations.Size()))];
            GameObject *keyLocation = p_keyLocations->GetChild(idx);

            GameObject *virus = m_virusPrefab.Get()->Instantiate();
            Vector3 keyPosition = keyLocation->GetTransform()->GetPosition();
            virus->GetTransform()->SetPosition( keyPosition );
            virus->SetParent( SceneManager::GetActiveScene() );
            m_keyToVirus.Add(keyLocation->GetName(), virus);
        }
    }

    for (const auto &pair : m_keyToVirus)
    {
        GameObject *virusGO = pair.second;
        Virus *virus = virusGO->GetComponent<Virus>();

        bool isVirusColorOn = IsVirusColorOn(virus);
        virus->scaleFactor = isVirusColorOn ? 1.4f : 1.0f;
    }

    Array<Key> keys = Input::GetPressedKeys();
    keys.PushBack( Input::GetKeysDown() );
    keys.PushBack( Input::GetKeysUp() );

    for (Key k : keys)
    { 
        if (!KeyCodesToKeyName.ContainsKey(k)) { continue; }
        
        String keyName = KeyCodesToKeyName[k];
        if (m_keyToVirus.ContainsKey(keyName))
        {
            GameObject *virusGO = m_keyToVirus.Get(keyName);
            Virus *virus = virusGO->GetComponent<Virus>();

            bool isVirusColorOn = IsVirusColorOn(virus);
            if (isVirusColorOn)
            {
                virus->DestroySelf();
                m_keyToVirus.Remove(keyName);
            }
        }
    }
}

BANG_BEHAVIOUR_CLASS_IMPL(Core);
