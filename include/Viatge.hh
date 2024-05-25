/**
 * @file Viatge.hh
 * @brief Especificació de la classe Viatge.
 * 
 * Aquesta classe representa un viatge amb una ruta, una quantitat de productes comerciats i una distància recorreguda.
 * La distancia és la quantitat de ciutats visitades.
 * 
 */
#ifndef VIATGE_HH
#define VIATGE_HH

#ifndef NO_DIAGRAM
#include <list>
#include <string>
#include <iostream>
#endif

using namespace std;

/**
 * @class Viatge
 * @brief Representa un viatge amb una ruta, una quantitat de productes comerciats i una distància recorreguda.
 * 
 * Un objecte de la classe Viatge conté una llista de ciutats visitades, una quantitat de productes comerciats i una distància recorreguda.
 */
class Viatge {

private:
	list<string> ruta;  ///< Llista de ciutats visitades.
	int quant_comerciat;  ///< Quantitat de productes comerciats.
	int distancia;  ///< Distància recorreguda.

public:
	/* CONSTRUCTORS */
	/**
	 * @brief Constructora per defecte de la classe Viatge.
	 * 
	 * \pre Cert.
	 * \post Viatge amb tots els paràmetres inicialitzats a valors per defecte.
	 */
	Viatge();

	/* MODIFICADORS */
	/**
	 * @brief Afegir una ciutat a la ruta del viatge.
	 * 
	 * \pre id_city és un identificador vàlid. dir és una direcció vàlida {'d','e','r'}. conjunt és vàlid.
	 * \post La ciutat s'ha afegit a la ruta i s'ha actualitzat la distància i l'ordre.
	 */
	void afegirCiutat(std::string id_city);

	/**
	 * @brief Actualitzar la quantitat total comerciada.
	 * 
	 * \pre quant és un valor vàlid.
	 * \post S'ha incrementat la quantitat comerciada pel valor de quant.
	 */
	void actQuant(int quant);

	/**
	 * @brief Incorporar millor subviatge al viatge actual.
	 * 
	 * \pre v és un viatge vàlid.
	 * \post S'ha actualitzat el viatge amb les dades del subviatge.
	 */
	void actViatge(Viatge &v);

	/* CONSULTORS */
	/**
	 * @brief Consultar ruta del viatge.
	 * 
	 * \pre Cert.
	 * \post Retorna la llista de ciutats visitades.
	 */
	list<string> consultarRuta() const;

	/**
	 * @brief Consultar la quantitat total comerciada.
	 * 
	 * \pre Cert.
	 * \post Retorna la quantitat total comerciada.
	 */
	int consultarQuant() const;

	/**
	 * @brief Consultar la distància total recorreguda.
	 * 
	 * \pre Cert.
	 * \post Retorna la distància total recorreguda.
	 */
	int consultarDist() const;

	/**
	 * @brief Consultar l'última ciutat visitada.
	 * 
	 * \pre Cert.
	 * \post Retorna el id de l'última ciutat visitada.
	 */
	string consultarUltimaCiutat() const;
};

#endif