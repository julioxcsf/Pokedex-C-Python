/* 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 

    Implementação dos métodos da classe MenuPokedex

*/

#include <iostream>
#include "menuPokedex.h"

MenuPokedex::MenuPokedex() : estadoMenu(MENU) {
    // Inicialize apiDados e interface
    apiDados = new API_Dados(); 
    interface = new InterfaceGrafica(800, 600, "Pokedex");

    pokedex = new Pokedex(*apiDados, *interface); 

    // Carregue a imagem do logo
    string pokemon_image_path = "./Images/Pokedex_3D_logo.png"; 
    logo_image = interface->carregarImagemLocal(pokemon_image_path, 0.8, 0.4);
}

MenuPokedex::~MenuPokedex() {
    // Libere memória dos ponteiros
    delete apiDados;
    delete interface;
    delete pokedex;
}

void MenuPokedex::ConfigurarBtnMenu() {
    interface->ConfigurarBotoes(3, 0.3, 0.05, 0.5, 0.05);
    interface->GerarBotoes("menu", 3);
}

void MenuPokedex::ConfigurarBtnPokedex(int numBotoesCriados, int numPokemons, int offset) {
    interface->ConfigurarBotoes(6, 0.03, 0.01, 0.06, 0.01);
    interface->GerarBotoes("pokedex", numBotoesCriados, numPokemons, offset);
}

void MenuPokedex::ConfigurarBtnPokemonIndividual(int r, int g, int b) {
    interface->ConfigurarBotaoUnico(0.05, 0.45, 0.2, 0.1, r, g, b); // cor verde
    interface->GerarBotoes("pokemon_individual", 1);
}

void MenuPokedex::ConfigurarBtnTeamPokemon(int numPokemons) {
    interface->ConfigurarBotoes(6, 0.02, 0.01, 0.1, 0.05, 0.82);
    interface->GerarBotoes("teamPokemon", numPokemons, numPokemons, 0);
}

void MenuPokedex::EscreverPokemonIndividualBotao(int i) {
    string texto1 = "Adicionar";
    string texto2 = "na Equipe";
    float desloc = 0.0;
    if (i >= 0) {
        texto1 = "Remover";
        texto2 = "da Equipe";
        desloc = -0.008;

    }
    interface->DesenharTexto(0.105, 0.465, texto1);
    interface->DesenharTexto(0.105+desloc, 0.495, texto2);
}

void MenuPokedex::EscreverMenu() {
    interface->DesenharTexto(0.4 + 0.0505, 0.5 + 0.05,"Pokedex");
    interface->DesenharTexto(0.4 + 0.0455, 0.5 + 0.21,"Meu time");
    interface->DesenharTexto(0.4 + 0.075, 0.5 + 0.378,"Sair");
}

void MenuPokedex::EscreverTeamPokemon() {
    vector<int> dados = teamPokemon.getEstatisticas();

    interface->DesenharTexto(0.32, 0.01, "Estatisticas da Equipe Pokemon");
    int tamanho_team = teamPokemon.getQuantidadePokemons();

     

    if(tamanho_team > 0) {
        interface->DesenharRetangulo(0.22, 0.07, 0.73, 0.8, 122, 122, 122);

        interface->DesenharTexto(0.25, 0.1, "Status");
        interface->DesenharTexto(0.60, 0.1, "Soma");
        interface->DesenharTexto(0.85, 0.1, "Media");


        interface->DesenharTexto(0.25, 0.2, "HP: ");
        interface->DesenharTexto(0.62, 0.2, to_string(dados[0]));
        interface->DesenharTexto(0.87, 0.2, to_string(dados[0]/tamanho_team));

        interface->DesenharTexto(0.25, 0.3, "Attack: ");
        interface->DesenharTexto(0.62, 0.3, to_string(dados[1]));
        interface->DesenharTexto(0.87, 0.3, to_string(dados[1]/tamanho_team));

        interface->DesenharTexto(0.25, 0.4, "Defense: ");
        interface->DesenharTexto(0.62, 0.4, to_string(dados[2]));
        interface->DesenharTexto(0.87, 0.4, to_string(dados[2]/tamanho_team));

        interface->DesenharTexto(0.25, 0.5, "Special Attack: ");
        interface->DesenharTexto(0.62, 0.5, to_string(dados[3]));
        interface->DesenharTexto(0.87, 0.5, to_string(dados[3]/tamanho_team));

        interface->DesenharTexto(0.25, 0.6, "Special Defense: ");
        interface->DesenharTexto(0.62, 0.6, to_string(dados[4]));
        interface->DesenharTexto(0.87, 0.6, to_string(dados[4]/tamanho_team));

        interface->DesenharTexto(0.25, 0.7, "Speed: ");
        interface->DesenharTexto(0.62, 0.7, to_string(dados[5]));
        interface->DesenharTexto(0.87, 0.7, to_string(dados[5]/tamanho_team));

        int soma = dados[0] + dados[1] + dados[2] + dados[3] + dados[4] + dados[5];
        interface->DesenharTexto(0.25, 0.8, "Total: ");
        interface->DesenharTexto(0.62, 0.8, to_string(soma));
        interface->DesenharTexto(0.87, 0.8, to_string(soma/tamanho_team));
    }
    else {
        interface->DesenharTexto(0.3, 0.3, "Nenhum Pokemon foi adicionado a equipe!");
        interface->DesenharTexto(0.3, 0.35, "Entre na Pokedex e adicione o seu pokemon");
    }
}

