/*
 * Grid.cpp
 *
 *  Created on: Sep 3, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#include "Grid.h"
#include "Enemy.h"
#include "Tile.h"
#include "Tower.h"
#include <algorithm>
Grid::Grid(class Game *game) : GameObject(game), selectedTile(nullptr)
{
    // Create 7 row and 16 columns
    CreateRowsAndColumns();
    // Create Tiles
    CreateTiles();
    // Set start and end tiles
    GetStartTile()->SetTileState(Tile::START);
    GetEndTile()->SetTileState(Tile::END);
    // Set up Adjacency Lists
    CreateAdjacencyLists();
    // Find Path (in reverse)
    FindAStarPath(GetEndTile(), GetStartTile());
    UpdatePathTiles(GetStartTile());
    this->nextEnemySpawnTime = this->ENEMYSPAWNTIME;
}
void Grid::CreateTiles()
{
    // Create tiles
    for (size_t i = 0; i < NUMROWS; i++)
    {
        for (size_t j = 0; j < NUMCOLS; j++)
        {
            this->tiles[i][j] = new Tile(GetGame());
            this->tiles[i][j]->SetPosition(Vector2(TILESIZE / 2.0f + j * TILESIZE, STARTY + i * TILESIZE));
        }
    }
}
void Grid::CreateRowsAndColumns()
{
    this->tiles.resize(NUMROWS);
    for (size_t i = 0; i < this->tiles.size(); i++)
    {
        this->tiles[i].resize(NUMCOLS);
    }
}
void Grid::CreateAdjacencyLists()
{
    for (size_t i = 0; i < NUMROWS; i++)
    {
        for (size_t j = 0; j < NUMCOLS; j++)
        {
            if (i > 0)
            {
                this->tiles[i][j]->adjacentTiles.push_back(this->tiles[i - 1][j]);
            }
            if (i < NUMROWS - 1)
            {
                this->tiles[i][j]->adjacentTiles.push_back(this->tiles[i + 1][j]);
            }
            if (j > 0)
            {
                this->tiles[i][j]->adjacentTiles.push_back(this->tiles[i][j - 1]);
            }
            if (j < NUMCOLS - 1)
            {
                this->tiles[i][j]->adjacentTiles.push_back(this->tiles[i][j + 1]);
            }
        }
    }
}
void Grid::ProcessClick(int x, int y)
{
    y -= static_cast<int>(this->STARTY - this->TILESIZE / 2);
    if (y >= 0)
    {
        x /= static_cast<int>(TILESIZE);
        y /= static_cast<int>(TILESIZE);
        if (x >= 0 && x < static_cast<int>(NUMCOLS) && y >= 0 && y < static_cast<int>(NUMROWS))
        {
            SelectTile(y, x);
        }
    }
}
bool Grid::FindAStarPath(Tile *start, Tile *goal)
{
    for (size_t i = 0; i < NUMROWS; i++)
    {
        for (size_t j = 0; j < NUMCOLS; j++)
        {
            this->tiles[i][j]->g = 0.0f;
            this->tiles[i][j]->isInOpenSet = false;
            this->tiles[i][j]->isInClosedSet = false;
        }
    }
    std::vector<Tile *> openSet;
    // Set current node to start, and add to closed set
    Tile *currentTile = start;
    currentTile->isInClosedSet = true;
    do
    {
        // Add adjacent nodes to open set
        for (Tile *neighbor : currentTile->adjacentTiles)
        {
            if (neighbor->isBlocked)
            {
                continue;
            }
            // Only check node that aren't in the closed set
            if (!neighbor->isInClosedSet)
            {
                if (!neighbor->isInOpenSet)
                {
                    // In open set, so set parent
                    neighbor->parent = currentTile;
                    neighbor->h = (neighbor->GetPosition() - goal->GetPosition()).Length();
                    // g(x) is the parnet's g plus cost of traversing edge
                    neighbor->g = currentTile->g + TILESIZE;
                    neighbor->f = neighbor->g + neighbor->h;
                    openSet.emplace_back(neighbor);
                    neighbor->isInOpenSet = true;
                }
                else
                {
                    // Computer g(x) cost if current become the parent
                    float newG = currentTile->g + TILESIZE;
                    if (newG < neighbor->g)
                    {
                        // Adopt this node
                        neighbor->parent = currentTile;
                        neighbor->g = newG;
                        // f(x) changes because g(x) changes
                        neighbor->f = neighbor->g + neighbor->h;
                    }
                }
            }
        }
        // If open set is empty, all possible paths are exhausted
        if (openSet.empty())
        {
            break;
        }
        // Find lowest cost node in open set
        auto iter = std::min_element(openSet.begin(), openSet.end(), [](Tile *a, Tile *b) { return a->f < b->f; });
        // Set to current and move from open to closed
        currentTile = *iter;
        openSet.erase(iter);
        currentTile->isInOpenSet = false;
        currentTile->isInClosedSet = true;
    } while (currentTile != goal);
    // Check if a path is found
    return (currentTile == goal) ? true : false;
}
void Grid::UpdatePathTiles(class Tile *start)
{
    // Reset all tiles to normal (except for start/end)
    for (size_t i = 0; i < NUMROWS; i++)
    {
        for (size_t j = 0; j < NUMCOLS; j++)
        {
            if (!(i == 3 && j == 0) && !(i == 3 && j == 15))
            {
                this->tiles[i][j]->SetTileState(Tile::DEFAULT);
            }
        }
    }
    Tile *newTile = start->parent;
    while (newTile != GetEndTile())
    {
        newTile->SetTileState(Tile::PATH);
        newTile = newTile->parent;
    }
}
void Grid::BuildTower()
{
    if (this->selectedTile && !this->selectedTile->isBlocked)
    {
        this->selectedTile->isBlocked = true;
        if (FindAStarPath(GetEndTile(), GetStartTile()))
        {
            Tower *tower = new Tower(GetGame());
            tower->SetPosition(this->selectedTile->GetPosition());
        }
        else
        {
            // This tower would block the path, so don't allow build
            this->selectedTile->isBlocked = false;
            FindAStarPath(GetEndTile(), GetStartTile());
        }
        UpdatePathTiles(GetStartTile());
    }
}
Tile *Grid::GetStartTile()
{
    return this->tiles[0][0];
}
Tile *Grid::GetEndTile()
{
    return this->tiles[3][15];
}
void Grid::UpdateGameObject(float deltaTime)
{
    GameObject::UpdateGameObject(deltaTime);
    // Check if it is time to spawn new enemy
    this->nextEnemySpawnTime -= deltaTime;
    if (this->nextEnemySpawnTime <= 0.0f)
    {
        new Enemy(GetGame());
        this->nextEnemySpawnTime += ENEMYSPAWNTIME;
    }
}
void Grid::SelectTile(size_t row, size_t col)
{
    // Ensure that choice is valid
    Tile::TileState currentState = this->tiles[row][col]->GetTileState();
    if (currentState != Tile::START && currentState != Tile::END)
    {
        // Deselect previous one
        if (this->selectedTile)
        {
            this->selectedTile->ToggleSelect();
        }
        this->selectedTile = this->tiles[row][col];
        this->selectedTile->ToggleSelect();
    }
}
