/* 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 

    Declaração da classe MenuPokedex

*/

#ifndef MENU_POKEDEX_H
#define MENU_POKEDEX_H

#include <string>
#include "API_dados.h"
#include "API_grafica.h"
#include "pokedex.h"
#include "teamPokemon.h"

enum Estado { 
    MENU,
    POKEDEX,
    POKEMON_INDIVIDUAL,
    TEAM_POKEMON,
    SAIR 
};

using namespace std;

class MenuPokedex {
    public:
        MenuPokedex();
        ~MenuPokedex();
        void run(); // Método principal para executar o menu
        
    private:
        API_Dados* apiDados;
        InterfaceGrafica* interface;
        Pokedex* pokedex;
        TeamPokemon teamPokemon;
        
        Estado estadoMenu;
        int offset;
        
        //TeamPokemon inimigos;
        Image logo_image;
        bool alterarConfBotoes = true;

        void ConfigurarBtnMenu(); // são configurações visuais dos botões
        void ConfigurarBtnPokedex(int numBotoesCriados = 10, int numPokemons = 1025, int offset = 0); // são configurações visuais dos botões
        void ConfigurarBtnPokemonIndividual(int r, int g, int b);
        void ConfigurarBtnTeamPokemon(int numPokemons);
        void EscreverMenu();
        void EscreverPokemonIndividualBotao(int indice);
        void EscreverTeamPokemon();
        //void MostrarMeusPokemons();
};

#endif // MENU_POKEDEX_H