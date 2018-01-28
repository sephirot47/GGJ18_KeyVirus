#include "Intro.h"

#include "Bang/UICanvas.h"
#include "Bang/RectTransform.h"
#include "Bang/GameObjectFactory.h"

void Intro::OnStart()
{
    Behaviour::OnStart();

    Scene *scene = GetGameObject()->GetScene();
    UICanvas *canvas = GameObjectFactory::CreateUICanvas();

    p_imgRend = GameObjectFactory::CreateUIImage();
    p_imgRend->SetImageTexture( PPATH("LogoBang_2048.png") );
    p_imgRend->GetGameObject()->GetRectTransform()->
            SetAnchors(Vector2::Zero, Vector2::Zero);
    p_imgRend->GetGameObject()->GetRectTransform()->SetMargins(
                -420, -150, -420, -150);

    canvas->GetGameObject()->SetParent(scene);
    p_imgRend->GetGameObject()->SetParent(canvas->GetGameObject());
}

void Intro::OnUpdate()
{
    Behaviour::OnUpdate();

    m_time += Time::GetDeltaTime();
    double StartFadeTime = IntroTime/2;
    if (m_time >= IntroTime)
    {
        SceneManager::LoadScene( PPATH("Menu.bscene") );
    }
    else if (m_time >= (StartFadeTime))
    {
        p_imgRend->SetTint(
          Color::White.WithAlpha(1.0 - ((m_time-StartFadeTime) /
                                        (IntroTime-StartFadeTime))));
    }

}

BANG_BEHAVIOUR_CLASS_IMPL(Intro);
