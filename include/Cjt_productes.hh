/**
 * @file Cjt_productes.hh
 * @brief Especificació de la classe Cjt_productes.
 * 
 * Aquesta classe representa un conjunt de productes, on cada producte és identificat per un enter.
 */
#ifndef CONJ_PROD_HH
#define CONJ_PROD_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
#endif

#include "Producte.hh"
using namespace std;

/**
 * @class Cjt_productes
 * @brief Conjunt de productes.
 * 
 * Un objecte de la classe Cjt_productes conté un conjunt de productes identificats per un enter.
 */
class Cjt_productes {

private:
    int quant_prod;  ///< Quantitat de productes
    vector<Producte> vprod;  ///< Vector de productes

public:
    /* CONSTRUCTORS */
    /**
     * @brief Constructora de Cjt_productes per defecte.
     * 
     * \pre Cert.
     * \post Conjunt de productes amb quantitat de productes igual a 0 i conjunt buit.
     */
    Cjt_productes();

    /**
     * @brief Constructora de Cjt_productes amb quantitat de productes determinada.
     * 
     * \pre mida és un valor vàlid.
     * \post Conjunt de productes amb quantitat igual a 0, però mida del vector = mida+1.
     */
    Cjt_productes(int mida);

    /* MODIFICADORS */
    /**
     * @brief Afegir nou producte al conjunt de productes.
     * 
     * \pre pes i volum són valors vàlids.
     * \post Existeix un nou producte amb id autoincrementat. quant_prod actualitzat.
     */
    void afegirProducte(int pes, int volumen);

    /**
     * @brief Modificar producte existent dintre del conjunt.
     * 
     * \pre El producte existeix. El producte per referència és vàlid.
     * \post Conjunt modificat amb el nou producte.
     */
    void modificarProducte(int id, const Producte& prod);

    /* CONSULTORS */
    /**
     * @brief Comprovar si el producte existeix.
     * 
     * \pre id_prod és qualsevol valor.
     * \post Retorna true si el id_prod està dintre dels valors vàlids (existeix), en cas contrari retorna false.
     */
    bool existeixProducte(int id) const;

    /**
     * @brief Consultar la quantitat de productes que hi ha al conjunt.
     * 
     * \pre Cert.
     * \post Retorna la quantitat de productes.
     */
    int consultarQuantitatProd() const;

    /**
     * @brief Retornar el producte especificat.
     * 
     * \pre El producte existeix.
     * \post Retorna una còpia del producte.
     */
    Producte consultarProducte(int id) const;

    /* ESCRIPTURA */
    /**
     * @brief Escriure producte.
     * 
     * \pre El producte existeix.
     * \post S'ha escrit el producte.
     */
    void escriureProd(int id) const;

    /* LECTURA */
    /**
     * @brief Llegir conjunt de productes.
     * 
     * \pre quant_prod és un valor vàlid.
     * \post El conjunt de productes és modificat amb els nous productes.
     */
    void llegir(int quant_prod);
};

#endif