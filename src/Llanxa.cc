/**
 * @file Llanxa.cc
 * @brief Implementació de la classe Llanxa.
 */
#include "Llanxa.hh"
using namespace std;

/* === CONSTRUCTORS === */

Llanxa::Llanxa() {
    comprar = make_pair(0, 0);
    vendre = make_pair(0, 0);
}

Llanxa::Llanxa(Vaixell& barco) {
    comprar = barco.consultarCompra();
    vendre = barco.consultarVenda();
}

/* === MODIFICADORS === */

int Llanxa::comerciarSenseMod(const Ciutat& city) {
    // La ciutat no té inventari (Optimització)
    if (not city.teInventari()) return 0;
    
    // Total comerciat
    int quant_total = 0;

    // Comprar de la ciutat
    
    // La ciutat té el producte i el llanxa pot comprar
    if (comprar.second>0 and city.teProducte(comprar.first)) {
        // Saber quantitat disponible a la ciutat
        int dif = city.consultarDiferencia(comprar.first);

        // La ciutat té quantitat per vendre al llanxa
        if (dif>0) {
            // Determinar la maxima quantitat a comerciar
            int quant_comerciar = min(comprar.second, dif);
            // Actualitzar la nova quantitat necessària del llanxa
            comprar.second -= quant_comerciar;
            // Actualitzar la quantitat total comerciada
            quant_total += quant_comerciar;
        }
    }

    // Vendre a la ciutat
    // La ciutat necessita el producte i el llanxa pot vendre
    if (vendre.second>0 and city.teProducte(vendre.first)) {
        // Saber quantitat necessària a la ciutat
        int dif = city.consultarDiferencia(vendre.first);
        
        // La ciutat té necessitat del producte
        if (dif<0) {
            // Determinar la maxima quantitat a comerciar
            int quant_comerciar = min(vendre.second, -dif);
            // Actualitzar la nova quantitat necessària del llanxa
            vendre.second -= quant_comerciar;
            // Actualitzar la quantitat total comerciada
            quant_total += quant_comerciar;
        }
    }
    
    return quant_total;
}

/* === CONSULTORS === */

int Llanxa::quantitatPerVendre() {
    return vendre.second;
}

int Llanxa::quantitatPerComprar() {
    return comprar.second;
}