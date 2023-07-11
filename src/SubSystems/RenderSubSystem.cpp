
#include "RenderSubSystem.h"
#include <iostream>



void RenderSubSystem::Destroy()
{
	m_RenderTargets . clear(); 
	m_ActorsPendingSpawn . clear();
}

bool RenderSubSystem::DestroyActor(uint32_t ObjectID) {
    for ( auto elem = m_RenderTargets . begin(); elem != m_RenderTargets . end(); ++ elem )
    {
        if ( (*elem) -> GetObjectID() == ObjectID ) {
        	for ( auto & comp : (*elem) -> GetComponents() )
        	{
        		comp -> SetPendingKill (); 
        	}
            (*elem) -> SetPendingKill();
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

bool RenderSubSystem::RegisterActor(const std::shared_ptr<Actor> &actor) {
    for ( auto & x : m_RenderTargets )
    {
        if ( x -> GetObjectID() == actor -> GetObjectID() )
            return false;
    }
    for ( auto & y : m_ActorsPendingSpawn )
        if ( y -> GetObjectID () == actor -> GetObjectID() ) {
            return false;
        }
    m_ActorsPendingSpawn . push_back( actor );
    return true;
}

void RenderSubSystem::Update() {
    GarbageCollect();
    HandleSpawnQueue();
    for ( auto & x : m_RenderTargets )
    {
        x -> Render( *m_Renderer );
    }
    m_Renderer -> Present();
}

bool RenderSubSystem::Init() {
    try
    {
        m_Renderer = std::make_shared <Renderer> ();
        m_Renderer -> Init( GameStatics::APP_NAME,
                           GameStatics::RESOLUTION_X,
                           GameStatics::RESOLUTION_Y,
                           false );
    }
    catch ( const RendererException & error )
    {
        std::cout << error.GetMessage() << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool RenderSubSystem::RegisterComponent(const std::shared_ptr<ActorComponent> &component) {
    return false;
}

void RenderSubSystem::GarbageCollect() {
    std::vector<uint32_t> m_IndexesToDeleteActors;
    for ( uint32_t i = 0; i < m_RenderTargets . size() ; i++  )
        if ( m_RenderTargets [i] -> GetPendingKill() ) {
            m_RenderTargets.erase(m_RenderTargets.begin() + i );
            return;
        }
}

void RenderSubSystem::HandleSpawnQueue() {
    if ( m_ActorsPendingSpawn . empty() )
        return;
    m_RenderTargets . push_back ( m_ActorsPendingSpawn . front() );
    m_ActorsPendingSpawn . pop_front();
    HandleSpawnQueue();
}
