#include <exception>
#include "Cjt_productes.hh"

/* CONSTANTS */
const char *ER1 = "ID NO VALID";
const char *ER2 = "PES NO VALID";
const char *ER3 = "VOLUM NO VALID";

Cjt_productes::Cjt_productes() {
    quant_prod = 0;
    vprod = vector<Producte>();
}

Cjt_productes::Cjt_productes(int mida) {
    quant_prod = mida;
    vprod = vector<Producte>(mida+1);
}

void Cjt_productes::afegirProducte(double pes, double volum) {
    if (pes<=0) throw PRO2Excepcio(ER2);
    if (volum<=0) throw PRO2Excepcio(ER3);
    int id = quant_prod+1;
    Producte temp(id,pes,volum);
    vprod.push_back(temp);
    quant_prod++;
}

void Cjt_productes::modificarProducte(int id, const Producte& prod) {
    if (id<=0 or id>quant_prod) throw PRO2Excepcio(ER1);
    vprod[id] = prod;
}

bool Cjt_productes::existeixProducte(int id) const {
    if (id<=0 or id>quant_prod) return false;
    return true;
}

int Cjt_productes::consultarQuantitatProd() const {
    return this->quant_prod;
}

Producte Cjt_productes::consultarProducte(int id) const {
    if (id<=0 or id>quant_prod) throw PRO2Excepcio(ER1);
    return vprod[id];
}