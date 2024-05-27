/** @mainpage <b> Pràctica PRO2 2023-2024: Comerç Fluvial </b>
 * @author Pau Bru Ribes (pau.bru@estudiantat.upc.edu)
 * 
 * @brief Programa que simula el comerç entre ciutats i/o amb un vaixell en una cuenca fluvial.
 * 
 * Les classes principals del programa són:
 * - \b Ciutat: Classe que representa una ciutat amb un identificador i un inventari de productes.
 * - \b Cjt_ciutats: Classe que representa un conjunt de ciutats.
 * - \b Cjt_productes: Classe que representa un conjunt de productes.
 * - \b Llanxa: Classe que representa una llanxa (vaixell petit) només destinat a calcular el millor viatge.
 * - \b Vaixell: Classe que representa un vaixell amb un inventari de productes.
 * - \b Viatge: Classe que representa un viatge entre ciutats.
 * 
 */

/**
 * @file program.cc
 * @brief Programa principal de la pràctica.
 * 
 * Aquest programa gestiona el comerç entre ciutats i un vaixell d'una cuenca fluvial. La cuenca és un arbre binari que representa les connexions entre les ciutats.
 * 
 * Aquest arbre només té els id's de les ciutats, després és fa servir un conjunt de ciutats per obtenir les dades de les ciutats.
 * Una ciutat pot tindre 2 ciutats fills o cap. De la estructura d'arbre tradicional, el root seria l'ultima ciutat de la cuenca mentre que les fulles serien les ciutats d'on comença un afluent.
 * 
 * Hi ha un conjunt de productes que no pot ser buit on es guarden els productes disponibles. El id comença per 1 i és incremental.
 * 
 * Una ciutat pot tindre o no inventari de productes. Aquest inventari es pot modificar afegint, eliminant o modificant productes.
 *
 * Un vaixell sempre té un inventari vàlid on té una quantitat d'un determinat producte per a vendre i un altre per a comprar (diferents). Aquest inventari es pot modificar.
 * El vaixell també té un registre de les ultimes ciutats on ha comerciat cada vegada que s'ha fet un viatge al llarg de la cuenca.
 * 
 * La classe Llanxa representa una versió del vaixell més reduïda que només s'utilitza per a calcular el millor viatge a realitzar.
 * Això implica que només té la informació sobre els productes de compra i venta del vaixell juntament amb mètodes modificats per a ser més optims.
 * 
 * La classe viatge ajuda a organitzar les dades per a realitzar un viatge entre ciutats. Conté la quantitat total de productes comerciats si es realitza el viatge i les ciutats per on passa.
 * 
 * \details Les polítiques de programació són:
 * - Per a la classe Cjt_productes s'ha decidit fer servir un vector per a tenir un accés ràpid donat que el id és numèric i incremental.
 * - Per a la classe Cjt_ciutats s'ha decidit fer servir un map per a tenir un accés més ràpid a les ciutats.
 * - Per a l'operació de viatge s'ha decidit crear una nova classe per millorar la llegibilitat del codi.
 * - No s'ha fet servir un BinTree de ciutats donat que modificar les ciutats dins de l'arbre gran perdem eficiencia.
 * - Els paràmetres que es passen a una mètode de la classe sempre són correctes.
 * 
 */

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include <list>
#include <utility>
#endif

#include "Llanxa.hh"
#include "Viatge.hh"
#include "BinTree.hh"
#include "Vaixell.hh"
#include "Cjt_ciutats.hh"
#include "Cjt_productes.hh"

using namespace std;

/**
 * @brief Llegir inventari d'una ciutat.
 * 
 * Primer s'ha de llegir el nom de la ciutat i després la quantitat de productes a afegeir.
 * És comprova si la ciutat existeix i les dades són vàlides.
 * És modifica l'inventari de la ciutat amb els nous productes.
 * 
 * \pre ciutats i productes són vàlids.
 * \post Ciutat modificada amb els nous productes.
 */
