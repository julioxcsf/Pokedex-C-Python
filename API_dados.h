/* 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar
    Declaração da classe API_dados
    usada como API para acessar dados da Pokedex na planilha

*/

#ifndef API_DADOS_H
#define API_DADOS_H

#include <pybind11/embed.h>
#include <vector>
#include <string>

namespace py = pybind11;
using namespace std;

class API_Dados {
    public:
        API_Dados();
        ~API_Dados();

        // Antes: lerDadosExcel(linhas, colunas)
        // Agora: Uma função para carregar TUDO de uma vez
        vector<vector<string>> lerDadosCompleto();
        vector<vector<string>> lerDadosPorIDPokemon(int id_pokemon);
        vector<vector<string>> lerDadosFiltrados(string textofiltro);

    private:
        py::object data_reader_module;  // Módulo Python
};


#endif // API_DADOS_H
