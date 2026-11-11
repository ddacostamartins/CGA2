#pragma once

class Weapon
{
private:
    int Damage = 3;
    int Lifesteal = 1;

public:
    int GetDamage() const;
    void SetDamage(int value);

    int GetLifesteal() const;
    void SetLifesteal(int value);
};