void leer_inventario(Cjt_ciutats& ciutats, Cjt_productes& productes) {
    // Info sobre Ciutat
    string id_ciutat;
    cin >> id_ciutat;
    cout << ' ' << id_ciutat << endl;
    if (not ciutats.existeixCiutat(id_ciutat)) {cout << "error: no existe la ciudad" << endl; return;}
    ciutats.eliminarTotsProdDeCiutat(id_ciutat);
    
    // Info sobre els productes
    int quant_prod;
    cin >> quant_prod;
    for (int j = 0; j<quant_prod; j++) {
        // Info sobre el producte
        int id_prod, oferta, demanda;
        cin >> id_prod >> oferta >> demanda;

        // Comprovar si les dades son correctes
        if (oferta<0) {cout << "error: oferta no valida" << endl; continue;}
        if (demanda<=0) {cout << "error: demanda no valida" << endl; continue;}
        if (not productes.existeixProducte(id_prod)) {cout << "error: no existe el producto" << endl; continue;}
        
        // Saber les dades sobre el producte a afegir
        pair<int,int> pesVol = productes.consultarProducte(id_prod);
        
        // Afegir el producte a la ciutat directament
        ciutats.afegirProdACiutat(id_ciutat, id_prod, oferta, demanda, pesVol.first, pesVol.second);
    }
}

/**
 * @brief Llegir inventaris de les ciutats que es van especificant.
 * 
 * Mentre que la ciutat no sigui "#" s'ha de llegir l'inventari de la ciutat.
 * És comprova si la ciutat existeix i les dades són vàlides.
 * S'esborra tots els productes de la ciutat i s'afegeixen els nous productes.
 * 
 * \pre ciutats i productes són vàlids. 
 * \post Ciutats modificades amb els nous productes.
 */
void leer_inventarios(Cjt_ciutats& ciutats, Cjt_productes& productes) {
    string id_ciutat;
    while (cin >> id_ciutat and id_ciutat!="#") {
        if (not ciutats.existeixCiutat(id_ciutat)) {cout << "error: no existe la ciudad" << endl; return;}
        ciutats.eliminarTotsProdDeCiutat(id_ciutat);
        
        // Info sobre els productes
        int quant_prod;
        cin >> quant_prod;
        for (int j = 0; j<quant_prod; j++) {
            // Info sobre el producte
            int id_prod, oferta, demanda;
            cin >> id_prod >> oferta >> demanda;
            
            // Comprovar si les dades son correctes
            if (oferta<0) {cout << "error: oferta no valida" << endl; continue;}
            if (demanda<=0) {cout << "error: demanda no valida" << endl; continue;}
            if (not productes.existeixProducte(id_prod)) {cout << "error: no existe el producto" << endl; continue;}

            // Saber les dades sobre el producte a afegir
            pair<int,int> pesVol = productes.consultarProducte(id_prod);
            
            // Afegir el producte a la ciutat directament
            ciutats.afegirProdACiutat(id_ciutat, id_prod, oferta, demanda, pesVol.first, pesVol.second);
        }
    }
}

/**
 * @brief Modificar el vaixell amb les noves dades.
 * 
 * És llegeixen les dades de compra i venda de productes i es comprova si són vàlides.
 * Si no són el mateix producte, es modifica el vaixell amb els nous productes.
 * 
 * \pre barco i productes són vàlids.
 * \post Vaixell modificat amb els nous productes.
 */
void modificar_barco(Vaixell& barco, Cjt_productes& productes) {
    // Info sobre la Compra
    int prod_compra, quant_compra;
    cin >> prod_compra >> quant_compra;
    if (not productes.existeixProducte(prod_compra)) {cout << "error: no existe el producto" << endl; return;}
    
    // Info sobre la Venta
    int prod_venta, quant_venta;
    cin >> prod_venta >> quant_venta;
    if (not productes.existeixProducte(prod_venta)) {cout << "error: no existe el producto" << endl; return;}

    if (prod_compra==prod_venta) {cout<< "error: no se puede comprar y vender el mismo producto" << endl; return;}
    barco.modificarMercancia(prod_compra, quant_compra, prod_venta, quant_venta);
}

