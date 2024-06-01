#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"
#include "../Physics/Transform.h"
#include <SDL2/SDL.h>

struct Properties{

    public:
        Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE){
            X = x;
            Y = y;
            Flip = flip;
            Width = width;
            Height = height;
            TextureID = textureID;
        }
    
    public:        
        std::string TextureID;
        float X, Y;
        int Width, Height;
        SDL_RendererFlip Flip;
};

class GameObject : public IObject{

    public:
        GameObject(Properties* props): m_TextureID(props->TextureID),
            m_Width(props->Width), m_Height(props->Height), m_Flip(props->Flip){

            m_Transform = new Transform(props->X, props->Y);
        }

        virtual ~GameObject(){delete m_Transform;}

        virtual void Draw()=0;
        virtual void Clean()=0;
        virtual void Update(float dt)=0;

    protected:
        std::string m_TextureID;
        Transform* m_Transform;
        int m_Width, m_Height;
        SDL_RendererFlip m_Flip;
};

#endif