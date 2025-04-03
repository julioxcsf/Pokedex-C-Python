/* 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 

    Implementação dos métofos das classes Pokedex

*/

#include "pokedex.h"
#include <sstream>
#include <iostream>

Pokedex::Pokedex(API_Dados& apiDados, InterfaceGrafica& interfaceGrafica)
    : apiDados(apiDados), interfaceGrafica(interfaceGrafica), total_pokemons(0) {
    carregarTodosPokemons();
    carregarPokemonsSprites(offset);
}

void Pokedex::carregarTodosPokemons() {
    std::vector<std::vector<std::string>> dados = apiDados.lerDadosCompleto();

    for (const std::vector<std::string>& linha : dados) {
        if (linha.size() < 2) continue;

        std::string valor_str = linha[0];
        double val;
        {
            std::istringstream iss(valor_str);
            if (!(iss >> val)) {
                // Não conseguiu ler como número, pular
                continue;
            }
        }

        // Checar se val é inteiro
        double floored = std::floor(val);
        if (floored == val) {
            int indice = static_cast<int>(val);
            std::string nome = linha[1];
            todosPokemons.emplace_back(indice, nome);
        }
        // Se não for inteiro, simplesmente não adiciona
    }
    total_pokemons = (int)todosPokemons.size();
    std::cout << "Carreguei " << total_pokemons << " pokemons." << std::endl;
}


void Pokedex::carregarPokemonsSprites(int offset) {
    for (int i = 1; i <= 1025; i++) { //1024
        string pokemon_image_path = "./Images/sprites/pokemon/" + to_string(i) + ".png";
        Image sprite = interfaceGrafica.carregarImagemLocal(pokemon_image_path, 0.15, 0.15);
        pokemonSprites.push_back(sprite);
    }
}

void Pokedex::mostrarPokemons(int offset) {
    for (int i = 0; i < numBotoes; i++) {
        int idx = (offset + i) % total_pokemons;
        Pokemon& p = todosPokemons[idx];

        std::pair<float, float> pos = interfaceGrafica.getPosBotao(i);
        float nx = pos.first;
        float ny = pos.second;

        interfaceGrafica.DesenharImagem(nx, ny, pokemonSprites[idx]); // Desenha o sprite do pokemon
        interfaceGrafica.DesenharTexto(nx + 0.15, ny+0.05, p.getNome()); // Desenha o nome do Pokemon no botão
        string texto = "No. "+to_string(idx+1);
        interfaceGrafica.DesenharTexto(nx + 0.35, ny+0.05, texto); // Desenha o número do Pokemon no botão


        // Poderia também desenhar imagem chamando p.getImagem(interfaceGrafica) e depois interfaceGrafica.DesenharImagem(nx, ny, imagem) com ajustes.

        //codigo que mostra barra de pesquisa e botão de voltar
    }
}

