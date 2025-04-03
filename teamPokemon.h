/* 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 

    Declaração da classe TeamPokemon

*/

#ifndef TEAM_POKEMON_H
#define TEAM_POKEMON_H

#include "pokemon.h"

class TeamPokemon {
    public:
        void adicionarPokemon(Pokemon pokm);//não sei se preciso de ponteiro aqui
        void removerPokemon(unsigned int indice);
        //void trocarPokemon(Pokemon new_pokm);
        //void salvarAutomaticoEquipe();
        bool salvarEquipe();
        bool carregarEquipe();
        void atualizarEstatisticas();
        vector<int> getEstatisticas();
        vector<int> getPokemonIndices();
        vector<Image> getPokemonImagens(InterfaceGrafica& interfaceGrafica);
        int getQuantidadePokemons();
        int operator()(int indicePokemon) const; // para verificar se tem o pokemon ID na equipe
        
    private:
        vector<Pokemon> team;
        vector<Image> spritePokemons;
        unsigned int num_pokemons;
        int soma_hp_equipe;
        int soma_attack_equipe;
        int soma_defense_equipe;
        int soma_spAttack_equipe;
        int soma_spDefense_equipe;
        int soma_speed_equipe;

};

#endif