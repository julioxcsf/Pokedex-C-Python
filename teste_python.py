''' 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 

'''

import pygame
#from Lib_janela import Janela  # Supondo que a classe está no arquivo 'classes.py'
from Lib_janela import * #importa todas as funcoes


def main():
    # Cria uma instância da janela
    janela = Janela(800, 600, "Minha Janela", 20, 30, 60)
    janela.Iniciar()

    rodando = True

    imagem = CarregarImagem("./Images/sprites/pokemon/other/home/25.png",250,250)

    while rodando:
        
        janela.Escrever("Olá, Mundo!", 400, 300)

        janela.Atualizar()

        janela.DesenharImagem(imagem,50,50)

        rodando = janela.ProcessarEventos()

    # Fecha a janela após sair do loop
    janela.Fechar()

if __name__ == "__main__":
    main()


