#include "Entity.h"

Entity::Entity(std::string name, int life,int damage ,int maxLife,
    int positionX, int positionY)
    : Name(name),
    Life(life),
    Damage(damage),
    MaxLife(maxLife),
    PositionX(positionX),
    PositionY(positionY)
{
    if (MaxLife < 0)
        MaxLife = 0;

    if (Life < 0)
        Life = 0;

    if (Life > MaxLife)
        Life = MaxLife;

    if (PositionX < 0)
        PositionX = 0;

    if (PositionY < 0)
        PositionY = 0;
}

int Entity::GetLife() const
{
    return Life;
}

void Entity::SetLife(int value)
{
    if (value < 0)
        value = 0;

    if (value > MaxLife)
        value = MaxLife;

    Life = value;
}

int Entity::GetDamage() const
{
    return Damage;
}

void Entity::SetDamage(int value)
{
    if (value < 0)
        value = 0;

    Damage = value;
}
std::string Entity::GetName() const
{
    return Name;
}

void Entity::SetName(const std::string& value)
{
    Name = value;
}

int Entity::GetPositionX() const
{
    return PositionX;
}

int Entity::GetPositionY() const
{
    return PositionY;
}

void Entity::SetPositionX(int value)
{
    if (value < 0)
        value = 0;

    PositionX = value;
}

void Entity::SetPositionY(int value)
{
    if (value < 0)
        value = 0;

    PositionY = value;
}