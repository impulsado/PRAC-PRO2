/**
 * @file Producte.hh
 * @brief Especificació de la classe Producte.
 * 
 * Aquesta classe representa un producte amb un identificador únic, pes i volum.
 */
#ifndef PRODUCTE_HH
#define PRODUCTE_HH

#ifndef NO_DIAGRAM
#include <iostream>
#endif

/**
 * @class Producte
 * @brief Representa un producte amb un identificador únic, pes i volum.
 * 
 * Un objecte de la classe Producte conté un identificador únic autoincremental, un pes i un volum.
 */
class Producte {

private:
    int id;  ///< Identificador del producte
    int pes;  ///< Pes del producte
    int volum;  ///< Volum del producte

public:
    /* CONSTRUCTORS */
    /**
     * @brief Constructora Producte per defecte.
     * 
     * \pre Cert.
     * \post Producte amb id, pes i volum inicialitzats a 0.
     */
    Producte();

    /**
     * @brief Constructora Producte amb valors específics.
     * 
     * \pre id, pes i volum són valors vàlids.
     * \post Crea un producte amb l'id, pes i volum especificats.
     */
    Producte(int id, int pes, int volumen);

    /* CONSULTORS */
    /**
     * @brief Consultar pes del producte.
     * 
     * \pre Cert.
     * \post Retorna el pes del producte.
     */
    int consultarPes() const;

    /**
     * @brief Consultar volum del producte.
     * 
     * \pre Cert.
     * \post Retorna el volum del producte.
     */
    int consultarVolum() const;

    /* ESCRIPTURA */
    /**
     * @brief Escriure per consola l'id, pes i volum del producte.
     * 
     * \pre Cert.
     * \post Mostra per consola l'id, pes i volum del producte.
     */
    void escriure() const;
};

#endif