Pokemon Pokedex::mostrarUnicoPokemon(int indice) {
    // Obtem referência ao pokemon desejado
    Pokemon& p = todosPokemons[indice];
    int pokemonID = p.getID(); // Este ID é o número da Pokédex do Pokémon

    // Agora busca os dados completos do Pokémon na planilha via API
    // Suponha que a função: vector<vector<string>> API_Dados::lerDadosPorIDPokemon(int idPokemon)
    // foi implementada conforme descrito anteriormente.
    auto dadosPokemon = apiDados.lerDadosPorIDPokemon(pokemonID);

    // Caso não encontre ou dê algum problema, tratar o retorno
    if (dadosPokemon.empty()) {
        std::cerr << "Nenhum dado encontrado para o Pokémon com ID " << pokemonID << std::endl;
        return Pokemon(pokemonID, "Desconhecido");
    }

    // Espera-se que 'dadosPokemon' tenha apenas uma linha, pois filtramos por ID único
    const auto& linha = dadosPokemon[0];

    // Carrega a imagem do Pokémon
    std::string pokemon_image_path = "./Images/sprites/pokemon/" + std::to_string(pokemonID) + ".png";
    Image sprite = interfaceGrafica.carregarImagemLocal(pokemon_image_path, 0.4, 0.4);
    interfaceGrafica.DesenharRetangulo(0.3, 0.05, 0.4, 0.5, 120, 120, 120); // para a imagem e nome
    interfaceGrafica.DesenharRetangulo(0.3, 0.575, 0.4, 0.375, 120, 120, 120); // para os dados
    interfaceGrafica.DesenharImagem(0.3, 0.07, sprite);

    // Desenha os retangulos do tipos do pokemon
    if (linha[10] != "nan") { //tem 2 tipos
        interfaceGrafica.DesenharRetanguloType(0.34, 0.475, 0.15, 0.05, linha[9]);
        interfaceGrafica.DesenharRetanguloType(0.51, 0.475, 0.15, 0.05, linha[10]);
    }
    else {
        interfaceGrafica.DesenharRetanguloType(0.425, 0.475, 0.15, 0.05, linha[9]);
    }

    // Desenha o nome do Pokémon
    std::string nomePokemon = "Nome:" + linha[1]; // Nome do Pokémon obtido da planilha
    interfaceGrafica.DesenharTexto(0.325, 0.06, nomePokemon);

    // Desenha o número do Pokémon
    std::string texto = "No. " + std::to_string(pokemonID);
    interfaceGrafica.DesenharTexto(0.6, 0.06, texto);

    // Exibir outras informações, por exemplo, tipo(s), altura, peso, etc. conforme as colunas lidas
    // Digamos que linha[2] = Tipo, linha[3] = Altura, linha[4] = Peso, ...
    // Ajuste as posições conforme sua planilha.
    if (linha.size() > 2) {
        interfaceGrafica.DesenharTexto(0.32, 0.6, "HP: ");
        interfaceGrafica.DesenharTexto(0.65, 0.6, linha[2]);
    }

    if (linha.size() > 3) {
        float attack = std::stof(linha[3]);
        interfaceGrafica.DesenharTexto(0.32, 0.65, "Attack: ");
        interfaceGrafica.DesenharTexto(0.65, 0.65, to_string((int)attack));
    }

    if (linha.size() > 4) {
        interfaceGrafica.DesenharTexto(0.32, 0.7, "Defense: ");
        interfaceGrafica.DesenharTexto(0.65, 0.7, linha[4]);
    }

    if (linha.size() > 5) {
        interfaceGrafica.DesenharTexto(0.32, 0.75, "Special Attack: ");
        interfaceGrafica.DesenharTexto(0.65, 0.75, linha[5]);

    }

    if (linha.size() > 6) {
        interfaceGrafica.DesenharTexto(0.32, 0.8, "Special Defense: ");
        interfaceGrafica.DesenharTexto(0.65, 0.8, linha[6]);
    }

    if (linha.size() > 7) {
        interfaceGrafica.DesenharTexto(0.32, 0.85, "Speed: ");
        interfaceGrafica.DesenharTexto(0.65, 0.85, linha[7]);
    }

    if (linha.size() > 8) {
        interfaceGrafica.DesenharTexto(0.32, 0.90, "Total: ");
        interfaceGrafica.DesenharTexto(0.65, 0.90, linha[8]);
    }
    
    // Agora, criar um objeto Pokémon retornável com todos os dados necessários:
    // Convertendo valores obtidos da string para float
    int hp = std::stoi(linha[2]);
    int attack = std::stoi(linha[3]);
    int defense = std::stoi(linha[4]);
    int spAttack = std::stoi(linha[5]);
    int spDefense = std::stoi(linha[6]);
    int speed = std::stoi(linha[7]);

    Pokemon pokemonRetorno(pokemonID, linha[1], hp, attack, defense, spAttack, spDefense, speed);

    // Definir os tipos do Pokémon
    std::string type1 = (linha.size() > 9) ? linha[9] : "";
    std::string type2 = (linha.size() > 10) ? linha[10] : ""; //(hasSecondType) ? linha[10] : "";
    pokemonRetorno.setTypes(type1, type2);

    // Retorna o objeto Pokemon completo
    return pokemonRetorno;
}

void Pokedex::carregarPokemonsFiltrados(const std::string& filtro) {
    pokemonsFiltrados.clear();
    indicesPokemonsFiltrados.clear();
    std::vector<std::vector<std::string>> dados = apiDados.lerDadosFiltrados(filtro);

    for (const std::vector<std::string>& linha : dados) {
        if (linha.size() < 2) continue;

        std::string valor_str = linha[0];
        double val;
        {
            std::istringstream iss(valor_str);
            if (!(iss >> val)) {
                continue;
            }
        }

        double floored = std::floor(val);
        if (floored == val) {
            int indice = static_cast<int>(val);
            indicesPokemonsFiltrados.push_back(indice-1);//experimentalmente observei que o numero era 1 acima
            std::string nome = linha[1];
            pokemonsFiltrados.emplace_back(indice, nome);//chat, acho que posso apenas adicionar o pokemon aqui, certo?
        }
    }
    //cout << "Numero de pokemons encontrados: " << pokemonsFiltrados.size() << endl;
    //cout << "Filtro: " << filtro << endl;
}

int Pokedex::getIdPokemonFiltrado(int pokemonID) {
    return indicesPokemonsFiltrados[pokemonID];
}

void Pokedex::mostrarPokemonsFiltrados(int offset) {
    int total_filtrados = (int)pokemonsFiltrados.size();

    // Limita o número de botões exibidos ao total de Pokémons filtrados
    int botoes_exibir = std::min(numBotoes, total_filtrados - offset);

    for (int i = 0; i < botoes_exibir; i++) {
        int idx = offset + i;

        if (idx >= total_filtrados) break;

        Pokemon& p = pokemonsFiltrados[idx];
        std::pair<float, float> pos = interfaceGrafica.getPosBotao(i);
        float nx = pos.first;
        float ny = pos.second;

        int spriteIndex = indicesPokemonsFiltrados[idx]; // Acessa o índice correto do sprite
        interfaceGrafica.DesenharImagem(nx, ny, pokemonSprites[spriteIndex]); 
        interfaceGrafica.DesenharTexto(nx + 0.15, ny + 0.05, p.getNome()); 

        std::string texto = "No. " + std::to_string(p.getID());
        interfaceGrafica.DesenharTexto(nx + 0.45, ny + 0.05, texto); 
    }
}

int Pokedex::getNumPokemonsFiltrados() {
    return (int)pokemonsFiltrados.size();
}