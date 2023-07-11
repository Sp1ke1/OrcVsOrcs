//
// Created by Черкасов Андрей on 14.05.2022.
//

#include "InputManager.h"


void InputManager::Process() {
    SDL_Event e;
    SDL_PollEvent( &e );
    switch (e.type)
    {
        case SDL_QUIT:
            m_State = State::EXIT;
            break;
        case SDL_KEYDOWN:
            ProcessKeyDown(e.key.keysym.sym);
            break;
        case SDL_KEYUP:
            ProcessKeyUp(e.key.keysym.sym);
            break;
        default:
            break;
    }
}

void InputManager::ProcessKeyDown(const SDL_Keycode &key) {
    switch (key)
    {
        case SDLK_LEFT:
            m_KeyMap[KEY_LEFT] = true;
            break;
        case SDLK_RIGHT:
            m_KeyMap[KEY_RIGHT] = true;
            break;
        case SDLK_UP:
            m_KeyMap[KEY_UP] = true;
            break;
        case SDLK_SPACE:
            m_KeyMap[KEY_SPACE] = true;
            break;
        case SDLK_ESCAPE:
            m_KeyMap[KEY_ESCAPE] = true;
            break;
        case SDLK_s:
            m_KeyMap[KEY_S] = true;
            break;
        default:
            break;
    }
}

void InputManager::ProcessKeyUp(const SDL_Keycode &key) {
    switch (key)
    {
        case SDLK_LEFT:
            m_KeyMap[KEY_LEFT] = false;
            break;
        case SDLK_RIGHT:
            m_KeyMap[KEY_RIGHT] = false;
            break;
        case SDLK_UP:
            m_KeyMap[KEY_UP] = false;
            break;
        case SDLK_SPACE:
            m_KeyMap[KEY_SPACE] = false;
            break;
        case SDLK_ESCAPE:
            m_KeyMap[KEY_ESCAPE] = false;
            m_State = State::EXIT;
            break;
        case SDLK_s:
            m_KeyMap[KEY_S] = false;
            break;
        default:
            break;
    }
}


