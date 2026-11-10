
#include "Levels.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// =========================
// CHARGEMENT D'UN NIVEAU TXT
// =========================
bool loadLevel(int numero, Level& level) {

    // Nom du fichier : Level1.txt, Level2.txt, etc.
    std::string filename =
        "Level" + std::to_string(numero) + ".txt";

    std::cout << "Chargement du fichier : "
        << filename << '\n';

    // Ouvrir le fichier
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "ERREUR : impossible d'ouvrir "
            << filename << '\n';

        std::cout << "Verifie que le fichier se trouve "
            << "dans le repertoire de travail du jeu.\n";

        return false;
    }

    std::cout << "Fichier ouvert avec succes.\n";

    // =========================
    // REINITIALISER LE NIVEAU
    // =========================
    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) {
        level.Map[i] = 0;
    }

    level.enemyCount = 0;

    bool heroFound = false;
    bool exitFound = false;

    std::string line;

    // =========================
    // 1. LIRE LA CARTE
    // =========================
    for (int y = 0; y < MAP_HEIGHT; y++) {

        if (!std::getline(file, line)) {
            std::cout << "ERREUR : il manque des lignes "
                << "dans la carte.\n";
            return false;
        }

        // Gerer les fins de ligne Windows
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        // Verifier la largeur
        if (line.size() != MAP_WIDTH) {
            std::cout << "ERREUR : la ligne " << y + 1
                << " contient " << line.size()
                << " caracteres au lieu de "
                << MAP_WIDTH << ".\n";

            return false;
        }

        for (int x = 0; x < MAP_WIDTH; x++) {

            char symbole = line[x];

            if (symbole == '.' ||
                symbole == 'H' ||
                symbole == 'E' ||
                symbole == 'X') {

                // Sol, heros, sortie ou ennemi
                level.Map[y * MAP_WIDTH + x] = 0;
            }
            else if (symbole == 'A') {

                // Mur
                level.Map[y * MAP_WIDTH + x] = 1;
            }
            else if (symbole == '~') {

                // Eau
                level.Map[y * MAP_WIDTH + x] = 2;
            }
            else {

                std::cout << "ERREUR : symbole inconnu '"
                    << symbole << "' en x=" << x
                    << ", y=" << y << ".\n";

                return false;
            }
        }
    }

    // =========================
    // 2. LIRE LE SEPARATEUR ---
    // =========================
    if (!std::getline(file, line)) {
        std::cout << "ERREUR : separateur --- absent.\n";
        return false;
    }

    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }

    if (line != "---") {
        std::cout << "ERREUR : la ligne suivant la carte "
            << "doit contenir ---.\n";
        return false;
    }

    // =========================
    // 3. LIRE LES ENTITES
    // =========================
    while (std::getline(file, line)) {

        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        // Ignorer les lignes vides
        if (line.empty()) {
            continue;
        }

        std::istringstream stream(line);

        std::string type;
        stream >> type;

        // -------------------------
        // POSITION DU HEROS
        // Format : HERO x y
        // -------------------------
        if (type == "HERO") {

            int x, y;
            std::string extra;

            if (!(stream >> x >> y) || (stream >> extra)) {
                std::cout << "ERREUR : format HERO invalide.\n";
                return false;
            }

            if (heroFound ||
                x < 0 || x >= MAP_WIDTH ||
                y < 0 || y >= MAP_HEIGHT) {

                std::cout << "ERREUR : position HERO invalide "
                    << "ou declaree plusieurs fois.\n";

                return false;
            }

            level.startX = x;
            level.startY = y;
            heroFound = true;
        }

        // -------------------------
        // POSITION DE LA SORTIE
        // Format : EXIT x y
        // -------------------------
        else if (type == "EXIT") {

            int x, y;
            std::string extra;

            if (!(stream >> x >> y) || (stream >> extra)) {
                std::cout << "ERREUR : format EXIT invalide.\n";
                return false;
            }

            if (exitFound ||
                x < 0 || x >= MAP_WIDTH ||
                y < 0 || y >= MAP_HEIGHT) {

                std::cout << "ERREUR : position EXIT invalide "
                    << "ou declaree plusieurs fois.\n";

                return false;
            }

            level.sortie.x = x;
            level.sortie.y = y;
            exitFound = true;
        }

        // -------------------------
        // POSITION D'UN ENNEMI
        // Format : ENEMY x y damage
        // -------------------------
        else if (type == "ENEMY") {

            int x, y, damage;
            std::string extra;

            if (!(stream >> x >> y >> damage) ||
                (stream >> extra)) {

                std::cout << "ERREUR : format ENEMY invalide.\n";
                return false;
            }

            if (level.enemyCount >= MAX_ENEMIES) {
                std::cout << "ERREUR : trop d'ennemis. Maximum : "
                    << MAX_ENEMIES << ".\n";
                return false;
            }

            if (x < 0 || x >= MAP_WIDTH ||
                y < 0 || y >= MAP_HEIGHT ||
                damage < 0) {

                std::cout << "ERREUR : position ou degats "
                    << "d'un ennemi invalides.\n";

                return false;
            }

            Enemy enemy;

            enemy.nom = "X";
            enemy.damage = damage;
            enemy.x = x;
            enemy.y = y;

            level.enemies[level.enemyCount] = enemy;
            level.enemyCount++;
        }

        // -------------------------
        // TYPE INCONNU
        // -------------------------
        else {
            std::cout << "ERREUR : type inconnu dans le "
                << "fichier : " << type << '\n';

            return false;
        }
    }

    // =========================
    // 4. VERIFIER LES DONNEES
    // =========================
    if (!heroFound) {
        std::cout << "ERREUR : ligne HERO manquante.\n";
        return false;
    }

    if (!exitFound) {
        std::cout << "ERREUR : ligne EXIT manquante.\n";
        return false;
    }

    // Le heros ne doit pas commencer dans un mur
    int heroCell =
        level.Map[level.startY * MAP_WIDTH + level.startX];

    if (heroCell == 1) {
        std::cout << "ERREUR : le HERO est dans un mur.\n";
        return false;
    }

    // La sortie ne doit pas etre dans un mur
    int exitCell =
        level.Map[level.sortie.y * MAP_WIDTH + level.sortie.x];

    if (exitCell == 1) {
        std::cout << "ERREUR : la sortie est dans un mur.\n";
        return false;
    }

    // Aucun ennemi ne doit commencer dans un mur
    for (int i = 0; i < level.enemyCount; i++) {

        int x = level.enemies[i].x;
        int y = level.enemies[i].y;

        if (level.Map[y * MAP_WIDTH + x] == 1) {
            std::cout << "ERREUR : l'ennemi " << i + 1
                << " est dans un mur.\n";
            return false;
        }
    }

    // =========================
    // 5. NIVEAU CHARGE
    // =========================
    std::cout << "Niveau " << numero
        << " charge avec succes !\n";

    std::cout << "Nombre d'ennemis : "
        << level.enemyCount << '\n';

    return true;
}