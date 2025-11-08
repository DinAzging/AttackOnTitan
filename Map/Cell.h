#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Cell
{
public:
    enum class CellType
    {
        Idle,
        Titan,
        Forest,
        Beast,
        Warehouse,
        DeadTitan
    };

    Cell(CellType type, unsigned short cellX, unsigned short cellY);
    virtual ~Cell();

    sf::FloatRect getGlobalBounds();
    sf::Vector2f getCellCoordinate();
    CellType getCellType();

    void setCellColor(sf::Color color);
    void setOutline(float size, sf::Color color);
    void setCellType(CellType type);

    void cellPainting();

    void render(sf::RenderTarget&target);

protected:
    CellType type;

    sf::CircleShape hexagon;
    std::size_t pointCount;
    float radius;

    unsigned short cellX;
    unsigned short cellY;

    sf::Color colorCell;

    void initVariables();
    void initHexagon();
};

namespace cell
{
    class IdleCell : public Cell
    {
    public:
        IdleCell(unsigned short cellX, unsigned short cellY);
    };

    class TitanCell : public Cell
    {
    public:
        TitanCell(unsigned short cellX, unsigned short cellY);
    };

    class ForestCell : public Cell
    {
    public:
        ForestCell(unsigned short cellX, unsigned short cellY);
    };

    class BeastCell : public Cell
    {
    public:
        BeastCell(unsigned short cellX, unsigned short cellY);
    };

    class WarehouseCell : public Cell
    {
    public:
        WarehouseCell(unsigned short cellX, unsigned short cellY);
    };
}
#endif 