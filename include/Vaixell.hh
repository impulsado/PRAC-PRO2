/**
 * @file Vaixell.hh
 * @brief Especificació de la classe Vaixell.
 * 
 * Aquesta classe representa un vaixell amb una determinada quantitat de productes per comprar i vendre. 
 * També conté un registre de les últimes ciutats visitades a cada viatge realitzat.
 */
#ifndef VAIXELL_HH
#define VAIXELL_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#endif

#include "Cjt_productes.hh"
#include "Ciutat.hh"
using namespace std;

/**
 * @class Vaixell
 * @brief Representa un vaixell amb una determinada quantitat de productes per comprar i vendre.
 * 
 * Un objecte de la classe Vaixell conté una parella de productes per comprar i vendre, així com un registre de les últimes ciutats visitades.
 */
class Vaixell {

private:
    pair<int,int> comprar;  ///< Producte a comprar
    pair<int,int> vendre;  ///< Producte a vendre
    vector<string> registre_ultimes_ciutats;  ///< Registre de les últimes ciutats visitades

public:
    /* CONSTRUCTORS */
    /**
     * @brief Constructora per defecte de la classe Vaixell.
     * 
     * \pre Cert.
     * \post Vaixell amb tots els paràmetres inicialitzats a 0 o buits.
     */
    Vaixell();

    /* MODIFICADORS */
    /**
     * @brief Actualitzar informació sobre quin producte vendrà i comprarà el vaixell.
     * 
     * \pre id_compra i id_venta existeixen. quant_compra i quant_venta són valors vàlids.
     * \post El vaixell té les dades sobre el producte a comprar i vendre actualitzades.
     */
    void modificarMercancia(int id_compra, int quant_compra, int id_venta, int quant_venta);

    /**
     * @brief Realitza l'operació de comerç amb una ciutat.
     * 
     * @details Aquesta funció pot modificar la ciutat si es desitja. Això és per optimitzar el càlcul de la millor ruta.
     * 
     * \pre La ciutat té un inventari vàlid. Els productes existeixen en el conjunt de productes.
     * \post Actualitza el vaixell i la ciutat segons l'operació de comerç. Retorna la quantitat total comerciada.
     */
    int comerciar(Ciutat& city, const Cjt_productes& productes, bool modificar_ciutat);

    /**
     * @brief Afegir una ciutat al registre de les últimes ciutats visitades.
     * 
     * \pre id_city és vàlid.
     * \post El registre de les últimes ciutats conté id_city.
     */
    void afegirCiutat(std::string id_city);

    /**
     * @brief Eliminar totes les ciutats del registre.
     * 
     * \pre Cert.
     * \post El vaixell no conté cap registre de les últimes ciutats visitades.
     */
    void eliminarRegistre();

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

    /* LECTURA */
    /**
     * @brief Llegir els valors necessaris del vaixell des de l'entrada estàndard.
     * 
     * \pre Cert.
     * \post El vaixell té com atributs les dades llegides.
     */
    void llegir(Cjt_productes productes);
    
    /* ESCRIPTURA */
    /**
     * @brief Mostra tota la informació del vaixell.
     * 
     * \pre Cert.
     * \post Mostra per consola el producte a comprar i vendre, juntament amb les respectives quantitats, i les últimes ciutats visitades.
     */
    void escriure();
};

#endif