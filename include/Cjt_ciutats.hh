/**
 * @file Cjt_ciutats.hh
 * @brief Especificació de la classe Cjt_ciutats.
 * 
 * Aquesta classe representa un conjunt de ciutats, on cada ciutat és identificada per un string.
 */
#ifndef CONJ_CITY_HH
#define CONJ_CITY_HH

#ifndef NO_DIAGRAM
#include <map>
#include <list>
#include <string>
#endif

#include "Llanxa.hh"
#include "Viatge.hh"
#include "Ciutat.hh"
#include "Vaixell.hh"
#include "BinTree.hh"
#include "Cjt_productes.hh"
using namespace std;

/**
 * @class Cjt_ciutats
 * @brief Conjunt de ciutats.
 * 
 * Un objecte de la classe Cjt_ciutats conté un conjunt de ciutats identificades per un string.
 */
class Cjt_ciutats {

private:
    map<string, Ciutat> cmap;  ///< Conjunt de ciutats.

    /**
     * @brief Llegir conjunt de ciutats i retornar l'arbre binari.
     * 
     * \pre Cert.
     * \post El conjunt de ciutats és modificat amb les noves ciutats.
     * @return BinTree<std::string> 
     */
    BinTree<string> leer_rio_aux();

public:
    /* CONSTRUCTORS */
    /**
     * @brief Constructor per defecte de la classe Cjt_ciutats.
     * 
     * \pre Cert.
     * \post Conjunt de ciutats buit.
     */
    Cjt_ciutats();

    /* MODIFICADORS */
    /**
     * @brief Afegir nova ciutat al conjunt.
     * 
     * \pre id_city i la ciutat són vàlids.
     * \post El conjunt conté la nova ciutat.
     */
    void afegirCiutat(const string& id_city, const Ciutat& city);

    /** 
     * @brief Modificar ciutat existent dintre del conjunt.
     * 
     * \pre La ciutat existeix. La ciutat per referència és vàlida.
     * \post Conjunt modificat amb la nova ciutat.
     */
    void modificarCiutat(const string& id_city, const Ciutat& city);

    /**
     * @brief Afegir un nou producte a la ciutat.
     * 
     * \pre La ciutat existeix. El producte existeix. Oferta/Demanda/Pes/Volum són vàlids.
     * \post La ciutat té el producte al seu inventari i pes_total/volum_total actualitzats.
     */
    void afegirProdACiutat(const string& id_city, int id_prod, int oferta, int demanda, int pes, int volum);

    /**
     * @brief Comerciar entre dues ciutats.
     * 
     * \pre Les dues ciutats existeixen. El conjunt de productes és vàlid.
     * \post Les ciutats han intercanviat productes.
     */
    void comerciar(string& id_city1, string& id_city2, const Cjt_productes& productes);

    /**
     * @brief Comerciar entre ciutats.
     * 
     * \pre Les dues ciutats existeixen.
     * \post Cada ciutat ha donat el seu excés a l'altra ciutat.
     */
    void redistribuir(const BinTree<string>& Cuenca, const Cjt_productes& productes);

    /**
     * @brief Realitzar un viatge entre ciutats.
     * 
     * \pre El viatge és vàlid.
     * \post Les ciutats han intercanviat productes amb el vaixell.
     */
    void realitzar_viatge(const Cjt_productes& productes, const Viatge& viatge_top, Vaixell barco);

    /**
     * @brief Determinar el viatge a realitzar.
     * 
     * \pre El conjunt de ciutats és vàlid. El conjunt de productes és vàlid. El vaixell és vàlid.
     * \post Retorna el viatge a realitzar.
     */
    Viatge determinar_viatge(const BinTree<string>& cuenca, const Cjt_productes& productes, Llanxa lancha);

    /**
     * @brief Eliminar tots els productes d'una ciutat.
     * 
     * \pre Cert.
     * \post La ciutat no té cap producte al seu inventari. Pes i volum total a 0.
     */
    void eliminarTotsProdDeCiutat(string id_city);

    /* CONSULTORS */

    /**
     * @brief Comprovar si la ciutat amb l'ID especificada existeix.
     * 
     * \pre id_city és un valor qualsevol.
     * \post Retorna true si la ciutat existeix, en cas contrari retorna false.
     */
    bool existeixCiutat(string id_city) const;

    /**
     * @brief Retorna la ciutat especificada.
     * 
     * \pre La ciutat existeix.
     * \post Retorna una còpia de la ciutat.
     */
    Ciutat consultarCiutat(string id_city) const;

    /* ESCRIPTURA */
    /**
     * @brief Escriure la ciutat especificada.
     * 
     * \pre La ciutat existeix.
     * \post La ciutat és escrita per pantalla.
     */
    void escriureCiutat(string id_city) const;
    
    /* LECTURA */
    
    /**
     * @brief Eliminar les ciutats actuals i llegir un nou conjunt de ciutats.
     * 
     * \pre Cert.
     * \post El conjunt de ciutats és modificat amb les noves ciutats.
     */
    BinTree<string> leer_rio();
};

#endif