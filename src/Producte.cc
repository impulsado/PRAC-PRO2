#include <exception>
#include "Producte.hh"

/* CONSTANTS */
const char *ER1 = "ID NO VALID";
const char *ER2 = "PES NO VALID";
const char *ER3 = "VOLUM NO VALID";

Producte::Producte() {
    id = 0;
}

Producte::Producte(int id, double pes, double volum) {
    if (id<=0) throw PRO2Excepcio(ER1);
    if (pes<=0) throw PRO2Excepcio(ER2);
    if (volum<=0) throw PRO2Excepcio(ER3);
    this->id = id;
    this->pes = pes;
    this->volum = volum;
}

int Producte::consultarId() const {
    return this->id;
}

double Producte::consultarPes() const {
    return this->pes;
}

double Producte::consultarVolum() const {
    return this->volum;
}

// ?? Revisar Format ?? 
void Producte::escriure() const {
    cout << this->pes << ' ' << this->volum << endl;
}