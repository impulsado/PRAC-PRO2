#include "Cjt_productes.hh"
using namespace std;

/* === CONSTRUCTORS === */

/**
 * @brief Constructora de Cjt_productes per defecte.
 * 
 * \pre Cert.
 * \post Conjunt de productes amb quantitat de productes igual a 0 i conjunt buit.
 */
Cjt_productes::Cjt_productes() {
    quant_prod = 0;
    vprod = vector<Producte>();
}

/**
 * @brief Constructora de Cjt_productes amb quantitat de productes determinada.
 * 
 * \pre mida és un valor vàlid.
 * \post Conjunt de productes amb quantitat igual a 0, però mida del vector = mida+1.
 */
Cjt_productes::Cjt_productes(int mida) {
    quant_prod = 0;
    vprod = vector<Producte>(mida+1);
}

/* === MODIFICADORS === */

/**
 * @brief Afegir nou producte al conjunt de productes.
 * 
 * \pre pes i volum són valors vàlids.
 * \post Existeix un nou producte amb id autoincrementat. quant_prod actualitzat.
 */
void Cjt_productes::afegirProducte(int pes, int volum) {
    quant_prod++;
    int id = quant_prod;
    Producte temp(id, pes, volum);
    vprod.push_back(temp);
}

/**
 * @brief Modificar producte existent dintre del conjunt.
 * 
 * \pre El producte existeix. El producte per referència és vàlid.
 * \post Conjunt modificat amb el nou producte.
 */
void Cjt_productes::modificarProducte(int id_prod, const Producte& prod) {
    vprod[id_prod-1] = prod;
}

/* === CONSULTORS === */

/**
 * @brief Comprovar si el producte existeix.
 * 
 * \pre id_prod és qualsevol valor.
 * \post Retorna true si el id_prod està dintre dels valors vàlids (existeix), en cas contrari retorna false.
 */
bool Cjt_productes::existeixProducte(int id_prod) const {
    if (id_prod<=0 or id_prod>quant_prod) return false;
    return true;
}

/**
 * @brief Consultar la quantitat de productes que hi ha al conjunt.
 * 
 * \pre Cert.
 * \post Retorna la quantitat de productes.
 */
int Cjt_productes::consultarQuantitatProd() const {
    return quant_prod;
}

/**
 * @brief Retornar el producte especificat.
 * 
 * \pre El producte existeix.
 * \post Retorna una còpia del producte.
 */
Producte Cjt_productes::consultarProducte(int id_prod) const {
    return vprod[id_prod-1];
}