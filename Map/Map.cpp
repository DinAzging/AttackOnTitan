#include "Map.h"
#include <cmath>
#include <iostream>

sf::Vector2i Map::playerIndexSearch(sf::Vector2f playerPosition)
{
    for (size_t i = 0; i < this->worldSizeHeight; i++)
    {
        for (size_t j = 0; j < this->worldSizeWidth; j++)
        {
            if (this->map[i][j]->getCellCoordinate().x > playerPosition.x && this->map[i][j]->getCellCoordinate().y > playerPosition.y)   
            {
                if (i % 2 == 0)
                {  
                    return sf::Vector2i(j, i - 1);
                }
                else return sf::Vector2i(j - 1, i - 1);

            }
            if ((j == this->worldSizeWidth - 1) 
                 && (
                        this->map[i][j]->getCellCoordinate().x + this->map[i][j]->getGlobalBounds().width > playerPosition.x 
                     && this->map[i][j]->getCellCoordinate().y > playerPosition.y
                    )
                )
                {
                    if (i % 2 == 0)
                    {  
                        return sf::Vector2i(j, i - 1);
                    }
                    else return sf::Vector2i(j, i - 1);
                }

            if ((i == this->worldSizeHeight - 1) && (j == this->worldSizeWidth - 1) 
            && (
                   this->map[i][j]->getCellCoordinate().x + this->map[i][j]->getGlobalBounds().width > playerPosition.x 
                && this->map[i][j]->getCellCoordinate().y + this->map[i][j]->getGlobalBounds().height > playerPosition.y
               ))
               {
                    if (i % 2 == 0)
                    {  
                        return sf::Vector2i(j, i);
                    }
                    else return sf::Vector2i(j, i);
               }

               if ((i == this->worldSizeHeight - 1) 
               && (
                    this->map[i][j]->getCellCoordinate().x > playerPosition.x
                   && this->map[i][j]->getCellCoordinate().y + this->map[i][j]->getGlobalBounds().height > playerPosition.y
                  ))
                {
                    if (i % 2 == 0)
                    {  
                       return sf::Vector2i(j, i);
                    }
                    else return sf::Vector2i(j - 1, i);
                }
            else continue;
        }
    }
    return sf::Vector2i(100000, 100000);
}

void Map::clear()
{
	for (size_t x = 0; x < this->worldSizeHeight; x++)
	{
		for (size_t y = 0; y < this->worldSizeWidth; y++)
		{
			delete this->map[x][y];
			this->map[x][y] = NULL;
		}
		this->map[x].clear();
	}
	this->map.clear();

}

char Map::getRandomCell()
{
    char cellRandom[] = 
    {
        'i', 't', 'f', 'w', 'b'
    };

    float cellChance[] =
    {
        .510f, .093f, .080f, .093f, .085f
    };

    int arrayLength = sizeof(cellChance)/sizeof(*cellChance);
    double random;
    int arraySize;

    do
    {
        random = (double)rand()/(double)RAND_MAX;
        arraySize = 0;
        for (int i = 0; i < arrayLength; i++)
        {
            arraySize += random <= cellChance[i] ? 1:0;
        }
        
    } while (arraySize == 0);
    
    int* inxs = new int[arraySize];

    for (int i = 0, p = 0; i < arrayLength; i++)
    {
        if(random <= cellChance[i])
        {
            inxs[p++] = i;
        }
    }
    
    char result = cellRandom[inxs[(int)floor((double)rand()/(double)RAND_MAX * arraySize)]];
    delete[] inxs;

    return result;
}

sf::Vector2f Map::getPositionHexagon(int indexX, float indexY)
{
    return this->map[indexY][indexX]->getCellCoordinate();
}

sf::Vector2i Map::indexSearch(sf::Vector2f position)
{
    for (size_t i = 0; i < this->worldSizeHeight; i++)
    {
        for (size_t j = 0; j < this->worldSizeWidth; j++)
        {
            if (this->map[i][j]->getCellCoordinate().x < position.x && position.x < this->map[i][j]->getCellCoordinate().x + this->map[i][j]->getGlobalBounds().width
            &&  this->map[i][j]->getCellCoordinate().y < position.y && position.y < this->map[i][j]->getCellCoordinate().y + this->map[i][j]->getGlobalBounds().height)   
            {
                return sf::Vector2i(j, i);

            }
            else continue;
        }
    }
    return sf::Vector2i(100000, 100000);
}

