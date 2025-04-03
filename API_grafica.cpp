/* 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 

    Implementação da API gráfica por meio dos métodos
    da classe InterfaceGrafica
*/

#include "API_grafica.h"

InterfaceGrafica::InterfaceGrafica(int largura,int altura, string textoJanela, int r, int g, int b) {
    //py::scoped_interpreter guard{}; // Inicializa o interpretador Python    // tenho que usar na main.cpp
    PySource_LibJanela = py::module::import("Lib_janela");
    PySource_LibJanela.attr("IniciarPygame")();
    larguraDesenho = largura;
    alturaDesenho = altura;
    Window = PySource_LibJanela.attr("Janela")(largura, altura, textoJanela, r, g, b);
    Window.attr("Iniciar")();
}

InterfaceGrafica::~InterfaceGrafica() {
    Window.attr("Fechar")();
}

int InterfaceGrafica::desnormalizar(float valor, char eixo) {
    if (eixo == 'x') {
        return static_cast<int>(valor * larguraDesenho);
    }
    else if (eixo == 'y') {
        return static_cast<int>(valor * alturaDesenho);
    }
    else return 0;
}

void InterfaceGrafica::trocarTelaCheia() {
    Window.attr("TelaCheia")();
}

void InterfaceGrafica::Atualizar() {
    Window.attr("Atualizar")();
}

void InterfaceGrafica::Fechar() {
    Window.attr("Fechar")();
}

bool InterfaceGrafica::VerificarEventos() {
    return Window.attr("ProcessarEventos")().cast<bool>();
}

void InterfaceGrafica::MudarFont(int tamanho) {
    Window.attr("DefinirFont")(tamanho);
}

int InterfaceGrafica::get_dy() {
    return Window.attr("get_dy")().cast<int>();
}

void InterfaceGrafica::DesenharImagem(float Xpos, float Ypos, Image imagem) {
    Xpos = desnormalizar(Xpos,'x');
    Ypos = desnormalizar(Ypos,'y');
    Window.attr("DesenharImagem")(imagem, Xpos, Ypos);
}

void InterfaceGrafica::DesenharTexto(float Xpos, float Ypos, string texto) {
    Xpos = desnormalizar(Xpos,'x');
    Ypos = desnormalizar(Ypos,'y');
    Window.attr("Escrever")(texto,Xpos,Ypos);
}


void InterfaceGrafica::ConfigurarBotoes(int n, float margemX, float distanciamentoY, float margemYsuperior, float margemYinferior, float margemXdireita) {
    Window.attr("SetConfigBotoes")(n, margemX, distanciamentoY, margemYsuperior, margemYinferior, margemXdireita);
}

void InterfaceGrafica::ConfigurarBotaoUnico(float x, float y, float largura, float altura, int r, int g, int b) {
    x = desnormalizar(x,'x');
    y = desnormalizar(y,'y');
    largura = desnormalizar(largura, 'x');
    altura = desnormalizar(altura, 'y');
    Window.attr("SetConfigBotaoUnico")(x, y, largura, altura, r, g, b);
}

void InterfaceGrafica::GerarBotoes(string tipo, int numBotoes, int numPokemons, int offset) {
    Window.attr("AdicionarBotoes")(tipo, numBotoes, numPokemons, offset);
}

void InterfaceGrafica::DesenharBotoes() {
    Window.attr("DesenharBotoes")();
}

void InterfaceGrafica::DesenharRetangulo(float x, float y, float largura, float altura, int r, int g, int b){
    x = desnormalizar(x,'x');
    y = desnormalizar(y,'y');
    largura = desnormalizar(largura, 'x');
    altura = desnormalizar(altura, 'y');
    Window.attr("DesenharRect")(x, y, largura, altura, r, g, b);
}

void InterfaceGrafica::DesenharRetanguloType(float x, float y, float largura, float altura, string tipo) {
    x = desnormalizar(x,'x');
    y = desnormalizar(y,'y');
    largura = desnormalizar(largura, 'x');
    altura = desnormalizar(altura, 'y');
    Window.attr("DesenharTipo")(x, y, largura, altura, tipo);
}

vector<bool> InterfaceGrafica::GetBotoesEstados() {
    return Window.attr("getEstadosBotoes")().cast<vector<bool>>();
}

void InterfaceGrafica::SetBotaoEstado(int indice, bool estado) {
    Window.attr("SetBotaoEstado")(indice, estado);
}

std::pair<float,float> InterfaceGrafica::getPosBotao(int i) {
    auto tup = Window.attr("GetBotaoPos")(i).cast<std::pair<float,float>>();
    return tup;
}

int InterfaceGrafica::getOffset() {
    return Window.attr("GetOffset")().cast<int>();
}

bool InterfaceGrafica::getVoltar() {
    return Window.attr("getBtnVoltaEstado")().cast<int>();
}

void InterfaceGrafica::AtivarBtnVoltar(bool estado) {
    Window.attr("AtivarBackButton")(estado);
}

void InterfaceGrafica::AtivarBtnSave(bool estado) {
    Window.attr("AtivarSaveLoadButtons")(estado);    
}

vector<bool> InterfaceGrafica::getBotoesSave() {
    return Window.attr("getSaveLoadStates")().cast<vector<bool>>();
}

string InterfaceGrafica::getTextoBusca() {
    return Window.attr("GetInputText")().cast<string>();
}
        
void InterfaceGrafica::clearTextoBusca() {
    Window.attr("LimparInputText")();
}

Image InterfaceGrafica::carregarImagemLocal(string caminho, float larguraDesejada, float alturadesejada) {
    larguraDesejada = desnormalizar(larguraDesejada,'x');
    alturadesejada = desnormalizar(alturadesejada,'y');
    return PySource_LibJanela.attr("CarregarImagem")(caminho, larguraDesejada, alturadesejada).cast<Image>();
}