void MenuPokedex::run() {
    ConfigurarBtnMenu();
    offset = 0;
    int offset_filtrado = 0;
    //string textoBusca = "";
    string ultimaBusca = "";
    int indice;
    int posicao = -1;//para saber se um pokemon está no time
    bool running = true;
    bool usandoFiltro = false;
    bool resetarNumBotoesPokedex = false;
    Estado ultimoEstado;
    vector<bool> estadosBotoes;
    while (running) {
        running = interface->VerificarEventos();
        
        if (estadoMenu == MENU) {
            interface->DesenharImagem(0.1, 0.1, logo_image);
            interface->DesenharBotoes();
            EscreverMenu();
            estadosBotoes = interface->GetBotoesEstados();
            offset_filtrado = 0;
            ultimoEstado = MENU;
            indice = -1;
            

            // Se o primeiro botão (índice 0) do menu for pressionado, entra na pokédex
            if (estadosBotoes.size() > 0 && estadosBotoes[0]) {
                estadoMenu = POKEDEX;
                interface->AtivarBtnVoltar(true);   // Ativa botão de voltar
                ConfigurarBtnPokedex(10, 1025, offset); // Configura os botões da Pokédex
            }

            if (estadosBotoes[1]) {
                estadoMenu = TEAM_POKEMON;
                interface->AtivarBtnVoltar(true);   // Ativa botão de voltar
                interface->AtivarBtnSave(true);
                int n = teamPokemon.getQuantidadePokemons();
                ConfigurarBtnTeamPokemon(n);

            }

            // Se o segundo botão for "Sair", por exemplo
            if (estadosBotoes.size() > 1 && estadosBotoes[2]) {
                running = false;
            }
        }

        else if (estadoMenu == POKEDEX) {
            if (usandoFiltro) { offset_filtrado = interface->getOffset(); }
            else { offset = interface->getOffset(); }

            estadosBotoes = interface->GetBotoesEstados();

            // Verificar o texto de busca
            string textoBusca = interface->getTextoBusca();
            usandoFiltro = (!textoBusca.empty() && textoBusca != "pesquisar");

            if (usandoFiltro && textoBusca != ultimaBusca) {
                offset_filtrado = 0;
                // Carregar pokemons filtrados se ainda não o fez ou se o texto mudou
                ultimaBusca = textoBusca;
                pokedex->carregarPokemonsFiltrados(textoBusca);
                int numPokemonsFiltrados = pokedex->getNumPokemonsFiltrados();
                if (numPokemonsFiltrados < 6) {
                    ConfigurarBtnPokedex(numPokemonsFiltrados, numPokemonsFiltrados);
                    resetarNumBotoesPokedex = true;
                }
                else { ConfigurarBtnPokedex(10, numPokemonsFiltrados, offset_filtrado); }
            }

            for (unsigned i = 0; i < estadosBotoes.size(); i++) {
                if (estadosBotoes[i]) {
                    indice = i;
                }
            }
            if (indice >= 0) {
                if (usandoFiltro) {
                    indice += offset_filtrado;
                    indice = pokedex->getIdPokemonFiltrado(indice);
                }
                else {
                    indice += offset;
                }
                ultimoEstado = estadoMenu;
                estadoMenu = POKEMON_INDIVIDUAL;
                posicao = teamPokemon(indice+1); // Usa a sobrecarga do operador ()
                if (posicao < 0) { ConfigurarBtnPokemonIndividual(73, 235, 52); }
                else { ConfigurarBtnPokemonIndividual(235, 64, 52); }
                
            }
            else { 
                interface->DesenharBotoes();
                if (usandoFiltro) {
                    
                    // Mostrar pokemons filtrados
                    pokedex->mostrarPokemonsFiltrados(offset_filtrado);
                } else {
                    // Mostrar todos pokemons
                    if (resetarNumBotoesPokedex) {
                        resetarNumBotoesPokedex = false;
                        ConfigurarBtnPokedex(10,1025,offset);
                        offset_filtrado = 0;
                    }
                    pokedex->mostrarPokemons(offset);
                }
                }

            if (interface->getVoltar()) {
                estadoMenu = MENU;
                interface->AtivarBtnVoltar(false);
                interface->clearTextoBusca();
                ultimaBusca = "";
                ConfigurarBtnMenu();
                
            }
        }

        else if (estadoMenu == POKEMON_INDIVIDUAL) {
            Pokemon novoPokemon = pokedex->mostrarUnicoPokemon(indice);
            interface->DesenharBotoes();

            EscreverPokemonIndividualBotao(posicao);

            estadosBotoes = interface->GetBotoesEstados();
            if (estadosBotoes[0]) {
                if (posicao < 0) { // O Pokémon não está na equipe
                    cout << "pokemon adicionado com sucesso" << endl;
                    teamPokemon.adicionarPokemon(novoPokemon);
                } else {
                    cout << "pokemon removido com sucesso" << endl;
                    teamPokemon.removerPokemon(posicao);
                }
                posicao = teamPokemon(indice+1); // Recalcula a posição do Pokémon
                if (posicao < 0) { ConfigurarBtnPokemonIndividual(73, 235, 52); }
                else { ConfigurarBtnPokemonIndividual(235, 64, 52); }
                interface->SetBotaoEstado(0, false);
            }
            
            if (interface->getVoltar()) {
                if (ultimoEstado == POKEDEX) {
                    estadoMenu = POKEDEX;
                    if (usandoFiltro) {
                        int numPokemonsFiltrados = pokedex->getNumPokemonsFiltrados();
                        if (numPokemonsFiltrados < 6) {
                            ConfigurarBtnPokedex(numPokemonsFiltrados, numPokemonsFiltrados, offset_filtrado);
                            resetarNumBotoesPokedex = true;
                        }
                        else { ConfigurarBtnPokedex(10, numPokemonsFiltrados, offset_filtrado); }
                    }
                    else {
                        ConfigurarBtnPokedex(10, 1025, offset);
                    }
                    
                    indice = -1;
                }
                else {
                    estadoMenu = TEAM_POKEMON;
                    interface->AtivarBtnSave(true);
                    int n = teamPokemon.getQuantidadePokemons();
                    ConfigurarBtnTeamPokemon(n);
                }
                indice = -1;
            }
        }
        

        else { // TEAM_POKEMON
            interface->DesenharBotoes();
            EscreverTeamPokemon();
            estadosBotoes = interface->GetBotoesEstados();
            ultimoEstado = TEAM_POKEMON;

            for (unsigned i = 0; i < estadosBotoes.size(); i++) {
                if (estadosBotoes[i]) {
                    indice = i;
                    posicao = i;
                }
            }

            if (indice >= 0) {
                vector<int> indicesPokemons = teamPokemon.getPokemonIndices();
                indice = indicesPokemons[indice]-1; // converte o indice do pokemon para o indice na pokedex (planilha)
                ultimoEstado = estadoMenu;
                estadoMenu = POKEMON_INDIVIDUAL;
                interface->AtivarBtnSave(false);
                ConfigurarBtnPokemonIndividual(235, 64, 52);//botao vermelho
            }

            vector<bool> saidasSave = interface->getBotoesSave();
            if (saidasSave[0]) { // salvando
                if (teamPokemon.salvarEquipe())
                    cout << "Equipe salva com sucesso!" << endl;
            }
            if (saidasSave[1]) { // carregando
                if (teamPokemon.carregarEquipe()) {
                    int n = teamPokemon.getQuantidadePokemons();
                    ConfigurarBtnTeamPokemon(n);
                    cout << "Equipe carregada com sucesso!" << endl;
                }
            }

            vector<Image> sprites = teamPokemon.getPokemonImagens(*interface);
            for (int i = 0; i < teamPokemon.getQuantidadePokemons(); i++) {
                interface->DesenharImagem(0.03, 0.1+0.143*i, sprites[i]);
            }

            if (interface->getVoltar()) {
                estadoMenu = MENU;
                interface->AtivarBtnVoltar(false); 
                interface->AtivarBtnSave(false); // desativa o botão de salvar
                interface->clearTextoBusca();
                ultimaBusca = "";
                ConfigurarBtnMenu(); 
                indice = -1; // resetar indice
            }
        }
        interface->Atualizar(); // atualiza a imagem da janela
    }
}
