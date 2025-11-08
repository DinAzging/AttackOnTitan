#include "Cell.h"
#include <iostream>

//Class Cell
void Cell::initVariables()
{
    this->pointCount = 6;
    this->radius = 50.f;
}

void Cell::initHexagon()
{
    this->hexagon.setPointCount(this->pointCount);
    this->hexagon.setRadius(this->radius);
}

Cell::Cell(CellType type, unsigned short cellX, unsigned short cellY) 
    : type(type)
{

}

Cell::~Cell()
{
    
}

sf::FloatRect Cell::getGlobalBounds()
{
    return sf::FloatRect(this->hexagon.getGlobalBounds());
}

sf::Vector2f Cell::getCellCoordinate()
{
    return this->hexagon.getPosition();
}

Cell::CellType Cell::getCellType()
{
    return this->type;
}

void Cell::setCellColor(sf::Color color)
{
    this->hexagon.setFillColor(color);
}

void Cell::setOutline(float size, sf::Color color)
{
    this->hexagon.setOutlineThickness(size);
    this->hexagon.setOutlineColor(color);
}

void Cell::setCellType(CellType type)
{
    this->type = type;
}

void Cell::cellPainting()
{
    this->hexagon.setOutlineThickness(2);

    if (type == Cell::CellType::Idle)
    {
        this->hexagon.setFillColor(sf::Color::Transparent);
        this->hexagon.setOutlineColor(sf::Color::Black);
    }

    else if (type == Cell::CellType::Beast)
    {
        this->hexagon.setFillColor(sf::Color::Blue);
        this->hexagon.setOutlineColor(sf::Color::Black);
    }

    else if (type == Cell::CellType::Forest)
    {
        this->hexagon.setFillColor(sf::Color::Green);
        this->hexagon.setOutlineColor(sf::Color::Black);
    }

    else if (type == Cell::CellType::Titan)
    {
        this->hexagon.setFillColor(sf::Color::Red);
        this->hexagon.setOutlineColor(sf::Color::Black);
    }

    else if (type == Cell::CellType::Warehouse)
    {
        this->hexagon.setFillColor(sf::Color::Yellow);
        this->hexagon.setOutlineColor(sf::Color::Black);
    }
}

void Cell::render(sf::RenderTarget&target)
{
    target.draw(this->hexagon);
}


//Class IdleCell
cell::IdleCell::IdleCell(unsigned short cellX, unsigned short cellY) : Cell(CellType::Idle, cellX, cellY)
{   
    this->initVariables();
    this->initHexagon();
    this->cellPainting();

    this->cellX = cellX;
    this->cellY = cellY;

    this->hexagon.setPosition(cellX, cellY);
}


//Class TitanCell
cell::TitanCell::TitanCell(unsigned short cellX, unsigned short cellY) : Cell(CellType::Titan, cellX, cellY)
{
    this->initVariables();
    this->initHexagon();
    this->cellPainting();

    this->cellX = cellX;
    this->cellY = cellY;

    this->hexagon.setPosition(cellX, cellY);
}


//Class ForestCell
cell::ForestCell::ForestCell(unsigned short cellX, unsigned short cellY) : Cell(CellType::Forest, cellX, cellY)
{
    initVariables();
    initHexagon();
    cellPainting();

    this->cellX = cellX;
    this->cellY = cellY;

    this->hexagon.setPosition(cellX, cellY);
}


//Class BeastCell
cell::BeastCell::BeastCell(unsigned short cellX, unsigned short cellY) : Cell(CellType::Beast, cellX, cellY)
{
    this->initVariables();
    this->initHexagon();
    this->cellPainting();

    this->cellX = cellX;
    this->cellY = cellY;

    this->hexagon.setPosition(cellX, cellY);
}


//Class WarehouseCell
cell::WarehouseCell::WarehouseCell(unsigned short cellX, unsigned short cellY) : Cell(CellType::Warehouse, cellX, cellY)
{
    this->initVariables();
    this->initHexagon();
    this->cellPainting();

    this->cellX = cellX;
    this->cellY = cellY;

    this->hexagon.setPosition(cellX, cellY);
}
