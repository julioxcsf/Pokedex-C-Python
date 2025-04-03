/* 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 
    implementação da API por meio dos métodos
    da classe API_Dados
    
*/

#include "API_dados.h"
#include <iostream>

using namespace std;

API_Dados::API_Dados() {
    try {
        data_reader_module = py::module::import("data_reader");
    } catch (const py::error_already_set& e) {
        cerr << "Erro ao importar o modulo Python: " << e.what() << endl;
    }
}

API_Dados::~API_Dados() {
    // O interpretador Python será finalizado automaticamente pelo py::scoped_interpreter no main
}

vector<vector<string>> API_Dados::lerDadosCompleto() {
    vector<vector<string>> dados_resultantes;

    try {
        py::object resultado = data_reader_module.attr("ler_excel_completo")();
        py::list resultado_list = resultado.cast<py::list>(); // Conversão explícita para py::list

        Py_ssize_t num_linhas = py::len(resultado_list);

        for (Py_ssize_t i = 0; i < num_linhas; i++) {
            py::object linha_obj = resultado_list[i];
            py::list linha_list = linha_obj.cast<py::list>();

            vector<string> linha_vector;
            Py_ssize_t num_colunas = py::len(linha_list);

            for (Py_ssize_t j = 0; j < num_colunas; j++) {
                py::object valor = linha_list[j];
                std::string valor_str = py::str(valor);
                linha_vector.push_back(valor_str);
            }

            dados_resultantes.push_back(linha_vector);
        }

    } catch (const py::error_already_set& e) {
        std::cerr << "Erro ao chamar a funcao ler_excel_completo: " << e.what() << std::endl;
    }

    return dados_resultantes;
}

vector<vector<string>> API_Dados::lerDadosPorIDPokemon(int id_pokemon) {
    vector<vector<string>> dados_resultantes;

    try {
        // Chama a função Python passando o ID
        py::object resultado = data_reader_module.attr("ler_excel_por_id_pokemon")(id_pokemon);

        py::list resultado_list = resultado.cast<py::list>();
        Py_ssize_t num_linhas = py::len(resultado_list);

        for (Py_ssize_t i = 0; i < num_linhas; i++) {
            py::object linha_obj = resultado_list[i];
            py::list linha_list = linha_obj.cast<py::list>();

            vector<string> linha_vector;
            Py_ssize_t num_colunas = py::len(linha_list);

            for (Py_ssize_t j = 0; j < num_colunas; j++) {
                py::object valor = linha_list[j];
                std::string valor_str = py::str(valor);
                linha_vector.push_back(valor_str);
            }

            dados_resultantes.push_back(linha_vector);
        }

    } catch (const py::error_already_set& e) {
        std::cerr << "Erro ao chamar a funcao ler_excel_por_id_pokemon: " << e.what() << std::endl;
    }

    return dados_resultantes;
}

vector<vector<string>> API_Dados::lerDadosFiltrados(string textofiltro) {
    vector<vector<string>> dados_resultantes;

    try {
        // Use a variável textofiltro em vez de "textofiltro"
        py::object resultado = data_reader_module.attr("ler_excel_filtrado")(textofiltro);
        py::list resultado_list = resultado.cast<py::list>();

        Py_ssize_t num_linhas = py::len(resultado_list);

        for (Py_ssize_t i = 0; i < num_linhas; i++) {
            py::object linha_obj = resultado_list[i];
            py::list linha_list = linha_obj.cast<py::list>();

            vector<string> linha_vector;
            Py_ssize_t num_colunas = py::len(linha_list);

            for (Py_ssize_t j = 0; j < num_colunas; j++) {
                py::object valor = linha_list[j];
                std::string valor_str = py::str(valor);
                linha_vector.push_back(valor_str);
            }

            dados_resultantes.push_back(linha_vector);
        }

    } catch (const py::error_already_set& e) {
        std::cerr << "Erro ao chamar a funcao ler_excel_filtrado: " << e.what() << std::endl;
    }

    return dados_resultantes;
}