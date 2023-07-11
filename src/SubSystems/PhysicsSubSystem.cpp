#include "PhysicsSubSystem.h"
#include <iostream>

void PhysicsSubSystem::Destroy()
{
	m_CollisionQuery . clear(); 
	m_ActorsPendingSpawn . clear(); 
}


bool PhysicsSubSystem::DestroyActor(uint32_t ObjectID) {
    for ( auto x = m_CollisionQuery.begin(); x != m_CollisionQuery . end(); ++ x ) {
        if ( (*x) -> GetObjectID() == ObjectID ) {
            ( *x ) -> SetPendingKill();
            for ( auto & comp : (*x) -> GetComponents() )
            {
            	comp -> SetPendingKill ();  
            }
            return true;
        }
    }
    for ( auto y = m_ActorsPendingSpawn . begin(); y != m_ActorsPendingSpawn . end(); ++ y ) { 
        if ( (*y) -> GetObjectID() == ObjectID ) {
            (*y) -> SetPendingKill();
            for ( auto & comp : (*y) -> GetComponents() )
            {
                comp -> SetPendingKill();
            }
            return true;
        }
    }
    return false;
}

bool PhysicsSubSystem::RegisterActor(const std::shared_ptr<Actor> &actor) {
   for ( auto & x : m_CollisionQuery )
       if ( x -> GetObjectID() == actor -> GetObjectID() )
           return false;
   for ( auto & y : m_ActorsPendingSpawn )
        if ( y -> GetObjectID () == actor -> GetObjectID() ) { 
            return false;
        }
   m_ActorsPendingSpawn . push_back ( actor );
   return true;
}

bool PhysicsSubSystem::RegisterComponent(const std::shared_ptr<ActorComponent> &component) {
    return false;
}

void PhysicsSubSystem::Update() {
    GarbageCollect();
    HandleSpawnQueue();
    for ( size_t i = 0; i < m_CollisionQuery . size(); i ++ )
        for ( size_t j = 0; j < m_CollisionQuery . size(); j ++ )
        {
            if ( i == j )
                continue;
            if ( m_CollisionQuery [ i ] && m_CollisionQuery [ i ] -> GetCollisionEnabled()  )
            {
                std::pair<int,int> ResolveVector;
                if ( CheckCollisionWithWorld( m_CollisionQuery [ i ] -> GetPhysicsBody(), ResolveVector ) )
                {
                    m_CollisionQuery[i]->ReactToCollision(std::shared_ptr<Actor>(), EWorld, ResolveVector);
                    for ( auto & x : m_CollisionQuery [ i ] -> GetComponents() )
                    {
                        x->ReactToCollision(std::shared_ptr<Actor>(), EWorld, ResolveVector);
                    }
                    break;
                }
                else if ( m_CollisionQuery [ j ] && m_CollisionQuery [ j ] -> GetCollisionEnabled() && CheckCollisions( m_CollisionQuery [ i ] -> GetPhysicsBody(), m_CollisionQuery [ j ] -> GetPhysicsBody(), ResolveVector ) )
                {
                    m_CollisionQuery[i]->ReactToCollision(m_CollisionQuery[j], m_CollisionQuery [ j ] -> GetCollisionChannel(), ResolveVector);
                    m_CollisionQuery[j]->ReactToCollision(m_CollisionQuery[i], m_CollisionQuery [ i ] -> GetCollisionChannel(),
                                                          std::pair<int, int>(ResolveVector.first * -1,
                                                                              ResolveVector.second * -1));
                    for ( auto & x : m_CollisionQuery [ i ] -> GetComponents() )
                    {
                        x->ReactToCollision(std::shared_ptr<Actor>(), EWorld, ResolveVector);
                    }
                    for ( auto & x : m_CollisionQuery [ j ] -> GetComponents() )
                    {

                        ResolveVector . first *= -1; ResolveVector . second *= -1;
                        x->ReactToCollision(m_CollisionQuery[i], EWorld, ResolveVector);
                    }
                    break;
                }
            }
        }
}

bool PhysicsSubSystem::Init() {
    return true;
}

bool PhysicsSubSystem::CheckCollisionWithWorld( const SDL_Rect & physicsBody, std::pair<int,int> & ResolveVector ) {
    bool isCollision = false;
    if ( physicsBody.x < 0 ){
        ResolveVector . first = 1;
        isCollision = true;
    }
    else if ( physicsBody.x > (int)m_GameWidth - physicsBody.w )
    {
        ResolveVector . first = -1;
        isCollision = true;
    }
    if ( physicsBody.y + physicsBody.h > (int)m_GroundLvl )
    {
        ResolveVector . second = 1;
        isCollision = true;
    }
    else if ( physicsBody.y - physicsBody.h < (int)m_GameHeight )
    {
        ResolveVector . second = -1;
        isCollision = true;
    }
    if ( isCollision )
        return true;
    ResolveVector = std::pair<int,int> ( 0, 0 );
    return false;
}

bool PhysicsSubSystem::CheckCollisions(const SDL_Rect & x, const SDL_Rect &y, std::pair<int, int> &ResolveVector) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = x.x;
    rightA = x.x + x.w;
    topA = x.y;
    bottomA = x.y + x.h;

    leftB = y.x;
    rightB = y.x + y.w;
    topB = y.y;
    bottomB = y.y + y.h;

    if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB )
        return false;
    return true;
}

void PhysicsSubSystem::GarbageCollect() {
    for ( uint32_t i = 0; i < m_CollisionQuery . size() ; i++  )
        if ( m_CollisionQuery[i] -> GetPendingKill() )
        {
            m_CollisionQuery . erase ( m_CollisionQuery . begin() + i );
            return;
        }

}

void PhysicsSubSystem::HandleSpawnQueue() {
    if ( m_ActorsPendingSpawn . empty() )
        return;
    m_CollisionQuery . push_back ( m_ActorsPendingSpawn . front() );
    m_ActorsPendingSpawn . pop_front();
    HandleSpawnQueue();
}
