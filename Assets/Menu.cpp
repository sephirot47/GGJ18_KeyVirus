#include "Menu.h"

void Menu::OnStart()
{
    Behaviour::OnStart();

    // This code is executed once when the Behaviour is started
}

void Menu::OnUpdate()
{
    Behaviour::OnUpdate();

    if (Input::GetKeyDown(Key::Space))
    {
        SceneManager::LoadScene( PPATH("Game.bscene") );
    }
}

BANG_BEHAVIOUR_CLASS_IMPL(Menu);
