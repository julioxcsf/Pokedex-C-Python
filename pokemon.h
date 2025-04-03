/* 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 

    Declaração da classe Pokemon

*/

#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include "API_grafica.h"

class Pokemon {
public:
    Pokemon(int ID, const std::string& nome,
            int hp = 0, int attack = 0, int defense = 0,
            int spAttack = 0, int spDefense = 0, int speed = 0);

    int getID() const;
    const std::string& getNome() const;

    // Métodos para tipos
    void setTypes(const std::string& type1, const std::string& type2 = "");
    std::string getType(unsigned int index) const;

    // Métodos para obter Stats
    int getHP() const;
    int getAttack() const;
    int getDefense() const;
    int getSpAttack() const;
    int getSpDefense() const;
    int getSpeed() const;

private:
    int ID;
    std::string type[2];
    std::string nome;

    // Atributos de status
    float hp;
    float attack;
    float defense;
    float spAttack;
    float spDefense;
    float speed;
};

#endif // POKEMON_H
