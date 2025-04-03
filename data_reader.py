''' 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 

'''

import pandas as pd
import os

# Define o caminho para o arquivo Excel
diretorio_atual = os.path.dirname(os.path.abspath(__file__))
caminho_arquivo = os.path.join(diretorio_atual, 'NationalPokedexGen9.xlsx')

def ler_excel_por_id_pokemon(id_pokemon):
    # Colunas desejadas
    colunas = [0,1,34,35,36,37,38,39,40,41,42]
    df = pd.read_excel(caminho_arquivo, header=0, usecols=colunas)

    # Filtra o DataFrame para pegar apenas a linha cujo valor da coluna[0] seja igual ao id_pokemon
    # Aqui assumimos que a primeira coluna (índice 0) corresponde à ID do Pokémon. Ajuste se necessário.
    df_filtrado = df[df.iloc[:,0] == id_pokemon]

    # Se não encontrar nada, retorna uma lista vazia ou trate de outra forma
    if df_filtrado.empty:
        return []

    # Retorna a linha encontrada em formato de lista de listas (mesmo padrão de retorno dos outros métodos)
    return df_filtrado.values.tolist()

def ler_excel_completo():
    # Carregar a planilha inteira ou as colunas desejadas
    # Suponha que seu excel tenha pelo menos 2 colunas: ID, Nome
    df = pd.read_excel('NationalPokedexGen9.xlsx', usecols=[0,1])  # Ajuste conforme necessário
    return df.values.tolist()  # Lista de listas

def ler_excel_filtrado(texto_busca):
    # Carrega as colunas que você precisa (por exemplo, ID e Name)
    # Ajuste o usecols de acordo com as colunas exatas do seu Excel.
    # Supondo que a primeira coluna (ID) é a coluna 0 e a segunda (Name) é a coluna 1
    df = pd.read_excel(caminho_arquivo, header=0, usecols=[0,1])

    # Renomeia para um padrão simples caso necessário
    # Supondo que as colunas originais sejam algo como:
    # "National Pokédex Number" e "Name"
    df.columns = ["ID", "Name"]

    # Converte tudo para minúsculas para a busca
    texto_busca = texto_busca.lower()
    df['Name'] = df['Name'].str.lower()

    # Filtra as linhas que começam com o texto_busca
    nomes_filtrados = df[df['Name'].str.startswith(texto_busca, na=False)]

    # Retorna [ [ID, Nome], [ID, Nome], ... ]
    return nomes_filtrados.values.tolist()


# ================TESTE============================================================
# Exemplo: Ler linhas de 0 a 49 e colunas 1 e 3
#linhas_desejadas = range(0, 1025)   # Primeiras 50 linhas
#colunas_desejadas = [0, 1, 41 ,42]        # Colunas específicas (por índice)
#dados = ler_excel_completo()
#print("printando tudo\n")
#pd.set_option('display.max_rows', None)
#print(dados)

#print("\nprintando filtrado\n")
#dados = ler_excel_filtrado("xa")

#print(dados)
