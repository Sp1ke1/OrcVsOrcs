#include "RangeEnemy.h"
#include "../Bonuses/BonusManager.h"
#include "../../Components/Animations/CharacterAnimationComponent.h"
#include "../../Components/Attack/EnemyRangeAttackComponent.h"
#include "../../../GameEngine.h"

/**
 * @brief class to spawn new enemies, send messages to other systems and delete killed enemies
 */
class EnemyManager : public Actor {
public:
    /**
     * @Brief Creates new instance of the object
     * @param id Object unique identifier
     * @param map_layout map layout for spawning air enemies
     * @param playerBonusManager to send messages for spawning new bonuses
     * @param AirEnemyAnimations textures to animate air enemies
     * @param enemiesAnimations textures to animatie ground enemies
     * @param bulletTexture texture of enemies attack particle
     */
    EnemyManager (
            uint32_t id,
            uint32_t SpawnCoolDown,
            const std::shared_ptr<BonusManager> & playerBonusManager,
            const std::vector<std::shared_ptr<Texture>> & AirEnemyAnimations,
            const std::vector<std::shared_ptr<Texture>> & enemiesAnimations,
            const std::shared_ptr<Texture> & bulletTexture
    );
    /**
     * @brief default Destructor
    */
    ~EnemyManager() {
        for ( auto & enemy : m_AirEnemiesAlive )
        {
            enemy -> GetComponents() . clear();
        }
        for ( auto & enemy : m_EnemiesAlive )
        {
            enemy -> GetComponents() . clear();
        }
    };
    /**
     * @brief Tick method. Called every frame by engine.
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
    void ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel, const std::pair<int, int> &ResolveVector) override;
    /**
     * @brief Method to handle enemy death ( remove it from game and send messages to other systems )
     * @param EnemyID id of killed enemy
     */
    void OnEnemyDeath ( uint32_t EnemyID );
    /**
     * @brief Checks if there are any air enemy alive
     * @return is there any air enemy
     */
    bool isAnyAirEnemyAlive () const { return !m_AirEnemiesAlive . empty(); }
    void Init( const std::vector<std::vector<int>> & map_layout );
    std::vector<std::shared_ptr<Enemy>> m_AirEnemiesAlive;
private:
    /**
     * @brief method to spawn new ground enemy at random location on the ground
     */
    void SpawnGroundEnemy();
    /**
     * Method to spawn new air enemy ( calls in constructor )
     * @param i number of raw in the layout
     * @param j number of colomn in the layout
     */
    void SpawnAirEnemy ( size_t i, size_t j );
    std::shared_ptr<BonusManager> m_PlayerBonusManager;
    std::vector<std::shared_ptr<Enemy>> m_EnemiesAlive;
    
    const std::vector<std::shared_ptr<Texture>>  m_AirEnemiesAnimations;
    const std::vector<std::shared_ptr<Texture>>  m_GroundEnemiesAnimations;
    uint32_t m_SpawnCoolDown;
    const std::shared_ptr<Texture> m_BulletTexture;
    uint32_t m_TargetSpawnTick;
};
