#include "Enemy.h"
#include "Level.h"

Enemy::Enemy(int life, int damage, int enemyX, int enemyY, int maxLife)
	: Entity("Default name", life,damage ,maxLife, enemyX, enemyY)
{
    
}

void Enemy::enemymovement(Level& level)
{
    for (int i = 0; i < level.enemyCount; i++)
    {
        if (level.enemies[i].GetLife() <= 0)
            continue;

        int newX = level.enemies[i].GetPositionX();
        int newY = level.enemies[i].GetPositionY();

        // Choisir une direction aleatoire
        switch (rand() % 4)
        {
        case 0: newY--; break;
        case 1: newY++; break;
        case 2: newX--; break;
        case 3: newX++; break;
        }

        // Verifier si le deplacement est autorise
        if (!canMoveTo(level, newX, newY, i))
            continue;

        level.enemies[i].SetPositionX(newX);
        level.enemies[i].SetPositionY(newY);
    }
}

bool Enemy::canMoveTo(const Level& level, int x, int y,
    int ignoredEnemy,
    bool isHero)
{
    if (!isInsideMap(x, y))
        return false;

    if (level.Map[y * MAP_WIDTH + x] == 1)
        return false;

    // Seuls les ennemis ne peuvent pas entrer dans la sortie
    if (!isHero &&
        x == level.sortie.x &&
        y == level.sortie.y)
        return false;

    for (int i = 0; i < level.enemyCount; i++)
    {
        if (i == ignoredEnemy)
            continue;

        if (level.enemies[i].GetPositionX() == x &&
            level.enemies[i].GetPositionY() == y)
            return false;
    }

    return true;
}