/**
 * @brief Escriure les dades del vaixell.
 * 
 * Es mostren les dades del vaixell.
 * 
 * \pre barco és vàlid.
 * \post Dades del vaixell mostrades per pantalla.
 */
void escribir_barco(Vaixell& barco) {
    barco.escriure();
}

/**
 * @brief Afegir productes al conjunt de productes.
 * 
 * Es llegeix la quantitat de productes a afegir i s'afegeixen al conjunt de productes.
 * 
 * \pre productes és vàlid.
 * \post Productes afegits al conjunt de productes.
 */
void agregar_productos(Cjt_productes& productes) {
    int usr_quant;
    cin >> usr_quant;
    cout << ' ' << usr_quant << endl;
    productes.llegir(usr_quant);
}

/**
 * @brief Escriure les dades d'un producte.
 * 
 * Es llegeix l'identificador del producte i es comprova si existeix.
 * Si existeix es mostren les dades del producte.
 * 
 * \pre productes és vàlid.
 * \post Dades del producte mostrades per pantalla.
 */
void escribir_producto(Cjt_productes& productes) {
    int id_prod;
    cin >> id_prod;
    cout << ' ' << id_prod << endl;
    if (not productes.existeixProducte(id_prod)) {cout << "error: no existe el producto" << endl; return;}
    
    productes.escriureProd(id_prod);
}

/**
 * @brief Escriure les dades d'una ciutat.
 * 
 * Es llegeix l'identificador de la ciutat i es comprova si existeix.
 * Si existeix es mostren les dades de la ciutat.
 * 
 * \pre ciutats és vàlid.
 * \post Dades de la ciutat mostrades per pantalla.
 */
void escribir_ciudad(Cjt_ciutats& ciutats) {
    string id_city;
    cin >> id_city;
    cout << ' ' << id_city << endl;
    if (not ciutats.existeixCiutat(id_city)) {cout << "error: no existe la ciudad" << endl; return;}
    
    ciutats.escriureCiutat(id_city);
}

/**
 * @brief Afegir un producte a una ciutat.
 * 
 * És llegeixen les dades de la ciutat i del producte a afegir.
 * És comprova si les dades són vàlides.
 * Si la ciutat ja té el producte, és mostra un error.
 * És modifica la ciutat amb el nou producte i es mostra el nou pes i volum total de la ciutat.
 * 
 * \pre ciutats i productes són vàlids.
 * \post Ciutat modificada amb el nou producte.
 */
void poner_prod(Cjt_ciutats& ciutats, const Cjt_productes& productes) {
    string id_city;
    int id_prod, oferta, demanda;
    cin >> id_city >> id_prod >> oferta >> demanda;
    cout << ' ' << id_city << ' ' << id_prod << endl;

    // Comprovar si les dades son correctes
    if (not productes.existeixProducte(id_prod)) {cout << "error: no existe el producto" << endl; return;}
    if (not ciutats.existeixCiutat(id_city)) {cout << "error: no existe la ciudad" << endl; return;}
    if (oferta<0) {cout << "error: oferta no valida" << endl; return;}
    if (demanda<=0) {cout << "error: demanda no valida" << endl; return;}
    
    // Comprovar si la ciutat ja té el producte
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    if (temp_city.teProducte(id_prod)) {cout << "error: la ciudad ya tiene el producto" << endl; return;}
    
    // Saber les dades sobre el producte a afegir
    pair<int,int> pesVol = productes.consultarProducte(id_prod);

    // Afegir el producte a la ciutat
    temp_city.afegirProdAlInventari(id_prod, oferta, demanda, pesVol.first, pesVol.second);
    ciutats.modificarCiutat(id_city, temp_city);
    
    // Mostrar nou pes i volum total de la ciutat
    cout << temp_city.consultarPesTotal() << ' ' << temp_city.consultarVolumTotal() << endl;
}

