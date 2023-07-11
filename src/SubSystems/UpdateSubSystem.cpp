//
// Created by Черкасов Андрей on 18.05.2022.
//

#include "UpdateSubSystem.h"
#include <iostream>
void UpdateSubSystem::Destroy()
{		
	m_ActorsToUpdate . clear() ;
	m_ComponentsToUpdate . clear() ;
	m_ActorsPendingSpawn . clear() ;
	m_ComponentsPendingSpawn . clear();
    	
}
bool UpdateSubSystem::DestroyActor(uint32_t ObjectID) {
    for ( auto elem = m_ActorsToUpdate . begin(); elem != m_ActorsToUpdate . end(); ++ elem ) 
    {
        if ( (*elem) -> GetObjectID() == ObjectID ) {
            (*elem) -> SetPendingKill();
            if ( (*elem) -> GetObjectID() == 9 )
            {
                
            }
            for ( auto & comp : (*elem) -> GetComponents() ) 
            {
            	comp -> SetPendingKill(); 
        	}
            return true;
        }
    }
    for ( auto y = m_ActorsPendingSpawn . begin(); y != m_ActorsPendingSpawn . end(); ++ y ) 
    {
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

bool UpdateSubSystem::RegisterActor(const std::shared_ptr<Actor> &actor) {
    for ( auto elem = m_ActorsToUpdate . begin(); elem != m_ActorsToUpdate . end(); ++ elem )
    {
        if ( (*elem) -> GetObjectID() == actor -> GetObjectID() )
            return false;
    }
    for ( auto & y : m_ActorsPendingSpawn ) { 
        if ( y -> GetObjectID () == actor -> GetObjectID() ) { 
            return false;
        }
    }
    m_ActorsPendingSpawn . push_back ( actor );
    for ( auto & comp : actor -> GetComponents() ) { 
    	m_ComponentsPendingSpawn . push_back ( comp ); 
    }
    return true;
}

void UpdateSubSystem::Update() {
    GarbageCollect();
    HandleSpawnQueue();

    for ( auto & actor : m_ActorsToUpdate ) 
    {
        if ( actor -> GetTickEnabled() ) { 
            actor -> Tick( 0.16 );
        
        }
    }
    for ( auto & comp : m_ComponentsToUpdate )
    {
        if ( comp -> GetTickEnabled() )
            comp -> Tick ( 0.16 );
    }
}

bool UpdateSubSystem::Init() {
    return true;
}

bool UpdateSubSystem::RegisterComponent(const std::shared_ptr<ActorComponent> &component) {
    for ( auto elem = m_ActorsToUpdate . begin(); elem != m_ActorsToUpdate . end(); ++ elem )
    {
        if ( (*elem) -> GetObjectID() == component -> GetObjectID() )
            return false;
    }
    m_ComponentsPendingSpawn . push_back ( component );
    return true;
}

void UpdateSubSystem::GarbageCollect() {
    for ( uint32_t i = 0; i < m_ActorsToUpdate . size() ; i++  )
    { 
        if ( m_ActorsToUpdate[i] -> GetPendingKill() ) {
            m_ActorsToUpdate . erase ( m_ActorsToUpdate . begin() + i );
            break;
        }
    }
    for ( uint32_t i = 0; i < m_ComponentsToUpdate . size() ; i++  ) 
    { 
        if ( m_ComponentsToUpdate[i] -> GetPendingKill() ) {
            m_ComponentsToUpdate.erase(m_ComponentsToUpdate.begin() + i);
            break;
        }
    }
}

void UpdateSubSystem::HandleSpawnQueue() {
    if ( m_ActorsPendingSpawn . empty() && m_ComponentsPendingSpawn . empty() )
        return;
    if ( !m_ActorsPendingSpawn . empty() )
    {
        m_ActorsToUpdate . push_back ( std::move ( m_ActorsPendingSpawn . front() ) );
        m_ActorsPendingSpawn . pop_front();
    }
    if ( !m_ComponentsPendingSpawn . empty() )
    {
        m_ComponentsToUpdate . push_back ( m_ComponentsPendingSpawn . front() );
        m_ComponentsPendingSpawn . pop_front();
    }
    HandleSpawnQueue();
}

