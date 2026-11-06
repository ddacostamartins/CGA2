#pragma once
#include <string>
class Enemy
{
private:
	std::string Enemyname = "Default name";
protected:
	int EnemyLife;
	int EnemyDamage;
	int EnemyX;
	int EnemyY;
	int MaxEnemyLife;

public:
	
	Enemy(int EnemyLife, int enemydamage, int enemyX, int enemyY, int maxEnemyLife);

	int GetEnemyLife() const;
	void SetEnemyLife(int value);

	int GetEnemyDamage() const;
	void SetEnemyDamage(int value);

	void SetEnemyName(const std::string& value);
	std::string GetEnemyName() const;

	int GetEnemyX() const;
	int GetEnemyY() const;

	void SetEnemyX(int value);
	void SetEnemyY(int value);
};