/**
 * @brief Modificar un producte d'una ciutat.
 * 
 * És llegeixen les dades de la ciutat i del producte a modificar.
 * És comprova si les dades són vàlides.
 * Si la ciutat no té el producte, és mostra un error.
 * És modifica la ciutat amb el producte modificat i es mostra el nou pes i volum total de la ciutat.
 * 
 * \pre ciutats i productes són vàlids.
 * \post Ciutat modificada amb el producte modificat.
 */
void modificar_prod(Cjt_ciutats& ciutats, const Cjt_productes& productes) {
    string id_city;
    int id_prod, oferta, demanda;
    cin >> id_city >> id_prod >> oferta >> demanda;
    cout << ' ' << id_city << ' ' << id_prod << endl;

    // Comprovar si les dades son correctes
    if (not productes.existeixProducte(id_prod)) {cout << "error: no existe el producto" << endl; return;}
    if (not ciutats.existeixCiutat(id_city)) {cout << "error: no existe la ciudad" << endl; return;}
    if (oferta<0) {cout << "error: oferta no valida" << endl; return;}
    if (demanda<=0) {cout << "error: demanda no valida" << endl; return;}
    
    // Comprovar si la ciutat no té el producte
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    if (not temp_city.teProducte(id_prod)) {cout << "error: la ciudad no tiene el producto" << endl; return;}
    
    // Saber les dades sobre el producte a modiuficar
    pair<int,int> pesVol = productes.consultarProducte(id_prod);
    
    // Modificar el producte a la ciutat
    temp_city.modificarProdDelInventari(id_prod, oferta, demanda, pesVol.first, pesVol.second);
    ciutats.modificarCiutat(id_city,temp_city);

    // Mostrar nou pes i volum total de la ciutat
    cout << temp_city.consultarPesTotal() << ' ' << temp_city.consultarVolumTotal() << endl;
}

/**
 * @brief Treure un producte d'una ciutat.
 * 
 * És llegeixen les dades de la ciutat i del producte a treure.
 * És comprova si les dades són vàlides.
 * Si la ciutat no té el producte, és mostra un error.
 * És modifica la ciutat eliminant el producte i es mostra el nou pes i volum total de la ciutat.
 * 
 * \pre ciutats i productes són vàlids.
 * \post Ciutat modificada sense el producte.
 */
void quitar_prod(Cjt_ciutats& ciutats, const Cjt_productes& productes) {
    string id_city;
    int id_prod;
    cin >> id_city >> id_prod;
    cout << ' ' << id_city << ' ' << id_prod << endl;

    // Comprovar si les dades son correctes
    if (not productes.existeixProducte(id_prod)) {cout << "error: no existe el producto" << endl; return;}
    if (not ciutats.existeixCiutat(id_city)) {cout << "error: no existe la ciudad" << endl; return;}
    
    // Comprovar si la ciutat no té el producte
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    if (not temp_city.teProducte(id_prod)) {cout << "error: la ciudad no tiene el producto" << endl; return;}
    
    // Saber les dades sobre el producte a eliminar
    pair<int,int> pesVol = productes.consultarProducte(id_prod);
    
    // Eliminar el producte de la ciutat
    temp_city.eliminarProdDelInventari(id_prod, pesVol.first, pesVol.second);
    ciutats.modificarCiutat(id_city,temp_city);

    // Mostrar nou pes i volum total de la ciutat
    cout << temp_city.consultarPesTotal() << ' ' << temp_city.consultarVolumTotal() << endl;
}

/**
 * @brief Consultar les dades d'un producte d'una ciutat.
 * 
 * És llegeixen les dades de la ciutat i del producte a consultar.
 * És comprova si les dades són vàlides.
 * Si la ciutat no té el producte, és mostra un error.
 * Es mostren les dades del producte respecte la ciutat especificada.
 * 
 * \pre ciutats i productes són vàlids.
 * \post Dades del producte mostrades per pantalla.
 */
