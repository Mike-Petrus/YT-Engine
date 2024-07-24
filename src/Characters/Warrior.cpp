#include "Warrior.h"
#include "../Core/Engine.h"
#include "../Graphics/TextureManager.h"
#include "../Inputs/Input.h"
#include "../Camera/Camera.h"
#include "../Collision/CollisionHandler.h"
#include <SDL2/SDL.h>

Warrior::Warrior(Properties* props) : Character(props){
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 0, 6, 100);

    m_Collider = new Collider();
    m_Collider->SetBuffer(0, 0, 0, 0);

    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
}

void Warrior::Draw(){
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update(float dt){

    m_Animation->SetProps("player", 0, 6, 100);
    m_RigidBody->UnSetForce();

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        m_RigidBody->ApplyForce(5*BACKWARD);
        m_Animation->SetProps("player_run", 0, 8, 100, SDL_FLIP_HORIZONTAL);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        m_RigidBody->ApplyForce(5*FORWARD);
        m_Animation->SetProps("player_run", 0, 8, 100);
    }

    //Jump
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_IsGrounded){
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_IsJumping && m_JumpTime > 0){
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
    }
    else{
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    //move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())){
        m_Transform->X = m_LastSafePosition.X;
    }

    //move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())){
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }

    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;
    
    m_Animation->Update();
}

void Warrior::Clean(){
    TextureManager::GetInstance()->Drop(m_TextureID);
}