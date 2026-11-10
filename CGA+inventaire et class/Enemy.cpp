#include "Enemy.h"

Enemy::Enemy(int life, int damage, int enemyX, int enemyY, int maxLife)
	: Entity("Default name", life,damage ,maxLife, enemyX, enemyY)
{

}