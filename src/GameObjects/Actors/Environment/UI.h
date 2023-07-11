#pragma once
#include "../Player/PlayerCharacter.h"
#include "../Character.h"
/**
 * @brief class to render player score and hp
 */
class UI : public Actor {
public:
    /**
    * @brief Creates new instance of the object
    * @param HPBox box to render HP
    * @param ScoreBox box to render score points
    * @param playerRef reference to the player
    */
    UI (uint32_t id, const SDL_Rect & HPBox, const SDL_Rect & ScoreBox, const std::shared_ptr<PlayerCharacter> & playerRef );
    /**
     * @brief default destructor
     */
    ~UI() {};
    /**
     * @brief virtual Tick method. Called every frame by engine.
     * @param dt delta seconds elampes from last frame
    */
    void Tick ( float dt ) override;

    /**
     * @brief Render the object. Called every frame by engine
     * @param renderer Target renderer
     */
    void Render ( const Renderer & renderer ) const override;
    /**
     * @brief Method to react to collisions. Called by engine when collision found
     * @param otherActor collided with
     * @param CollisionChannel otherActor's collision channel
     * @param ResolveVector vector to go out of collision
     */
    void ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                  const std::pair<int, int> &ResolveVector) override;

private:
    std::string m_HPText;
    std::string m_ScoreText;

    const SDL_Rect m_HPBox;
    const SDL_Rect m_ScoreBox;
    const SDL_Color HPColor { 0, 255, 0 };
    const SDL_Color ScoreColor { 255, 255, 0};
    const std::shared_ptr<PlayerCharacter> m_PlayerRef;
};

