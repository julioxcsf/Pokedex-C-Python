/* 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 

    Implementação dos métodos da classe TeamPokemon
*/

#include "teamPokemon.h"
#include <fstream>   // para ofstream/ifstream (leitura e escrita em arquivo)
#include <iostream>  // para std::cerr
#include <stdexcept> // para exceções caso necessário

// Função auxiliar para atualizar as estatísticas médias do time
void TeamPokemon::atualizarEstatisticas() {
    if (team.empty()) {
        num_pokemons = 0;
        soma_hp_equipe = 0;
        soma_attack_equipe = 0;
        soma_defense_equipe = 0;
        soma_spAttack_equipe = 0;
        soma_spDefense_equipe = 0;
        soma_speed_equipe = 0;
        return;
    }

    // Resetar as somas antes de recalcular
    soma_hp_equipe = 0;
    soma_attack_equipe = 0;
    soma_defense_equipe = 0;
    soma_spAttack_equipe = 0;
    soma_spDefense_equipe = 0;
    soma_speed_equipe = 0;

    for (auto &p : team) {
        soma_hp_equipe += p.getHP();           // Supondo métodos getHP, getAttack, etc
        soma_attack_equipe += p.getAttack();
        soma_defense_equipe += p.getDefense();
        soma_spAttack_equipe += p.getSpAttack();
        soma_spDefense_equipe += p.getSpDefense();
        soma_speed_equipe += p.getSpeed();
    }
}

void TeamPokemon::adicionarPokemon(Pokemon pokm) {
    // Corrigindo a condição: se size() == 6, já temos 6 pokémons, então não adicionar mais
    if (team.size() < 6) {
        team.push_back(pokm);
        atualizarEstatisticas();
    } else {
        std::cerr << "Equipe ja possui 6 Pokemons, nao eh possivel adicionar mais.\n";
    }
}

void TeamPokemon::removerPokemon(unsigned int indice) {
    if (indice < team.size()) {
        team.erase(team.begin() + indice);
        atualizarEstatisticas();
    } else {
        std::cerr << "Indice invalido para remocao.\n";
    }
}

int TeamPokemon::getQuantidadePokemons () {
    return static_cast<int>(team.size());
}

vector<int> TeamPokemon::getEstatisticas() {
    vector<int> estatisticas;
    estatisticas.push_back(soma_hp_equipe);
    estatisticas.push_back(soma_attack_equipe);
    estatisticas.push_back(soma_defense_equipe);
    estatisticas.push_back(soma_spAttack_equipe);
    estatisticas.push_back(soma_spDefense_equipe);
    estatisticas.push_back(soma_speed_equipe);

    return estatisticas;
}

vector<int> TeamPokemon::getPokemonIndices() {
    vector<int> indices;
    for (unsigned i = 0; i < team.size(); i++) {
        indices.push_back(team[i].getID());
    }
    return indices;
}

vector<Image> TeamPokemon::getPokemonImagens(InterfaceGrafica& interfaceGrafica) {
    vector<Image> imagens;
    string pokemon_image_path = "";
    for (unsigned i=0; i < team.size(); i++) {
        pokemon_image_path =  "./Images/sprites/pokemon/" + std::to_string(team[i].getID()) + ".png";
        Image sprite = interfaceGrafica.carregarImagemLocal(pokemon_image_path, 0.133, 0.133);
        imagens.push_back(sprite);
    }
    return imagens;
}

int TeamPokemon::operator()(int PokemonID) const {
    for (unsigned i = 0; i < team.size(); ++i) {
        if (team[i].getID() == PokemonID) { // Verifica se o índice coincide
            return static_cast<int>(i); // Retorna a posição no vetor
        }
    }
    return -1; // Não encontrado
}


bool TeamPokemon::salvarEquipe() {
    // Salva equipe em um arquivo padrão, por exemplo "team.save"
    std::string filename = "team.save";
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        std::cerr << "Nao foi possivel abrir " << filename << " para escrita.\n";
        return false;
    }

    ofs << team.size() << "\n";
    for (auto &p : team) {
        ofs << p.getID() << " "
            << p.getNome() << " "
            << p.getHP() << " "
            << p.getAttack() << " "
            << p.getDefense() << " "
            << p.getSpAttack() << " "
            << p.getSpDefense() << " "
            << p.getSpeed() << "\n";
    }

    ofs.close();
    return true;
}

bool TeamPokemon::carregarEquipe() {
    // Carrega equipe do arquivo "team.save"
    std::string filename = "team.save";
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "Nao foi possivel abrir " << filename << " para leitura.\n";
        return false;
    }

    team.clear(); // Limpa equipe atual antes de carregar
    unsigned int qtd;
    ifs >> qtd;
    team.reserve(qtd);

    for (unsigned int i = 0; i < qtd; i++) {
        std::string nome;
        int ID, hp, attack, defense, spAttack, spDefense, speed;
        ifs >> ID >> nome >> hp >> attack >> defense >> spAttack >> spDefense >> speed;
        
        // Constrói Pokémon com os dados lidos
        Pokemon p(ID, nome, hp, attack, defense, spAttack, spDefense, speed);
        team.push_back(p);
    }

    ifs.close();

    atualizarEstatisticas();
    return true;
}