/* 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 

    Declaração da classe InterfaceGrafica
    Usada como API para classe e metodos declarados no arquivo Lib_Janela.py

*/

#ifndef API_GRAFICA_H
#define API_GRAFICA_H

#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <vector>
#include <string>

typedef pybind11::object Image; //facilita o manuseio de imagens

namespace py = pybind11;
using namespace std;

class InterfaceGrafica {
    public:
        InterfaceGrafica(int largura = 800, int altura = 600, string textoJanela = "Janela API C++/Python", int r = 20, int g = 40, int b = 60);
        ~InterfaceGrafica();

        //para configuracao de imagem
        void trocarTelaCheia();

        // =======================operacoes de desenho==========================
        // OBS: todos os metodos usam posicao normalizada na tela: de -1.0 a 1.0
        void DesenharImagem(float, float, Image);
        void DesenharTexto(float, float, string);

        // =======================operacoes de botoes===========================
        
        void ConfigurarBotoes(int n, float margemX, float distanciamentoY, float margemYsuperior, float margemYinferior, float margemXdireita = 0);
        void ConfigurarBotaoUnico(float x, float y, float l, float h, int r, int g, int b);
        void GerarBotoes(string tipo = "pokedex",int numBotoes = 6, int numPokemons = 1025, int offset = 0);
        void DesenharBotoes();
        void DesenharRetangulo(float x, float y, float largura, float altura, int r, int g, int b);
        void DesenharRetanguloType(float x, float y, float largura, float altura, string tipo);
        vector<bool> GetBotoesEstados();
        void SetBotaoEstado(int indice, bool estado);
        std::pair<float,float> getPosBotao(int i); //----------------------em teste
        int getOffset();

        bool getVoltar();
        void AtivarBtnVoltar(bool estado);
        void AtivarBtnSave(bool estado);
        vector<bool> getBotoesSave();
        string getTextoBusca();
        void clearTextoBusca();

        //void DesenharBotao(/*localização,texto*/);

        void Atualizar();
        void Fechar();
        bool VerificarEventos();
        void MudarFont(int);
        int get_dy();

        //void ReceberEntrada(/**/);
        
        Image carregarImagemLocal(string caminho, float larguraDesejada, float alturadesejada);

    private:
        py::module PySource_LibJanela;
        py::object Window;//recebe o objeto da classe python Janela
        int larguraDesenho,alturaDesenho;//se a janela for modificada, tenho que atualizar isso...
        int desnormalizar(float valor,char eixo);

};

#endif // API_GRAFICA_H