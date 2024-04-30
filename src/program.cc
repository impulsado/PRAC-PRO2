#include <iostream>
#include <string>
#include "BinTree.hh"

using namespace std;

void leer_rio(BinTree<string>& t);
void leer_inventario();

int main () {
    BinTree<string> cuenca;

    string usr_op;
    while (cin >> usr_op and usr_op!="fin") {
        if (usr_op=="leer_rio" or usr_op=="lr") leer_rio(cuenca);
        else if (usr_op=="leer_inventario" or usr_op=="li") leer_inventario();
        else if (usr_op=="leer_inventarios" or usr_op=="ls");
        else if (usr_op=="modificar_barco" or usr_op=="mb");
        else if (usr_op=="escribir_barco" or usr_op=="eb");
        else if (usr_op=="consultar_num" or usr_op=="cn");
        else if (usr_op=="agregar_productos" or usr_op=="ap");
        else if (usr_op=="poner_prod" or usr_op=="pp");
        else if (usr_op=="modificar_prod" or usr_op=="mp");
        else if (usr_op=="consultar_prod" or usr_op=="cp");
        else if (usr_op=="comerciar" or usr_op=="co");
        else if (usr_op=="redistribuir" or usr_op=="re");
        else if (usr_op=="hacer_viaje" or usr_op=="hv");
    }
}