/* 
    Ling. Prog. 2024-2 Trabalho Final
    Programa da Pokedex C++/Python
    Autor: Julio Cesar S. Fernandes
    data: 18/12/2024 

    main.cpp

*/

#include <iostream>
#include "menuPokedex.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

int main() {
    py::scoped_interpreter guard{}; // Inicializa o interpretador Python
    MenuPokedex menuPokedex;
    menuPokedex.run();
    return 0;
}
