#include <exception>
#include "Cjt_ciutats.hh"

/* CONSTANTS */
const char *ER1 = "CIUTAT NO VALIDA";

Cjt_ciutats::Cjt_ciutats() {
    this->cmap = map<string,Ciutat>();
}

void Cjt_ciutats::modificarCiutat(string id, const Ciutat& city) {
    if (not existeixCiutat(id)) throw PRO2Excepcio(ER1);
    cmap[id] = city;
}

// ?? No sé si ordre afecta en aquest cas ??
bool Cjt_ciutats::existeixCiutat(string id) {
    auto it = cmap.find(id);
    return it!=cmap.end();
}