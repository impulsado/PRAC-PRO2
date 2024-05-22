#include "Viatge.hh"
using namespace std;

/* === CONSTRUCTORS === */

/**
 * @brief Constructora per defecte de la classe Viatge.
 * 
 * \pre Cert.
 * \post Viatge amb tots els paràmetres inicialitzats a valors per defecte.
 */
Viatge::Viatge() {
    quant_comerciat = 0;
    ordre = "";
    distancia = 0;
    tot_comerciat = false;
}

/* === MODIFICADORS === */

/**
 * @brief Afegir una ciutat a la ruta del viatge.
 * 
 * \pre id_city és un identificador vàlid. dir és una direcció vàlida {'d','e','r'}. conjunt és vàlid.
 * \post La ciutat s'ha afegit a la ruta i s'ha actualitzat la distància i l'ordre.
 */
void Viatge::afegirCiutat(string id_city, char dir, Cjt_ciutats& conjunt) {
    ultima_ciutat = id_city;
    ordre += dir;
    distancia++;
    snapshot = conjunt;  // ?? Això ho haig de fer personalitzat o el per defecte serveix ??
}

/**
 * @brief Actualitzar la quantitat total comerciada.
 * 
 * \pre quant és un valor vàlid.
 * \post S'ha incrementat la quantitat comerciada pel valor de quant.
 */
void Viatge::actQuant(int quant) {
    quant_comerciat += quant;
}

/**
 * @brief Indica que tot el comerç s'ha completat.
 * 
 * \pre Cert.
 * \post S'ha actualitzat el flag de tot_comerciat a true.
 */
void Viatge::actTotComerciat() {
    tot_comerciat = true;
}

/* === CONSULTORS === */

/**
 * @brief Consultar l'ordre de les ciutats visitades.
 * 
 * \pre Cert.
 * \post Retorna string amb l'ordre de les ciutats visitades.
 */
string Viatge::consultarOrdre() const {
    return ordre;
}

/**
 * @brief Consultar la quantitat total comerciada.
 * 
 * \pre Cert.
 * \post Retorna la quantitat total comerciada.
 */
int Viatge::consultarQuant() const {
    return quant_comerciat;
}

/**
 * @brief Consultar la distància total recorreguda.
 * 
 * \pre Cert.
 * \post Retorna la distància total recorreguda.
 */
int Viatge::consultarDist() const {
    return distancia;
}

/**
 * @brief Consultar l'última ciutat visitada.
 * 
 * \pre Cert.
 * \post Retorna el id de l'última ciutat visitada.
 */
string Viatge::consultarUltimaCiutat() const {
    return ultima_ciutat;
}

/**
 * @brief Consultar una còpia de l'estat del conjunt de ciutats en el moment actual.
 * 
 * \pre Cert.
 * \post Retorna una còpia del conjunt de ciutats.
 */
Cjt_ciutats Viatge::consultarSnapshot() const {
    return snapshot;
}

/**
 * @brief Comprovar si tot el comerç s'ha completat.
 * 
 * \pre Cert.
 * \post Retorna true si tot el comerç s'ha completat, en cas contrari retorna false.
 */
bool Viatge::estaTotComerciat() const {
    return tot_comerciat;
}