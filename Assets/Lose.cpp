#include "Lose.h"

double Lose::s_lastedTime = 0.0;

void Lose::OnStart()
{
    Behaviour::OnStart();
}

void Lose::OnUpdate()
{
    Behaviour::OnUpdate();

    GameObject *textGO = GameObject::Find("Text");
    if (textGO)
    {
        UITextRenderer *text = textGO->GetComponent<UITextRenderer>();
        text->SetContent("YOU LASTED   " + String::ToString(s_lastedTime, 2));
    }
}

BANG_BEHAVIOUR_CLASS_IMPL(Lose);
