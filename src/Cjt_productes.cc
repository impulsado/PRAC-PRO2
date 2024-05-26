/**
 * @file Cjt_productes.cc
 * @brief Implementació de la classe Cjt_productes
 */
#include "Cjt_productes.hh"
using namespace std;

/* === CONSTRUCTORS === */

Cjt_productes::Cjt_productes() {
    quant_prod = 0;
    vprod = vector<pair<int,int>>();
}

/* === MODIFICADORS === */

void Cjt_productes::afegirProducte(int pes, int volum) {
    quant_prod++;
    vprod.push_back(make_pair(pes,volum));
}

void Cjt_productes::modificarProducte(int id_prod, int pes, int volum) {
    vprod[id_prod-1] = make_pair(pes,volum);
}

/* === CONSULTORS === */

bool Cjt_productes::existeixProducte(int id_prod) const {
    return id_prod>0 and id_prod<=quant_prod;
}

int Cjt_productes::consultarQuantitatProd() const {
    return quant_prod;
}

pair<int,int> Cjt_productes::consultarProducte(int id_prod) const {
    return vprod[id_prod-1];
}

/* === ESCRIPTURA === */

void Cjt_productes::escriureProd(int id) const {
    cout << id << ' ' << vprod[id-1].first << ' ' << vprod[id-1].second << endl;
}

/* === LECTURA === */

void Cjt_productes::llegir(int quant_prod) {
    for (int i = 0; i < quant_prod; i++) {
        int pes, volum;
        cin >> pes >> volum;
        afegirProducte(pes, volum);
    }
}