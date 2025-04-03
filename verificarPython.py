''' 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 

'''

#funçoes que serao usadas para confirmar que o ambiente suporta a execução do programa.

import importlib.util

def verificar_biblioteca(nome):
    """Verifica se uma biblioteca está instalada.
       Retorna True se estiver instalada, False se não estiver."""
    spec = importlib.util.find_spec(nome)
    if spec is None:
        print(f"Biblioteca '{nome}' não está instalada.")
        print(f"Para instalar '{nome}', execute:")
        print(f"  pip install {nome}")
        return False
    return True

def main():
    # Lista de bibliotecas a serem verificadas
    bibliotecas = ["pybind11", "openpyxl", "pygame", "pandas"]
    resultados = {}

    for biblioteca in bibliotecas:
        resultados[biblioteca] = verificar_biblioteca(biblioteca)

    # Retorna o status como um dicionário de resultados
    return resultados

if __name__ == "__main__":
    status = main()
    print("\nStatus das bibliotecas:")
    for biblioteca, estado in status.items():
        print(f"{biblioteca}: {'True' if estado else 'False'}")
