#pragma once

#include <string>

class Entity
{
protected:
    std::string Name;
    int Life;
    int MaxLife;
    int PositionX;
    int PositionY;

public:
    Entity(std::string name, int life, int maxLife, int positionX, int positionY);

    virtual ~Entity() = default;

    int GetLife() const;
    void SetLife(int value);

    std::string GetName() const;
    void SetName(const std::string& value);

    int GetPositionX() const;
    int GetPositionY() const;

    void SetPositionX(int value);
    void SetPositionY(int value);
};