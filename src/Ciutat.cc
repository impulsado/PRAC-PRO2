#include <exception>
#include "Ciutat.hh"
using namespace std;

/**
 * @brief Constructura per defecte classe Ciutat.
 * 
 * \pre Cert.
 * \post Ciutat té ID "0". pes_total i volum_total a 0.
 */
Ciutat::Ciutat() {
    id = "0";
    pes_total = 0;
    volum_total = 0;
}

/**
 * @brief Comprova si la ciutat té inventari.
 * 
 * \pre Cert.
 * \post Retorna "true" si hi ha almenys un producte a l'inventari. Altrament "false".
 */
bool Ciutat::teInventari() const {
    return !inventari.empty();
}

/**
 * @brief Comprova si la ciutat té el producte
 * 
 * \pre id és vàlid. La ciutat pot no tindre inventari.
 * \post Retorna "true" si al ciutat té el producte. Altrament retorna "false".
 */
bool Ciutat::teProducte(int id_prod) const {
    return inventari.find(id_prod)!=inventari.end();
}

/**
 * @brief Consultar oferta d'un producte específic.
 * 
 * \pre La ciutat té el producte.
 * \post Retornar quantitat de oferta del producte.
 */
int Ciutat::consultarOferta(int id_prod) const {
    auto it = inventari.find(id_prod);
    return it->second.first.first;
}

/**
 * @brief Consultar demanda d'un producte específic.
 * 
 * \pre La ciutat té el producte.
 * \post Retornar quantitat de demanda del producte.
 */
int Ciutat::consultarDemanda(int id_prod) const {
    auto it = inventari.find(id_prod);
    return it->second.first.second;
}

/**
 * @brief Consultar pes total de la ciutat.
 * 
 * \pre Cert.
 * \post Pes total.
 */
double Ciutat::consultarPesTotal() const {
    return pes_total;
}

/**
 * @brief Consultar volum total de la ciutat.
 * 
 * \pre Cert.
 * \post Volum total.
 */
double Ciutat::consultarVolumTotal() const {
    return volum_total;
}

/**
 * @brief Consultar la quantitat d'excendent que la ciutat.
 * 
 * \pre La ciutat té el producte.
 * \post Retorna la quantitat d'excendent del producte especificat.
 */
int Ciutat::consultarDiferencia(int id_prod) const { 
    // NOTA: Faig servir un iterador perque inventari[] modifica el inventari i la funció és 'const'
    auto it = inventari.find(id_prod);
    return it->second.second;
}

/**
 * @brief Retornar vectors amb tots els id's dels productes de la ciutat.
 * 
 * \pre La ciutat té inventari.
 * \post Vector amb les id's dels productes existents en la ciutat.
 */
vector<int> Ciutat::consultarProductes() const {
    vector<int> ids;
    auto it = inventari.begin();
    while (it!=inventari.end()) {
        ids.push_back(it->first);
        it++;
    }
    return ids;
}

/**
 * @brief Afegir producte no existent a l'inventari de la ciutat.
 * 
 * \pre Ciutat no té el producte. Oferta/Demanda/Pes/Volum son vàlids.
 * \post Ciutat si té el producte. pes_total/volum_total actualitzats.
 */
void Ciutat::afegirProdAlInventari(int id_prod, int oferta, int demanda, double pes, double volum) {
    inventari[id_prod].first.first = oferta;
    inventari[id_prod].first.second = demanda;
    inventari[id_prod].second = oferta-demanda;  // Necessitat del producte
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

/**
 * @brief Modificar la quantitat d'oferta respecte un producte determinat
 * 
 * \pre La ciutat té el producte. id_prod, quantiat, pes i volum son valors valids.
 * \post La ciutat té la nova quanitat d'oferta d'aquell producte. S'actualitza el pes i volum totals.
 */
void Ciutat::modificarOfertaProd(int id_prod, int quantitat, double pes, double volum) {
    auto it = inventari.find(id_prod);
    
    pes_total += quantitat*pes;
    volum_total += quantitat*volum;
    it->second.first.first += quantitat;  // Afegir la nova quanitat d'oferta
    it->second.second += quantitat;  // Actualitzar la necessitat del producte
}

/**
 * @brief Eliminar un producte existent en l'inventari de la ciutat.
 * 
 * \pre Ciutat si té el producte. id_prod/pes/volum són valors vàlids.
 * \post La ciutat no té el producte. Dades sobre pes i volum totals actualitzades.
 */
void Ciutat::eliminarProdDelInventari(int id_prod, double pes, double volum) {
    int oferta = inventari[id_prod].first.first;
    
    pes_total -= oferta*pes;
    volum_total -= oferta*volum;
    inventari.erase(id_prod);
}

/**
 * @brief Mostrar informació (Inventari, Pes i Volum total) de la ciutat.
 * 
 * \pre Cert.
 * \post Mostra per terminal per cada producte en l'inventari l'oferta i la demanda. Després mostra el pes i volum total de la ciutat.
 */
void Ciutat::escriure() const {
    // ?? Revisar format ??
    if (not teInventari()) {cout << "Error: Ciutat no té inventari" << endl; return;}
    for (auto it = inventari.begin(); it!=inventari.end(); it++) {
        cout << "Producte: " << it->first << " Oferta: " << it->second.first.first << " Demanda: " << it->second.first.second << endl;
    }
    cout << "Pes Total: " << pes_total << endl;
    cout << "Volum Total: " << volum_total << endl;
}