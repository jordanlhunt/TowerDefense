/*
 * SpriteComponent.h
 *
 *  Created on: Sep 2, 2020
 *      Author: Jordan "Heroic" Hunt
 */

#pragma once
#ifndef SPRITECOMPONENT_H_
#define SPRITECOMPONENT_H_
#include "Component.h"
#include "SDL2/SDL.h"
class SpriteComponent : public Component
{
public:
    // Lower draw order corresponds with closer background
    SpriteComponent(class GameObject *owningGameObject, int drawOrder = 100);
    ~SpriteComponent();
    virtual void Draw(SDL_Renderer *renderer);
    virtual void SetTexture(SDL_Texture *texture);
    int GetDrawOrder() const
    {
        return this->drawOrder;
    }
    int GetTextureHeight()
    {
        return this->textureHeight;
    }
    int GetTextureWidth() const
    {
        return this->textureWidth;
    }

protected:
    SDL_Texture *texture;
    int drawOrder;
    int textureWidth;
    int textureHeight;
};

#endif /* SPRITECOMPONENT_H_ */
