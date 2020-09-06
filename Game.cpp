/*
 * Game.cpp
 *
 *  Created on: Aug 12, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#include "Game.h"
#include "AIComponent.h"
#include "AIState.h"
#include "Enemy.h"
#include "GameObject.h"
#include "Grid.h"
#include "SDL2/SDL_image.h"
#include "SpriteComponent.h"
#include <algorithm>
Game::Game() : window(nullptr), renderer(nullptr), isRunning(true), isUpdatingGameObjects(false)
{
}
bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    this->window = SDL_CreateWindow("Tower Defense", 100, 100, 1024, 768, 0);
    if (!this->window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }
    LoadData();
    this->tickCount = SDL_GetTicks();
    return true;
}
void Game::RunLoop()
{
    while (this->isRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}
void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            this->isRunning = false;
            break;
        }
    }
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    // If player clicks ESC exit the game
    if (keyState[SDL_SCANCODE_ESCAPE])
    {
        this->isRunning = false;
    }
    // If player clicks "B" build a tower on the grid
    if (keyState[SDL_SCANCODE_B])
    {
        this->grid->BuildTower();
    }
    // Handle mouse
    int x;
    int y;
    Uint32 mouseButtons = SDL_GetMouseState(&x, &y);
    if (SDL_BUTTON(mouseButtons) & SDL_BUTTON_LEFT)
    {
        this->grid->ProcessClick(x, y);
    }
    // Update Game Objects
    this->isUpdatingGameObjects = true;
    for (auto gameObject : this->gameObjects)
    {
        gameObject->ProcessInput(keyState);
    }
    this->isUpdatingGameObjects = false;
}
void Game::UpdateGame()
{
    // Compute delta time
    // Wait until 16ms has elapased since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), this->tickCount + 16))
        ;
    float deltaTime = (SDL_GetTicks() - this->tickCount) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    this->tickCount = SDL_GetTicks();
    // Update all gameObjects
    this->isUpdatingGameObjects = true;
    for (auto gameObject : this->gameObjects)
    {
        gameObject->Update(deltaTime);
    }
    this->isUpdatingGameObjects = false;
    // Move pending gameObjects to active
    for (auto pendingGameObjects : this->pendingGameObjects)
    {
        this->gameObjects.emplace_back(pendingGameObjects);
    }
    this->pendingGameObjects.clear();
    // Add any dead gameObject to a temp vector
    std::vector<GameObject *> deadGameObjects;
    for (auto gameObject : this->gameObjects)
    {
        if (gameObject->GetState() == GameObject::DEAD)
        {
            deadGameObjects.emplace_back(gameObject);
        }
    }
    // Delete dead gameObjects (which removes them from this->gameObjects)
    for (auto gameObject : deadGameObjects)
    {
        delete gameObject;
    }
}
void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(this->renderer, 154, 206, 235, 255);
    SDL_RenderClear(this->renderer);
    // Draw all the sprite
    for (auto sprite : this->sprites)
    {
        sprite->Draw(this->renderer);
    }
    SDL_RenderPresent(this->renderer);
}
void Game::LoadData()
{
    this->grid = new Grid(this);
}
void Game::UnloadData()
{
    // Delete gameObjects
    while (this->gameObjects.empty())
    {
        delete this->gameObjects.back();
    }
    // Destroy textures
    for (auto texture : this->textures)
    {
        SDL_DestroyTexture(texture.second);
    }
    this->textures.clear();
}
SDL_Texture *Game::GetTexture(const std::string &fileName)
{
    SDL_Texture *texture = nullptr;
    // Check if the texture is already in the map
    auto iter = this->textures.find(fileName);
    if (iter != this->textures.end())
    {
        texture = iter->second;
    }
    else
    {
        // Load from file
        SDL_Surface *surface = IMG_Load(fileName.c_str());
        if (!surface)
        {
            SDL_Log("Failed to load texture file %s", fileName.c_str());
            return nullptr;
        }
        // Create texture from surface
        texture = SDL_CreateTextureFromSurface(this->renderer, surface);
        SDL_FreeSurface(surface);
        if (!texture)
        {
            SDL_Log("Failed to convert surface to texture %s",
                    fileName.c_str());
            return nullptr;
        }
        this->textures.emplace(fileName.c_str(), texture);
    }
    return texture;
}
void Game::Shutdown()
{
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
void Game::AddGameObject(GameObject *gameObject)
{
    // Check updating gameObjects, add to pending
    if (isUpdatingGameObjects)
    {
        this->pendingGameObjects.emplace_back(gameObject);
    }
    else
    {
        this->gameObjects.emplace_back(gameObject);
    }
}
void Game::RemoveGameObject(GameObject *gameObject)
{
    // Check if gameObject is pending
    auto iter = std::find(this->pendingGameObjects.begin(),
                          this->pendingGameObjects.end(), gameObject);
    if (iter != this->pendingGameObjects.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, this->pendingGameObjects.end() - 1);
        this->pendingGameObjects.pop_back();
    }
    // Check if gameObject is active
    iter = std::find(this->gameObjects.begin(), this->gameObjects.end(),
                     gameObject);
    if (iter != this->gameObjects.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, this->gameObjects.end() - 1);
        this->gameObjects.pop_back();
    }
}
void Game::AddSprite(SpriteComponent *sprite)
{
    // Find the insertion point in the sorted vector
    // The first element with a larger draw order
    int spriteDrawOrder = sprite->GetDrawOrder();
    auto iter = this->sprites.begin();
    for (; iter != this->sprites.end(); ++iter)
    {
        if (spriteDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }
    // Insert element before position of iterator
    this->sprites.insert(iter, sprite);
}
void Game::RemoveSprite(SpriteComponent *sprite)
{
    auto iter = std::find(this->sprites.begin(), this->sprites.end(), sprite);
    this->sprites.erase(iter);
}
Enemy *Game::GetNearestEnemy(const Vector2 &position)
{
    Enemy *nearestEnemy = nullptr;
    if (this->enemies.size() > 0)
    {
        nearestEnemy = this->enemies[0];
        // Save the distance squared of the first enemy, then test if others are closer
        float nearestEnemyDistanceSquared = (position - this->enemies[0]->GetPosition()).LengthSquared();
        for (size_t i = 1; i < this->enemies.size(); i++)
        {
            float otherEnemyDistanceSquared = (position - this->enemies[i]->GetPosition()).LengthSquared();
            if (otherEnemyDistanceSquared < nearestEnemyDistanceSquared)
            {
                nearestEnemyDistanceSquared = otherEnemyDistanceSquared;
                nearestEnemy = this->enemies[i];
            }
        }
    }
    return nearestEnemy;
}
