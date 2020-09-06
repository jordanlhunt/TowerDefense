/*
 * Game.h
 *
 *  Created on: Aug 12, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#pragma once
#include "Math.h"
#include "SDL2/SDL.h"
#include <string>
#include <unordered_map>
#include <vector>

#ifndef GAME_H_
#define GAME_H_

class Game
{
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
    void AddGameObject(class GameObject *gameObject);
    void RemoveGameObject(class GameObject *gameObject);
    void AddSprite(class SpriteComponent *sprite);
    void RemoveSprite(class SpriteComponent *sprite);
    SDL_Texture *GetTexture(const std::string &fileName);
    class Grid *GetGrid()
    {
        return this->grid;
    }
    std::vector<class Enemy *> &GetEnemies()
    {
        return this->enemies;
    }
    class Enemy *GetNearestEnemy(const Vector2 &position);

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();
    // Map of textures loaded
    std::unordered_map<std::string, SDL_Texture *> textures;
    // All the GameObjects in the game
    std::vector<class GameObject *> gameObjects;
    // All Pending GameObjects
    std::vector<class GameObject *> pendingGameObjects;
    // All the sprite components drawn
    std::vector<class SpriteComponent *> sprites;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint32 tickCount;
    bool isRunning;
    // Track if currently updating gameObjects
    bool isUpdatingGameObjects;
    // Tower Defense
    std::vector<class Enemy *> enemies;
    class Grid *grid;
    float nextEnemy;
};

#endif /* GAME_H_ */