void consultar_prod(Cjt_ciutats& ciutats, Cjt_productes& productes) {
    string id_city;
    int id_prod;
    cin >> id_city >> id_prod;
    cout << ' ' << id_city << ' ' << id_prod << endl;

    // Comprovar si les dades son correctes
    if (not productes.existeixProducte(id_prod)) {cout << "error: no existe el producto" << endl; return;}
    if (not ciutats.existeixCiutat(id_city)) {cout << "error: no existe la ciudad" << endl; return;}
    
    // Comprovar si la ciutat no té el producte
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    if (not temp_city.teProducte(id_prod)) {cout << "error: la ciudad no tiene el producto" << endl; return;}
    
    // Mostrar oferta i demanda del producte respecte la ciutat especificada
    cout << temp_city.consultarOferta(id_prod) << ' ' << temp_city.consultarDemanda(id_prod) << endl;
}

/**
 * @brief Comerciar entre dues ciutats.
 * 
 * És llegeixen les dades de les dues ciutats a comerciar.
 * És comprova que les dues ciutats existeixin i que no siguin la mateixa.
 * Es realitza el comerç entre les dues ciutats.
 * 
 * \pre ciutats i productes són vàlids.
 * \post Comerç realitzat entre les dues ciutats.
 */
void comerciar(Cjt_ciutats& ciutats, const Cjt_productes& productes) {
    string id_city1, id_city2;
    cin >> id_city1 >> id_city2;
    cout << ' ' << id_city1 << ' ' << id_city2 << endl;

    // Comprovar si les dades son correctes
    if (id_city1==id_city2) {cout << "error: ciudad repetida" << endl; return;}
    if (not ciutats.existeixCiutat(id_city1)) {cout << "error: no existe la ciudad" << endl; return;}
    if (not ciutats.existeixCiutat(id_city2)) {cout << "error: no existe la ciudad" << endl; return;}
    
    // Comerciar entre les ciutats
    ciutats.comerciar(id_city1, id_city2, productes);
}

/**
 * @brief Realitzar un viatge entre ciutats.
 * 
 * Es determina el millor viatge a realitzar i si es comercia algún producte es realitza.
 * 
 * \pre cuenca, ciutats, productes i barco són vàlids.
 * \post Viatge realitzat. Les ciutats són modificades però el vaixell no.
 */
void hacer_viaje(const BinTree<string>& cuenca, const Cjt_productes& productes, Vaixell& barco, Cjt_ciutats& ciutats) {
    // Determinar el millor viatge a realitzar
    Llanxa lancha(barco);
    Viatge ruta = ciutats.determinar_viatge(cuenca, productes, lancha);

    // Consultar quantitat de productes comerciats en el millor viatge
    int quantitat_comerciat = ruta.consultarQuant();
    cout << quantitat_comerciat << endl;

    // Realitzar el viatge si hi ha productes a comerciar
    if (quantitat_comerciat!=0) {
        // Guardar l'última ciutat on s'ha comerciat
        string id_last_city = ruta.consultarUltimaCiutat();
        barco.afegirCiutat(id_last_city);

        // Realitzar el millor viatge modificant les ciutats però el vaixell no
        ciutats.realitzar_viatge(productes, ruta, barco);
    }
}

