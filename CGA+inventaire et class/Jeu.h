#pragma once

#include <memory>
#include "Map.h"
#include "Jeu.h"
#include "FonctionJeu.h"
#include "ChoixClasse.h"
#include "Spell.h"

class Jeu
{
private:
    
    Jeu() = default;

    
    Jeu(const Jeu&) = delete;
    Jeu& operator=(const Jeu&) = delete;

    std::unique_ptr<Player> player;
    Level level;
    int currentLevel = 1;

    bool jeuEnCours = true;

public:
   
    static Jeu& getInstance()
    {
        static Jeu instance;
        return instance;
    }

    void lancerjeu();
};