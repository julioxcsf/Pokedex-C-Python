/* 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 

    Declaração da classe Pokedex

*/

#ifndef POKEDEX_H
#define POKEDEX_H

#include <vector>
#include <string>
#include "API_dados.h"
#include "API_grafica.h"
#include "pokemon.h"

using namespace std;


class Pokedex {
public:
    Pokedex(API_Dados& apiDados, InterfaceGrafica& interfaceGrafica);

    // Carrega todos os dados
    void carregarTodosPokemons();
    void carregarPokemonsSprites(int offset);
    void mostrarPokemons(int offset);
    Pokemon mostrarUnicoPokemon(int indice);
    void carregarPokemonsFiltrados(const std::string& filtro);
    void mostrarPokemonsFiltrados(int offset);
    int getNumPokemonsFiltrados();
    int getIdPokemonFiltrado(int pokemonID);


private:
    API_Dados& apiDados; // Referência ao objeto API_Dados
    InterfaceGrafica& interfaceGrafica; // Referência ao objeto InterfaceGrafica

    std::vector<Pokemon> todosPokemons; // Armazena todos os pokemons carregados
    std::vector<Pokemon> pokemonsFiltrados; // Armazena pokemons filtrados
    std::vector<int> indicesPokemonsFiltrados;
    vector<Image> pokemonSprites; // Armazena sprites dos pokemons
    string textoBusca = ""; // Armazena a string de busca
    int indice_pokemon_selecionado; // Armazena o indice do pokemon selecionado
    int offset = 0; // Indice inicial para carregar os pokemons
    int numBotoes = 10; // Número de botões para mostrar pokemons
    int total_pokemons = 0; 
};

#endif //POKEDEX_H