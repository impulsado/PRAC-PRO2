/**
 * @file Ciutat.hh
 * @brief Especificació de la classe Ciutat.
 */
#ifndef CIUTAT_HH
#define CIUTAT_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#endif

#include "Cjt_productes.hh"
using namespace std;

/** 
 * @class Ciutat
 * @brief Representa una ciutat amb un inventari de productes.
 * 
 * Un objecte de la classe Ciutat conté un identificador únic, un inventari de productes i les quantitats totals de pes i volum.
 */
class Ciutat {

private:
    string id;  ///< Identificador de la ciutat
    map<int, pair< pair<int,int> ,int>> inventari;  ///< Inventari de la ciutat.
    // first -> id producte
    // second.first.first -> oferta
    // second.first.second -> demanda
    // second.second -> necessitat
    int pes_total;  ///< Pes total de la ciutat
    int volum_total;  ///< Volum total de la ciutat

public:
    /* CONSTRUCTORS */
    /**
     * @brief Constructor per defecte de la classe Ciutat.
     * 
     * \pre Cert.
     * \post La ciutat té ID "0", i els atributs pes_total i volum_total inicialitzats a 0.
     */
    Ciutat();
    
    /**
     * @brief Constructor de la classe Ciutat amb un ID específic.
     * 
     * \pre Cert.
     * \post La ciutat té l'ID especificat. pes_total i volum_total s'inicialitzen a 0.
     */
    Ciutat(string id_city);

    /* MODIFICADORS */
    /**
     * @brief Afegeix un producte no existent a l'inventari de la ciutat.
     * 
     * \pre La ciutat no té el producte. Oferta/Demanda/Pes/Volum són vàlids.
     * \post La ciutat ara té el producte. pes_total i volum_total actualitzats.
     */
    void afegirProdAlInventari(int id_prod, int oferta, int demanda, int pes, int volum);
    
    /**
     * @brief Modifica les dades d'un producte existent a l'inventari de la ciutat.
     * 
     * \pre La ciutat té el producte. Pes i Volum són valors vàlids.
     * \post Les dades del producte són actualitzades, incloent pes_total i volum_total.
     */
    void modificarProdDelInventari(int id_prod, int oferta, int demanda, int pes, int volum);

    /**
     * @brief Modifica la quantitat d'oferta d'un producte determinat.
     * 
     * \pre La ciutat té el producte. id_prod, quantitat, pes i volum són valors vàlids.
     * \post La ciutat té la nova quantitat d'oferta d'aquell producte. S'actualitzen el pes i volum totals.
     */
    void modificarOfertaProd(int id_prod, int oferta, int pes, int volum);
    
    /**
     * @brief Elimina un producte existent de l'inventari de la ciutat.
     * 
     * \pre La ciutat té el producte. id_prod, pes i volum són valors vàlids.
     * \post La ciutat no té el producte. Dades sobre pes i volum totals actualitzades.
     */ 
    void eliminarProdDelInventari(int id_prod, int pes, int volum);

    /**
     * @brief Elimina tots els productes de l'inventari de la ciutat.
     * 
     * \pre Cert.
     * \post La ciutat no té cap producte a l'inventari. Pes i volum total es posen a 0.
     */
    void eliminarTotsProd();

    /**
     * @brief Realitza un comerç entre dues ciutats.
     * 
     * \pre Les ciutats tenen inventari. Els productes són vàlids.
     * \post Les ciutats intercanvien productes segons les seves necessitats.
     */
    void comerciar(Ciutat& other, const Cjt_productes& productes);

    /* CONSULTORS */
    /**
     * @brief Comprova si la ciutat té inventari.
     * 
     * \pre Cert.
     * \post Retorna true si hi ha almenys un producte a l'inventari, en cas contrari retorna false.
     */
    bool teInventari() const;

    /**
     * @brief Comprova si la ciutat té un producte específic.
     * 
     * \pre L'id_prod és vàlid. La ciutat pot no tenir inventari.
     * \post Retorna true si la ciutat té el producte, en cas contrari retorna false.
     */
    bool teProducte(int id_prod) const;

    /**
     * @brief Consulta l'oferta d'un producte específic.
     * 
     * \pre La ciutat té el producte.
     * \post Retorna la quantitat d'oferta del producte.
     */
    int consultarOferta(int id_prod) const;

    /**
     * @brief Consulta la demanda d'un producte específic.
     * 
     * \pre La ciutat té el producte.
     * \post Retorna la quantitat de demanda del producte.
     */
    int consultarDemanda(int id_prod) const;

    /**
     * @brief Consulta la quantitat d'excés d'un producte a la ciutat.
     * 
     * \pre La ciutat té el producte.
     * \post Retorna la quantitat d'excés del producte especificat.
     */
    int consultarDiferencia(int id_prod) const;

    /**
     * @brief Consulta el pes total de la ciutat.
     * 
     * \pre Cert.
     * \post Retorna el pes total.
     */
    int consultarPesTotal() const;

    /**
     * @brief Consulta el volum total de la ciutat.
     * 
     * \pre Cert.
     * \post Retorna el volum total.
     */
    int consultarVolumTotal() const;

    /* ESCRIPTURA */
    /**
     * @brief Mostra informació (Inventari, Pes i Volum total) de la ciutat.
     * 
     * \pre Cert.
     * \post Es mostra per terminal cada producte de l'inventari amb la seva oferta i demanda. Després es mostra el pes i volum total de la ciutat.
     */
    void escriure() const;
};

#endif