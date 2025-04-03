# 📘 Pokédex C++/Python

Trabalho final da disciplina de Linguagens de Programação (UFRJ), consistindo em um programa em C++ com integração ao Python para leitura e exibição de dados de uma Pokédex da 9ª geração.

---

## 🖼️ Exemplos de Interface

Abaixo, algumas capturas de tela do funcionamento da Pokédex e do gerenciamento de equipe no programa:

### 🧭 Menu Inicial

![Menu Inicial](Images/menu-inicial.png)

---

### 🔍 Exemplo de Filtro de Pokémon

Busca por nome parcial ou completo:

![Filtro 1](Images/exemplo-de-filtro1.png)  
![Filtro 2](Images/exemplo-de-filtro2.png)

---

### 🧠 Gestão de Equipe

Estado inicial da equipe:

![Equipe vazia](Images/equipe-vazia.png)

Equipe montada com até 6 Pokémon:

![Equipe montada](Images/equipe-montada.png)

---

### 🌀 Status de um Pokémon

Visualização de um Pokémon **dentro** e **fora** da equipe:

- Dentro da equipe:  
  ![Porygon-Z na Equipe](Images/Porygon-Z_naEquipe.png)

- Fora da equipe:  
  ![Porygon-Z fora da Equipe](Images/Porygon-Z_foraDaEquipe.png)

## 🚀 Como Usar o Programa

### ✅ Requisitos

Certifique-se de que os seguintes itens estão instalados no sistema:

- `g++` (compilador C++)
- `make`
- `Python 3.11` (ou ajuste no `Makefile` caso tenha versão diferente)
- Bibliotecas Python:
  - `pygame`
  - `pandas`

Você pode instalar as bibliotecas com:

```bash
pip install pygame pandas
```

Para compilar o programa com:
```bash
make
```

Para executar o programa com:
```bash
./Pokedex-V1
```
