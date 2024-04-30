#include <exception>
#include "Ciutat.hh"

/* CONSTANTS */
const char *ER1 = "CIUTAT NO TE INVENTARI";
const char *ER2 = "CIUTAT NO TE EL PRODUCTE";

Ciutat::Ciutat() {
    id = "0";
    pes_total = 0;
    volum_total = 0;
}

bool Ciutat::teInventari() const {
    return !inventari.empty();
}

string Ciutat::consultarId() const {
    return this->id;
}

bool Ciutat::teProducte(int id) const {
    if (not teInventari()) throw PRO2Excepcio(ER1);
    return inventari.find(id)!=inventari.end();
}

int Ciutat::consultarOferta(int id) const {
    if (not teInventari()) throw PRO2Excepcio(ER1);
    auto it = inventari.find(id);
    if (it==inventari.end()) throw PRO2_EXCEPCIO(ER2);
    return it->second.first;
}

int Ciutat::consultarDemanda(int id) const {
    if (not teInventari()) throw PRO2Excepcio(ER1);
    auto it = inventari.find(id);
    if (it==inventari.end()) throw PRO2_EXCEPCIO(ER2);
    return it->second.second;
}

/**
 * \pre Ciutat té el producte. Pes/Volum són valors vàlids.
*/
void Ciutat::afegirProdAlInventari(int id, double pes, double volum) {
    int oferta = inventari[id].first;
    int demanda = inventari[id].second;
    
    inventari[id].first = oferta;
    inventari[id].second = demanda;
    this->pes_total += oferta*pes;
    this->volum_total += oferta*volum;
}

/**
 * \pre Ciutat té el producte. Pes/Volum són valors vàlids.
*/
void Ciutat::modificarProdDelInventari(int id, double pes, double volum) {
    int oferta = inventari[id].first;
    int demanda = inventari[id].second;
    auto it = inventari.find(id);
    
    if (it->second.first!=oferta) {  // No diferenciem entre cassos perquè si la diferència és negativa, al fer la suma, ja farà resta.
        int diferencia = (oferta)-(it->second.first);
        this->pes_total += diferencia*pes;
        this->volum_total += diferencia*volum;
        it->second.first = oferta;
    }
    it->second.second = demanda;
}

/**
 * \pre Ciutat té el producte. Pes/Volum són valors vàlids.
*/
void Ciutat::eliminarProdDelInventari(int id, double pes, double volum) {
    int oferta = inventari[id].first;
    
    this->pes_total -= oferta*pes;
    this->volum_total -= oferta*volum;
    inventari.erase(id);
}

// - [ ] Revisar el format de sortida 
void Ciutat::escriure() const {
    if (not teInventari()) throw PRO2Excepcio(ER1);
    for (auto it = inventari.begin(); it!=inventari.end(); it++) {
        cout << "Producte: " << it->first << " Oferta: " << it->second.first << " Demanda: " << it->second.second << endl;
    }
    cout << "Pes Total: " << pes_total << endl;
    cout << "Volum Total: " << volum_total << endl;
}