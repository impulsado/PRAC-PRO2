#ifndef VAIXELL_HH
#define VAIXELL_HH

#include "Cjt_productes.hh"
#include "Ciutat.hh"
#include <iostream>
#include <vector>
#include <string>
#include <utility>

class Vaixell {

private:
    std::pair<int,int> comprar;
    std::pair<int,int> vendre;
    std::vector<std::string> registre_ultimes_ciutats;

public:
    /* CONSTRUCTORS */
    Vaixell();

    /* MODIFICADORS */
    void modificarMercancia(int id_compra, int quant_compra, int id_venta, int quant_venta);
    int comerciar(Ciutat& city, const Cjt_productes& productes);
    void afegirCiutat(std::string id_city);
    void eliminarRegistre();

    /* CONSULTORS */
    int quantitatPerVendre();
    int quantitatPerComprar();

    /* LECTURA */
    void llegir(Cjt_productes productes);
    
    /* ESCRIPTURA */
    void escriure();
};

#endif