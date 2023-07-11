#include "Actor.h"

Actor::Actor (uint32_t id, const std::shared_ptr<Texture> & texture, const SDL_Rect & physicsBody, ECollisionChannel CollisionChannel )
: m_ObjectID ( id ), m_Tex ( texture ), m_PhysicsBody( physicsBody ), m_CollisionChannel ( CollisionChannel )
{}

SDL_Rect Actor::GetPhysicsBody () const { return m_PhysicsBody; }
void Actor::SetCollisionEnabled ( bool enabled ) { m_HasCollision = enabled; }
bool Actor::GetCollisionEnabled () const { return m_HasCollision; }
bool Actor::GetTickEnabled () const { return m_TickEnabled; }
void Actor::SetTickEnabled(bool enabled) { m_TickEnabled = enabled; }

uint32_t Actor::GetObjectID() const {
    return m_ObjectID;
}

ECollisionChannel Actor::GetCollisionChannel() const { return m_CollisionChannel; }
void Actor::SetCollisionChannel( ECollisionChannel newChannel ) { m_CollisionChannel = newChannel; }

void Actor::AddComponent(const std::shared_ptr<ActorComponent> & comp ) {
    m_Components . push_back (  comp );
}

std::vector<std::shared_ptr<ActorComponent>> & Actor::GetComponents() {
    return m_Components;
}

bool Actor::GetPendingKill() const { return m_PendingKill; }


void Actor::SetPendingKill() { m_PendingKill = true; }

void Actor::SetTexture( const std::shared_ptr<Texture> & texture ) {
    m_Tex = texture;
}
std::shared_ptr<Texture> Actor::GetTexture() const {
    return m_Tex;
}

ActorComponent::ActorComponent(uint32_t ObjectID, const std::shared_ptr<Actor> &ownerActor)
        : m_ObjectID ( ObjectID ), m_OwnerActor(std::move( ownerActor ) )
{

}
std::shared_ptr<Actor> ActorComponent::GetOwner() const {
    return m_OwnerActor;
}

uint32_t ActorComponent::GetObjectID() {
    return m_ObjectID;
}
void ActorComponent::SetTickEnabled(bool enabled) {
    m_TickEnabled = enabled;
}

bool ActorComponent::GetTickEnabled() const {
    return m_TickEnabled;
}

void ActorComponent::SetCollisionEnabled(bool enabled) {
    m_CollisionEnabled = enabled;
}
bool ActorComponent::GetCollisionEnabled() const {
    return m_CollisionEnabled;
}

bool ActorComponent::GetPendingKill() const { return m_PendingKill; }


void ActorComponent::SetPendingKill() { m_PendingKill = true; }