template <typename Func>
sf::Vector2i Map::processRoute(std::string route, sf::Vector2f playerPosition, bool &out, Func action)
{
    sf::Vector2i playerIndex = playerIndexSearch(playerPosition);

    if((playerIndex.x == 100000) || (playerIndex.y == 100000))
    {
        std::cout<<"Fatal Error in Map::ghostRoute -> Map::playerIndexSearch";
        exit(0);
    }

    action(playerIndex);
    for (size_t i = 0; i < route.length(); i++)
    {
        switch (route[i])
        {
        case '1':
            if (playerIndex.y % 2 == 0)
            {
                if ((playerIndex.y == 0) || (playerIndex.x == this->worldSizeWidth - 1))
                {
                    out = true;
                    return playerIndexSearch(playerPosition);
                }
                playerIndex.y--;
                playerIndex.x++;
                action(playerIndex);
            }
            else 
            {
                if (playerIndex.y == 0)
                {
                    out = true;
                    return playerIndexSearch(playerPosition);
                }
                playerIndex.y--;
                action(playerIndex);
            }
            
            break;

        case '2':
            if (playerIndex.x == this->worldSizeWidth - 1)
            {
                out = true;
                return playerIndexSearch(playerPosition);
            }
            playerIndex.x++;
            action(playerIndex);
            break;

        case '3': 
            if (playerIndex.y % 2 == 0)
            {
                if ((playerIndex.x == this->worldSizeWidth - 1) || (playerIndex.y == this->worldSizeHeight - 1))
                {
                    out = true;
                    return playerIndexSearch(playerPosition);
                }
                playerIndex.x++;
                playerIndex.y++;
                action(playerIndex);
            }
            else 
            {
                if (playerIndex.y == this->worldSizeHeight - 1)
                {
                    out = true;
                    return playerIndexSearch(playerPosition);
                }
                playerIndex.y++;
                action(playerIndex);
            }
            
            break;

        case '4':
            if (playerIndex.y % 2 == 0)
            {
                if (playerIndex.y == this->worldSizeHeight - 1)
                {
                    out = true;
                    return playerIndexSearch(playerPosition);
                }
                playerIndex.y++;
                action(playerIndex);
            }
            else 
            {
                if ((playerIndex.x == 0) || (playerIndex.y == this->worldSizeHeight - 1))
                {
                    out = true;
                    return playerIndexSearch(playerPosition);
                }
                playerIndex.x--;
                playerIndex.y++;
                action(playerIndex);
            }
            
            break;

        case '5':
            if (playerIndex.x == 0)
            {
                out = true;
                return playerIndexSearch(playerPosition);
            }
            playerIndex.x--;
            action(playerIndex);
            break;

        case '6':
            if (playerIndex.y % 2 == 0)
            {
                if (playerIndex.y == 0)
                {
                    out = true;
                    return playerIndexSearch(playerPosition);
                }
                playerIndex.y--;
                action(playerIndex);
            }
            else 
            {
                if ((playerIndex.x == 0) || (playerIndex.y == 0))
                {
                    out = true;
                    return playerIndexSearch(playerPosition);
                }
                playerIndex.y--;
                playerIndex.x--;
                action(playerIndex);
            }
            break;

        default:
            if(route[i] == 'd')
            {
                break;
            }
            else
            {
                std::cout<<"Fatal Error in Map::ghostRoute::default";
                exit(1);
                break;
            }
        }
    }

    return playerIndex;
}

sf::Vector2i Map::ghostRoute(std::string route, sf::Vector2f playerPosition, bool &out)
{
    return processRoute(route, playerPosition, out, [this](sf::Vector2i idx){this->map[idx.y][idx.x]->setCellColor(gostColor);});
}

void Map::deselectGhostRoute(std::string route, sf::Vector2f playerPosition, bool &out)
{
    processRoute(route, playerPosition, out, [this](sf::Vector2i idx){this->map[idx.y][idx.x]->cellPainting();});
}

void Map::changeCell(sf::Vector2i playerPosition, Cell::CellType type)
{
    this->map[playerPosition.y][playerPosition.x]->setCellType(type);
    this->map[playerPosition.y][playerPosition.x]->setCellColor(sf::Color(128,0,0));
    this->map[playerPosition.y][playerPosition.x]->setOutline(2, sf::Color::Black);
}

void Map::selectCell(int index_x, int index_y)
{
    this->map[index_y][index_x]->setOutline(3, sf::Color::Green);
}

void Map::deselectCell(int index_x, int index_y)
{
    this->map[index_y][index_x]->cellPainting();
}

Cell::CellType Map::getCellType(sf::Vector2i index) const
{
    return this->map[index.y][index.x]->getCellType();
}

sf::Vector2i Map::getWorldSize() const
{
    return sf::Vector2i(this->worldSizeWidth, this->worldSizeHeight);
}

void Map::initVariables()
{
    this->worldSizeHeight = 18;
    this->worldSizeWidth = 21;
    this->gostColor = sf::Color(255,250,250,50);
}

void Map::initMap()
{      
    unsigned short y = 0;
    unsigned short x;

    this->map.resize(this->worldSizeHeight, std::vector<Cell*>());
	for (size_t i = 0; i < this->worldSizeHeight; i++)
	{
		for (size_t j = 0; j < this->worldSizeWidth; j++)
		{
			this->map[i].resize(this->worldSizeWidth, NULL);
		}
	}

    for(size_t i = 0; i < this->worldSizeHeight; i++)
    {
        y += 78;

        if (i % 2 == 0)
        {
            x = 65;
        }
        
        else    
        {
            x = 20;
        }

        for(size_t j = 0; j < this->worldSizeWidth; j++)
        {
            if (j != 0) x += 90;

            if (this->map[i][j] == NULL)
		    {
                char cellType = getRandomCell();

                if (cellType == 'w')
                {
                    this->map[i][j] = new cell::WarehouseCell(x,y);
                }

                else if (cellType == 't')
                {
                    this->map[i][j] = new cell::TitanCell(x,y);
                }

                else if (cellType == 'f')
                {
                    this->map[i][j] = new cell::ForestCell(x,y);
                }

                else if (cellType == 'b')
                {
                    this->map[i][j] = new cell::BeastCell(x,y);
                }

                else if (cellType == 'i')
                {
                    this->map[i][j] = new cell::IdleCell(x, y);
                }                
		    }
        }
    }
}

void Map::initBackground()
{
    
    
}

Map::Map()
{
    initVariables();
    initMap();
    initBackground();
}

Map::~Map()
{
    clear();
}

void Map::update(const float& dt)
{
}

void Map::render(sf::RenderTarget& target)
{
    for (size_t x = 0; x < this->worldSizeHeight; x++)
	{
	    for (size_t y = 0; y < this->worldSizeWidth; y++)
		{	
			if (this->map[x][y] != NULL)
        	{
				this->map[x][y]->render(target);
			}
    	}
	}
}

    
    
    