/**
 * @brief Funció principal del programa.
 * 
 * El programa comença declarant els objectes necessaris.
 * Un cop inicialitzades les variables principals (productes, ciutats i vaixell) es comença a llegir les comandes.
 * 
 * Les comandes poden ser de diferents tipus:
 * - Leer_rio: Llegir la cuenca.
 * - Leer_inventario: Llegir l'inventari d'una ciutat.
 * - Leer_inventarios: Llegir els inventaris de les ciutats.
 * - Modificar_barco: Modificar el vaixell.
 * - Escribir_barco: Escriure les dades del vaixell.
 * - Consultar_num: Consultar el nombre de productes.
 * - Agregar_productos: Afegir productes al conjunt de productes.
 * - Escribir_producto: Escriure les dades d'un producte.
 * - Escribir_ciudad: Escriure les dades d'una ciutat.
 * - Poner_prod: Afegir un producte a una ciutat.
 * - Modificar_prod: Modificar un producte d'una ciutat.
 * - Quitar_prod: Treure un producte d'una ciutat.
 * - Consultar_prod: Consultar les dades d'un producte d'una ciutat.
 * - Comerciar: Comerciar entre dues ciutats.
 * - Redistribuir: Redistribuir els productes entre les ciutats.
 * - Hacer_viaje: Realitzar el viatge que faci que el vaixell comercii més quantitat entre ciutats.
 * Nota: Si una comanda no és vàlida, es deixa passar.
 * 
 */

int main () {
    // === Introducció
    // Demanar productes
    Cjt_productes productes;
    int quant_prod;
    cin >> quant_prod;
    productes.llegir(quant_prod);

    // Demanar cuenca
    Cjt_ciutats ciutats;
    BinTree<string> cuenca = ciutats.leer_rio();

    // Demanar vaixell
    Vaixell barco;
    barco.llegir(productes);

    // === Commandes
    string usr_op;
    while (cin >> usr_op and usr_op!="fin") {
        if (usr_op == "//") {
            getline(cin, usr_op);
            continue; // Anar a la següent iteració del bucle
        }
        else if (usr_op=="leer_rio" or usr_op=="lr") {
            cout << "#" << usr_op << endl;
            barco.eliminarRegistre();
            cuenca = ciutats.leer_rio();
        }
        else if (usr_op=="leer_inventario" or usr_op=="li") {
            cout << "#" << usr_op;
            leer_inventario(ciutats, productes);
        }
        else if (usr_op=="leer_inventarios" or usr_op=="ls") {
            cout << "#" << usr_op << endl;
            leer_inventarios(ciutats, productes);
        }
        else if (usr_op=="modificar_barco" or usr_op=="mb") {
            cout << "#" << usr_op << endl;
            modificar_barco(barco, productes);
        }
        else if (usr_op=="escribir_barco" or usr_op=="eb") {
            cout << "#" << usr_op << endl;
            escribir_barco(barco);
        }
        else if (usr_op=="consultar_num" or usr_op=="cn") {
            cout << "#" << usr_op << endl;
            cout << productes.consultarQuantitatProd() << endl;
        }
        else if (usr_op=="agregar_productos" or usr_op=="ap") {
            cout << "#" << usr_op;
            agregar_productos(productes);
        }
        else if (usr_op=="escribir_producto" or usr_op=="ep") {
            cout << "#" << usr_op;
            escribir_producto(productes);
        }
        else if (usr_op=="escribir_ciudad" or usr_op=="ec") {
            cout << "#" << usr_op;
            escribir_ciudad(ciutats);
        }
        else if (usr_op=="poner_prod" or usr_op=="pp") {
            cout << "#" << usr_op;
            poner_prod(ciutats, productes);
        }
        else if (usr_op=="modificar_prod" or usr_op=="mp") {
            cout << "#" << usr_op;
            modificar_prod(ciutats, productes);
        }
        else if (usr_op=="quitar_prod" or usr_op=="qp") {
            cout << "#" << usr_op;
            quitar_prod(ciutats, productes);
        }
        else if (usr_op=="consultar_prod" or usr_op=="cp") {
            cout << "#" << usr_op;
            consultar_prod(ciutats, productes);
        }
        else if (usr_op=="comerciar" or usr_op=="co") {
            cout << "#" << usr_op;
            comerciar(ciutats, productes);
        }
        else if (usr_op=="redistribuir" or usr_op=="re") {
            cout << "#" << usr_op << endl;
            ciutats.redistribuir(cuenca, productes);
        }
        else if (usr_op == "hacer_viaje" or usr_op == "hv") {
            cout << "#" << usr_op << endl;
            hacer_viaje(cuenca, productes, barco, ciutats);
        }
    }
}