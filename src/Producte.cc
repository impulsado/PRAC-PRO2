#include "Producte.hh"
using namespace std;

/* === CONSTRUCTORS === */

/**
 * @brief Constructora Producte per defecte.
 * 
 * \pre Cert.
 * \post Producte amb id, pes i volum inicialitzats a 0.
 */
Producte::Producte() {
    id = pes = volum = 0;
}

/**
 * @brief Constructora Producte amb valors específics.
 * 
 * \pre id, pes i volum són valors vàlids.
 * \post Crea un producte amb l'id, pes i volum especificats.
 */
Producte::Producte(int id, int pes, int volum) {
    this->id = id;
    this->pes = pes;
    this->volum = volum;
}

/* === CONSULTORS === */

/**
 * @brief Consultar pes del producte.
 * 
 * \pre Cert.
 * \post Retorna el pes del producte.
 */
int Producte::consultarPes() const {
    return pes;
}

/**
 * @brief Consultar volum del producte.
 * 
 * \pre Cert.
 * \post Retorna el volum del producte.
 */
int Producte::consultarVolum() const {
    return volum;
}

/* === ESCRIPTURA === */

/**
 * @brief Escriure per consola l'id, pes i volum del producte.
 * 
 * \pre Cert.
 * \post Mostra per consola l'id, pes i volum del producte.
 */
void Producte::escriure() const {
    cout << id << ' ' << pes << ' ' << volum << endl;
}