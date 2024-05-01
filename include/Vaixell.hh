#ifndef VAIXELL_HH
#define VAIXELL_HH

#include "PRO2Excepcio.hh"
#include <iostream>
#include <vector>
#include <string>
#include <utility>  // Per a "pair"

class Vaixell {

private:
    pair<int,int> comprar;
    pair<int,int> vendre;
    vector<string> registre_ultimes_ciutats;

public:
    /* CONSTRUCTORS */
    Vaixell();

    /* CONSULTORS */
    void mostrarProdAComprar();
    void mostrarProdAVendre();
    void mostrarRegistreViatjes();

    /* MODIFICADORS */
    void modificarMercancia(int id_compra, int quant_compra, int id_venta, int quant_venta);
};

#endif