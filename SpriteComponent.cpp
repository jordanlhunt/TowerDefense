/*
 * SpriteComponent.cpp
 *
 *  Created on: Sep 2, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#include "SpriteComponent.h"
#include "Game.h"
#include "GameObject.h"
SpriteComponent::SpriteComponent(GameObject *owner, int drawOrder) : Component(owner), texture(nullptr), drawOrder(drawOrder), textureWidth(0), textureHeight(0)
{
    this->owner->GetGame()->AddSprite(this);
}
SpriteComponent::~SpriteComponent()
{
    this->owner->GetGame()->RemoveSprite(this);
}
void SpriteComponent::Draw(SDL_Renderer *renderer)
{
    if (this->texture)
    {
        SDL_Rect drawRectange;
        // Scale the width and height to the owningGameObject's scale
        drawRectange.w = static_cast<int>(this->textureWidth * this->owner->GetScale());
        drawRectange.h = static_cast<int>(this->textureHeight * this->owner->GetScale());
        // Center the rectangle around the position of the owner
        drawRectange.x = static_cast<int>(this->owner->GetPosition().x - drawRectange.w / 2);
        drawRectange.y = static_cast<int>(this->owner->GetPosition().y - drawRectange.h / 2);
        // Draw - Convert angle from radians to degrees and clockwise to counter clockwise
        SDL_RenderCopyEx(renderer, this->texture, nullptr, &drawRectange, -Math::ToDegrees(this->owner->GetRotation()), nullptr, SDL_FLIP_NONE);
    }
}
void SpriteComponent::SetTexture(SDL_Texture *texture)
{
    this->texture = texture;
    SDL_QueryTexture(this->texture, nullptr, nullptr, &textureWidth, &textureHeight);
}
