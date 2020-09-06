/*
 * Tile.cpp
 *
 *  Created on: Sep 3, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#include "Tile.h"
#include "Game.h"
#include "SpriteComponent.h"
Tile::Tile(class Game *game)
    : GameObject(game), parent(nullptr), f(0.0), g(0.0f), h(0.0f), isBlocked(false), sprite(nullptr), tileState(DEFAULT), isSelected(false)
{
    this->sprite = new SpriteComponent(this);
    UpdateTexture();
}
void Tile::SetTileState(TileState state)
{
    this->tileState = state;
    UpdateTexture();
}
void Tile::ToggleSelect()
{
    this->isSelected = !isSelected;
    UpdateTexture();
}
void Tile::UpdateTexture()
{
    std::string text;
    switch (this->tileState)
    {
    case START:
        text = "Assets/TileTan.png";
        break;
    case END:
        text = "Assets/TileGreen.png";
        break;
    case PATH:
        if (isSelected)
        {
            text = "Assets/TileGreySelected.png";
        }
        else
        {
            text = "Assets/TileGrey.png";
        }
        break;
    case DEFAULT:
    default:
        if (isSelected)
        {
            text = "Assets/TileBrownSelected.png";
        }
        else
        {
            text = "Assets/TileBrown.png";
        }
        break;
    }
    this->sprite->SetTexture(GetGame()->GetTexture(text));
}
