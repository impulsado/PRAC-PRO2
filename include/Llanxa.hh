/**
 * @file Llanxa.hh
 * @brief Especificació de la classe Llanxa.
 * 
 * Aquesta classe representa un vaixell però que només conté la informació necessària per calcular el millor viatge.
 */
#ifndef LLANXA_HH
#define LLANXA_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <utility>
#endif

#include "Ciutat.hh"
#include "Vaixell.hh"
using namespace std;

/**
 * @class Llanxa
 * @brief Representa un vaixell però que només conté els mètodes i atributs necessaris per calcular el millor viatge.
 * 
 * Un objecte de la classe llanxa conté una parella de productes per comprar i vendre.
 */
class Llanxa {

private:
    pair<int,int> comprar;  ///< Producte a comprar
    pair<int,int> vendre;  ///< Producte a vendre

public:
    /* CONSTRUCTORS */
    /**
     * @brief Constructora per defecte de la classe Vaixell.
     * 
     * \pre Cert.
     * \post Vaixell amb tots els paràmetres inicialitzats a 0 o buits.
     */
    Llanxa();
    
    /**
     * @brief Constructora amb paràmetres de la classe Vaixell.
     * 
     * \pre El vaixell és vàlid.
     * \post Crea una llanxa amb la informació de compra i venta del vaixell.
     */
    Llanxa(Vaixell& barco);

    /**
     * @brief Realitza l'operació de comerç amb una ciutat sense modificar-la.
     * 
     * @details Aquesta funció no modifica la ciutat, és útil per determinar la millor ruta sense modificar les ciutats.
     * 
     * \pre La ciutat és vàlida.
     * \post Retorna la quantitat total comerciada sense modificar la ciutat.
     */
    int comerciarSenseMod(const Ciutat& city);

    /* CONSULTORS */
    /**
     * @brief Quantitat d'unitats restants per vendre.
     * 
     * \pre Cert.
     * \post Retorna la quantitat d'unitats restants per vendre.
     */
    int quantitatPerVendre();

    /**
     * @brief Quantitat d'unitats restants per comprar.
     * 
     * \pre Cert.
     * \post Retorna la quantitat d'unitats restants per comprar.
     */
    int quantitatPerComprar();
};

#endif