#ifndef VAIXELL_HH
#define VAIXELL_HH

#include "Cjt_productes.hh"
#include <iostream>
#include <vector>
#include <string>
#include <utility>  // Per a "pair"

class Vaixell {

private:
    std::pair<int,int> comprar;
    std::pair<int,int> vendre;
    std::vector<std::string> registre_ultimes_ciutats;

public:
    /* CONSTRUCTORS */
    Vaixell();

    /* CONSULTORS */

    /* MODIFICADORS */
    void modificarMercancia(int id_compra, int quant_compra, int id_venta, int quant_venta);
    void llegir(Cjt_productes productes);
    
    /* ESCRIPTURA */
    void escriure();
};

#endif