#include "Ciutat.hh"
using namespace std;

/* === CONSTRUCTORS === */

/**
 * @brief Constructor per defecte de la classe Ciutat.
 * 
 * \pre Cert.
 * \post La ciutat té ID "0", i els atributs pes_total i volum_total inicialitzats a 0.
 */
Ciutat::Ciutat() {
    id = "0";
    pes_total = 0;
    volum_total = 0;
}

/**
 * @brief Constructor de la classe Ciutat amb un ID específic.
 * 
 * \pre Cert.
 * \post La ciutat té l'ID especificat. pes_total i volum_total s'inicialitzen a 0.
 */
Ciutat::Ciutat(string id_city) {
    id = id_city;
    pes_total = 0;
    volum_total = 0;
}

/* === MODIFICADORS === */

/**
 * @brief Afegeix un producte no existent a l'inventari de la ciutat.
 * 
 * \pre La ciutat no té el producte. Oferta/Demanda/Pes/Volum són vàlids.
 * \post La ciutat ara té el producte. pes_total i volum_total actualitzats.
 */
void Ciutat::afegirProdAlInventari(int id_prod, int oferta, int demanda, int pes, int volum) {
    inventari[id_prod].first.first = oferta;
    inventari[id_prod].first.second = demanda;
    inventari[id_prod].second = oferta-demanda;  // Necessitat del producte
    pes_total += oferta*pes;
    volum_total += oferta*volum;
}

/**
 * @brief Modifica les dades d'un producte existent a l'inventari de la ciutat.
 * 
 * \pre La ciutat té el producte. Pes i Volum són valors vàlids.
 * \post Les dades del producte són actualitzades, incloent pes_total i volum_total.
 */
void Ciutat::modificarProdDelInventari(int id, int oferta, int demanda, int pes, int volum) {
    auto it = inventari.find(id);
    
    if (it->second.first.first!=oferta) {  // No diferenciem entre casos perquè si la diferència és negativa, al fer la suma, ja farà resta.
        int diferencia = oferta-(it->second.first.first);
        pes_total += diferencia*pes;
        volum_total += diferencia*volum;
        it->second.first.first = oferta;
    }
    it->second.first.second = demanda;

    it->second.second = oferta-demanda;  // Actualitzar la necessitat del producte
}

/**
 * @brief Modifica la quantitat d'oferta d'un producte determinat.
 * 
 * \pre La ciutat té el producte. id_prod, quantitat, pes i volum són valors vàlids.
 * \post La ciutat té la nova quantitat d'oferta d'aquell producte. S'actualitzen el pes i volum totals.
 */
void Ciutat::modificarOfertaProd(int id_prod, int quantitat, int pes, int volum) {
    auto it = inventari.find(id_prod);
    
    pes_total += quantitat*pes;
    volum_total += quantitat*volum;
    
    it->second.first.first += quantitat;  // Afegir la nova quantitat d'oferta
    it->second.second += quantitat;  // Actualitzar la necessitat del producte
}

/**
 * @brief Elimina un producte existent de l'inventari de la ciutat.
 * 
 * \pre La ciutat té el producte. id_prod, pes i volum són valors vàlids.
 * \post La ciutat no té el producte. Dades sobre pes i volum totals actualitzades.
 */
void Ciutat::eliminarProdDelInventari(int id_prod, int pes, int volum) {
    int oferta = inventari[id_prod].first.first;
    
    pes_total -= oferta * pes;
    volum_total -= oferta * volum;
    inventari.erase(id_prod);
}

/**
 * @brief Elimina tots els productes de l'inventari de la ciutat.
 * 
 * \pre Cert.
 * \post La ciutat no té cap producte a l'inventari. Pes i volum total es posen a 0.
 */
void Ciutat::eliminarTotsProd() {
    inventari.clear();
    pes_total = 0;
    volum_total = 0;
}

/**
 * @brief Comprova si la ciutat té inventari.
 * 
 * \pre Cert.
 * \post Retorna true si hi ha almenys un producte a l'inventari, en cas contrari retorna false.
 */
bool Ciutat::teInventari() const {
    return !inventari.empty();
}

/**
 * @brief Comprova si la ciutat té un producte específic.
 * 
 * \pre L'id_prod és vàlid. La ciutat pot no tenir inventari.
 * \post Retorna true si la ciutat té el producte, en cas contrari retorna false.
 */
bool Ciutat::teProducte(int id_prod) const {
    return inventari.find(id_prod)!=inventari.end();
}

/**
 * @brief Consulta l'oferta d'un producte específic.
 * 
 * \pre La ciutat té el producte.
 * \post Retorna la quantitat d'oferta del producte.
 */
int Ciutat::consultarOferta(int id_prod) const {
    auto it = inventari.find(id_prod);
    return it->second.first.first;
}

/**
 * @brief Consulta la demanda d'un producte específic.
 * 
 * \pre La ciutat té el producte.
 * \post Retorna la quantitat de demanda del producte.
 */
int Ciutat::consultarDemanda(int id_prod) const {
    auto it = inventari.find(id_prod);
    return it->second.first.second;
}

/**
 * @brief Consulta la quantitat d'excés d'un producte a la ciutat.
 * 
 * \pre La ciutat té el producte.
 * \post Retorna la quantitat d'excés del producte especificat.
 */
int Ciutat::consultarDiferencia(int id_prod) const { 
    // NOTA: Faig servir un iterador perquè inventari[] modifica l'inventari i la funció és 'const'
    auto it = inventari.find(id_prod);
    return it->second.second;
}

/**
 * @brief Consulta el pes total de la ciutat.
 * 
 * \pre Cert.
 * \post Retorna el pes total.
 */
int Ciutat::consultarPesTotal() const {
    return pes_total;
}

/**
 * @brief Consulta el volum total de la ciutat.
 * 
 * \pre Cert.
 * \post Retorna el volum total.
 */
int Ciutat::consultarVolumTotal() const {
    return volum_total;
}

/**
 * @brief Retorna un vector amb tots els ID's dels productes de la ciutat.
 * 
 * \pre La ciutat té inventari.
 * \post Vector amb els ID's dels productes existents a la ciutat.
 */
vector<int> Ciutat::consultarProductes() const {
    vector<int> ids;
    auto it = inventari.begin();
    while (it != inventari.end()) {
        ids.push_back(it->first);
        it++;
    }
    return ids;
}

/* === ESCRIPTURA === */

/**
 * @brief Mostra informació (Inventari, Pes i Volum total) de la ciutat.
 * 
 * \pre Cert.
 * \post Es mostra per terminal cada producte de l'inventari amb la seva oferta i demanda. Després es mostra el pes i volum total de la ciutat.
 */
void Ciutat::escriure() const {
    if (not teInventari()) {
        cout << "0 0" << endl;
        return;
    }
    
    for (auto it = inventari.begin(); it != inventari.end(); it++) {
        cout << it->first << ' ' << it->second.first.first << ' ' << it->second.first.second << endl;
    }
    cout << pes_total << ' ' << volum_total << endl;
}