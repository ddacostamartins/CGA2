#include "Enemy.h"
#include "Map.h"

Enemy::Enemy(int enemyLife, int enemyDamage, int enemyX, int enemyY, int maxEnemyLife)
	:EnemyLife(enemyLife),
	EnemyDamage(enemyDamage),
	EnemyX(enemyX),
	EnemyY(enemyY),
	MaxEnemyLife(maxEnemyLife)
{
    if (MaxEnemyLife < 0)
        MaxEnemyLife = 0;

    if (EnemyLife < 0)
        EnemyLife = 0;

    if (EnemyLife > MaxEnemyLife)
        EnemyLife = MaxEnemyLife;

    if (EnemyDamage < 0)
        EnemyDamage = 0;
}
int Enemy::GetEnemyLife() const
{
    return EnemyLife;
}

void Enemy::SetEnemyLife(int value)
{
    if (value < 0)
        value = 0;

    if (value > MaxEnemyLife)
        value = MaxEnemyLife;

    EnemyLife = value;
}

int Enemy::GetEnemyDamage() const
{
    return EnemyDamage;
}

void Enemy::SetEnemyDamage(int value)
{
    if (value < 0)
        value = 0;

    EnemyDamage = value;
}
int Enemy::GetEnemyX() const
{
    return EnemyX;
}

void Enemy::SetEnemyX(int value)
{
    if (value < 0)
        value = 0;

    if (value >= MAP_WIDTH)
        value = MAP_WIDTH - 1;

    EnemyX = value;
}

int Enemy::GetEnemyY() const
{
    return EnemyY;
}

void Enemy::SetEnemyY(int value)
{
    if (value < 0)
        value = 0;

    if (value >= MAP_HEIGHT)
        value = MAP_HEIGHT - 1;

    EnemyY = value;
}