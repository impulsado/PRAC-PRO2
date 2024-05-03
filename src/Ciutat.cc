#include <exception>
#include "Ciutat.hh"
using namespace std;

/* CONSTANTS */
const char *ER1 = "Error: Ciutat no té inventari";
const char *ER2 = "Error: Ciutat no té producte";

Ciutat::Ciutat() {
    id = "0";
    pes_total = 0;
    volum_total = 0;
}

bool Ciutat::teInventari() const {
    return !inventari.empty();
}

string Ciutat::consultarId() const {
    return id;
}

bool Ciutat::teProducte(int id) const {
    if (not teInventari()) throw PRO2Excepcio(ER1);
    return inventari.find(id)!=inventari.end();
}

int Ciutat::consultarOferta(int id) const {
    if (not teInventari()) throw PRO2Excepcio(ER1);
    auto it = inventari.find(id);
    if (it==inventari.end()) throw PRO2Excepcio(ER2);
    return it->second.first.first;
}

int Ciutat::consultarDemanda(int id) const {
    if (not teInventari()) throw PRO2Excepcio(ER1);
    auto it = inventari.find(id);
    if (it==inventari.end()) throw PRO2Excepcio(ER2);
    return it->second.first.second;
}

double Ciutat::consultarPesTotal() const {
    return pes_total;
}

double Ciutat::consultarVolumTotal() const {
    return volum_total;
}

int Ciutat::consultarDiferencia(int id_prod) const { 
    if (not teInventari()) throw PRO2Excepcio(ER1);
    // Faig servir un iterador perque inventari[] modifica el inventari i la funció és 'const'
    auto it = inventari.find(id_prod);
    if (it==inventari.end()) throw PRO2Excepcio(ER2);
    return it->second.second;
}

vector<int> Ciutat::consultarProductes() const {
    if (not teInventari()) throw PRO2Excepcio(ER1);
    vector<int> ids;
    auto it = inventari.begin();
    while (it!=inventari.end()) ids.push_back(it->first);
    return ids;
}

/**
 * \pre Ciutat no té el producte. Oferta/Demanda/Pes/Volum són valors vàlids.
*/
void Ciutat::afegirProdAlInventari(int id_prod, int oferta, int demanda, double pes, double volum) {
    inventari[id_prod].first.first = oferta;
    inventari[id_prod].first.second = demanda;
    inventari[id_prod].second = oferta-demanda;
    pes_total += oferta*pes;
    volum_total += oferta*volum;
}

/**
 * \pre Ciutat té el producte. Pes/Volum són valors vàlids.
*/
void Ciutat::modificarProdDelInventari(int id, int oferta, int demanda, double pes, double volum) {
    auto it = inventari.find(id);
    
    if (it->second.first.first!=oferta) {  // No diferenciem entre cassos perquè si la diferència és negativa, al fer la suma, ja farà resta.
        int diferencia = (oferta)-(it->second.first.first);
        pes_total += diferencia*pes;
        volum_total += diferencia*volum;
        it->second.first.first = oferta;
    }
    it->second.first.second = demanda;

    it->second.second = oferta-demanda;  // Actualitzar la necessitat del producte
}

void Ciutat::modificarOfertaProd(int id, int quantitat, double pes, double volum) {
    auto it = inventari.find(id);
    
    pes_total += quantitat*pes;
    volum_total += quantitat*volum;
    it->second.first.first += quantitat;  // Afegir la nova quanitat d'oferta
    it->second.second += quantitat;  // Actualitzar la necessitat del producte
}

/**
 * \pre Ciutat té el producte. Pes/Volum són valors vàlids.
*/
void Ciutat::eliminarProdDelInventari(int id, double pes, double volum) {
    int oferta = inventari[id].first.first;
    
    this->pes_total -= oferta*pes;
    this->volum_total -= oferta*volum;
    inventari.erase(id);
}

// ?? Revisar format ??
void Ciutat::escriure() const {
    if (not teInventari()) {cout << "Error: Ciutat no te inventari" << endl; return;}
    for (auto it = inventari.begin(); it!=inventari.end(); it++) {
        cout << "Producte: " << it->first << " Oferta: " << it->second.first.first << " Demanda: " << it->second.first.second << endl;
    }
    cout << "Pes Total: " << pes_total << endl;
    cout << "Volum Total: " << volum_total << endl;
}