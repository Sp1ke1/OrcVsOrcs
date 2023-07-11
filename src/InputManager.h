#pragma once
#include <SDL2/SDL.h>
#include <vector>
/**
 * @brief class to handle SDL events
 */
class InputManager {
public:
    /**
     * @brief creates a new instance of the object
     */
    InputManager()
    {
        for ( int i = 0; i < KEYS_COUNT; ++i )
            m_KeyMap . push_back ( false );
    };
    
    ~InputManager() = default;
    /**
     * @brief Processes SDL events and updates intternal map
     */
    void Process();
    /**
     * @brief state of input handler
     */
    enum State { RUNNING, EXIT };
    /**
     * @brief keys used by game
     */
    enum Keys { KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_SPACE, KEY_S, KEY_ESCAPE, KEYS_COUNT };
    /**
     * @brief getter for input handler state
     * @return state
     */
    State GetState () const { return m_State; }
    /**
     * gets if left arrow is pressed
     * @return is pressed
     */
    bool isLeftPressed () const { return m_KeyMap[KEY_LEFT]; }
    /**
     * gets if right arrow is pressed
     * @return is pressed
     */
    bool isRightPressed() const { return m_KeyMap[KEY_RIGHT]; }
    /**
     * gets if attack button is pressed
     * @return space is pressed
     */
    bool isAttackPressed () const { return m_KeyMap[KEY_SPACE]; }
    /**
     * gets if jump pressed
     * @return arrow up is pressed
     */
    bool isJumpPressed () const { return m_KeyMap[KEY_UP]; }
    /**
     * gets if super power is pressed
     * @return S is pressed
     */
    bool isSuperPressed () const { return m_KeyMap [ KEY_S ]; }
private:
    State m_State = RUNNING;
    std::vector <bool> m_KeyMap;
    void ProcessKeyDown ( const SDL_Keycode & key);
    void ProcessKeyUp ( const SDL_Keycode & key );
};
