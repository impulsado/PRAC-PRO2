#include "Producte.hh"
using namespace std;

/**
 * @brief Constructora Producte per defecte.
 * 
 * \pre Cert.
 * \post Producte amb id,pes i volum 0.
 */
Producte::Producte() {
    id = pes = volum = 0;
}

/**
 * @brief Constructura Producte amb valors específics.
 * 
 * \pre id,pes,volum son valors vàlids.
 * \post Retorna producte amb id,pes i volum.
 */
Producte::Producte(int id, int pes, int volum) {
    this->id = id;
    this->pes = pes;
    this->volum = volum;
}

/**
 * @brief Consultar pes del producte.
 * 
 * \pre Cert.
 * \post Retornar pes del producte.
 */
int Producte::consultarPes() const {
    return pes;
}

/**
 * @brief Consultar volum del producte.
 * 
 * \pre Cert.
 * \post Retornar volum del producte.
 */
int Producte::consultarVolum() const {
    return volum;
}

/**
 * @brief Escriure per consola el pes i volum del producte.
 * 
 * \pre Cert.
 * \post Mostrar dades del producte.
 */
void Producte::escriure() const {
    cout << id << ' ' << pes << ' ' << volum << endl;
}