#include "Cjt_productes.hh"
using namespace std;

/* === CONSTRUCTORS === */

Cjt_productes::Cjt_productes() {
    quant_prod = 0;
    vprod = vector<Producte>();
}

Cjt_productes::Cjt_productes(int mida) {
    quant_prod = 0;
    vprod = vector<Producte>(mida+1);
}

/* === MODIFICADORS === */

void Cjt_productes::afegirProducte(int pes, int volum) {
    quant_prod++;
    int id = quant_prod;
    Producte temp(id, pes, volum);
    vprod.push_back(temp);
}

void Cjt_productes::modificarProducte(int id_prod, const Producte& prod) {
    vprod[id_prod-1] = prod;
}

/* === CONSULTORS === */

bool Cjt_productes::existeixProducte(int id_prod) const {
    if (id_prod<=0 or id_prod>quant_prod) return false;
    return true;
}

int Cjt_productes::consultarQuantitatProd() const {
    return quant_prod;
}

Producte Cjt_productes::consultarProducte(int id_prod) const {
    return vprod[id_prod-1];
}

/* === ESCRIPTURA === */
void Cjt_productes::escriureProd(int id) const {
    vprod[id-1].escriure();
}


/* === LECTURA === */

void Cjt_productes::llegir(int quant_prod) {
    for (int i = 0; i < quant_prod; i++) {
        int pes, volum;
        cin >> pes >> volum;
        afegirProducte(pes,volum);
    }
}