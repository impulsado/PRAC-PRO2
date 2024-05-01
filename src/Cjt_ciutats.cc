#include <exception>
#include "Cjt_ciutats.hh"

Cjt_ciutats::Cjt_ciutats() {
    cmap = map<string,Ciutat>();
}

/**
 * \pre Ciutat existeix i la ciutat per referència es vàlida
 * \post 
 */
void Cjt_ciutats::modificarCiutat(string id_city, const Ciutat& city) {
    cmap[id_city] = city;
}

void Cjt_ciutats::afegirProdACiutat(string id_city, int id_prod, int oferta, int demanda, double pes, double volum) {
    cmap[id_city].afegirProdAlInventari(id_prod,oferta,demanda,pes,volum);
}

// ?? No sé si ordre afecta en aquest cas ??
bool Cjt_ciutats::existeixCiutat(string id_city) {
    auto it = cmap.find(id_city);
    return it!=cmap.end();
}

Ciutat Cjt_ciutats::consultarCiutat(string id_city) {
    return cmap[id_city];
}