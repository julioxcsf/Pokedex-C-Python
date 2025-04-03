/* 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
           Maria Fernanda Debatin de Magalhães
    data: 18/12/2024 

    Implementação dos metodos das funcoes da classe Pokemon

*/

#include "pokemon.h"
#include <stdexcept>

Pokemon::Pokemon(int ID, const std::string& nome,
                 int hp, int attack, int defense,
                 int spAttack, int spDefense, int speed)
    : ID(ID), nome(nome),
      hp(hp), attack(attack), defense(defense),
      spAttack(spAttack), spDefense(spDefense), speed(speed)
{
    type[0] = "";
    type[1] = "";
}

int Pokemon::getID() const { return ID; }

const std::string& Pokemon::getNome() const { return nome; }

void Pokemon::setTypes(const std::string& type1, const std::string& type2) {
    type[0] = type1;
    type[1] = type2;
}

std::string Pokemon::getType(unsigned int index) const {
    if (index > 1) {
        throw std::out_of_range("Index de tipo invalido");
    }
    return type[index];
}

int Pokemon::getHP() const { return hp; }
int Pokemon::getAttack() const { return attack; }
int Pokemon::getDefense() const { return defense; }
int Pokemon::getSpAttack() const { return spAttack; }
int Pokemon::getSpDefense() const { return spDefense; }
int Pokemon::getSpeed() const { return speed; }