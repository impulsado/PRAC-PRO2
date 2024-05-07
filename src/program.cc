#include <iostream>
#include <string>
#include "BinTree.hh"
#include "Vaixell.hh"
#include "Cjt_ciutats.hh"
#include "Cjt_productes.hh"

using namespace std;

BinTree<string> leer_rio(Cjt_ciutats& ciutats) {
    string id_city;
    cin >> id_city;

    // Base Case
    if (id_city=="#") return BinTree<string>();

    // General Case
    Ciutat node(id_city);
    ciutats.afegirCiutat(id_city, node);
    BinTree<string> esq = leer_rio(ciutats);
    BinTree<string> dret = leer_rio(ciutats);
    
    return BinTree<string>(id_city,esq,dret);
}

void leer_inventario(Cjt_ciutats& ciutats, Cjt_productes& productes, int num_ciutats) {
    for (int i = 0; i<num_ciutats; i++) {
        // Info sobre Ciutat
        string id_ciutat;
        cin >> id_ciutat;
        if (not ciutats.existeixCiutat(id_ciutat)) {cout << "Error: No existeix la ciutat" << endl; break;}
        
        // Info sobre els productes
        int quant_prod;
        cin >> quant_prod;
        for (int j = 0; j<quant_prod; j++) {
            // Info sobre el producte
            int id_prod, oferta, demanda;
            cin >> id_prod >> oferta >> demanda;
            // ?? Aqui paro tota l'execucio ??
            if (0<oferta) {cout << "Error: Oferta no valida" << endl; continue;}
            if (0<=demanda) {cout << "Error: Demanda no valida" << endl; continue;}
            if (not productes.existeixProducte(id_prod)) {cout << "Error: No existeix el producte" << endl; continue;}
            // ?? Que passa si la ciutat ja té el producte ??
            /*
            Ciutat temp_city = ciutats.consultarCiutat(id_ciutat);
            if (temp_city.teProducte(id_prod)) {cout << "Error: La ciutat ja té el producte" << endl; continue;}
            */
            
            // Saber les dades sobre el producte a afegir
            Producte temp_prod = productes.consultarProducte(id_prod);
            int pes = temp_prod.consultarPes();
            int volum = temp_prod.consultarVolum();
            // Afegir el producte a la ciutat directament
            ciutats.afegirProdACiutat(id_ciutat,id_prod,oferta,demanda,pes,volum);
        }
    }
}

void modificar_barco(Vaixell& barco, Cjt_productes& productes) {
    // NOTA: Es garantitza que les quantitats seràn valides.
    // Info sobre la Venta
    int prod_venta, quant_venta;
    cin >> prod_venta >> quant_venta;
    if (not productes.existeixProducte(prod_venta)) {cout << "Error: No existeix el producte" << endl; return;}
    
    // Info sobre la Compra
    int prod_compra, quant_compra;
    cin >> prod_compra >> quant_compra;
    if (not productes.existeixProducte(prod_compra)) {cout << "Error: No existeix el producte" << endl; return;}

    if (prod_compra==prod_venta) {cout<< "Error: No poden ser el mateix producte" << endl; return;}
    barco.modificarMercancia(prod_compra, quant_compra, prod_venta, quant_venta);
}

// ?? Revisar Format ??
// ?? Que passa si barco encara no te les dades correctes ??
void escribir_barco(Vaixell& barco) {
    barco.mostrarProdAComprar();
    barco.mostrarProdAVendre();
    barco.mostrarRegistreViatjes();
}

void agregar_productos(Cjt_productes& productes) {
    int pes, volum;
    cin >> pes >> volum;
    if (pes<=0) {cout << "Error: Pes no vàlid" << endl; return;}
    if (volum<=0) {cout << "Error: Volum no vàlid" << endl; return;}
    
    productes.afegirProducte(pes,volum);
}

void escribir_producto(Cjt_productes& productes) {
    int id_prod;
    cin >> id_prod;
    if (not productes.existeixProducte(id_prod)) {cout << "Error: No existeix el producte" << endl; return;}
    
    Producte temp_prod = productes.consultarProducte(id_prod);
    
    temp_prod.escriure();
}

void escribir_ciudad(Cjt_ciutats& ciutats) {
    string id_city;
    if (not ciutats.existeixCiutat(id_city)) {cout << "Error: No existeix la ciutat" << endl; return;}
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    temp_city.escriure();
}

void poner_prod(Cjt_ciutats& ciutats, const Cjt_productes& productes) {
    string id_city;
    int id_prod, oferta, demanda;
    cin >> id_city >> id_prod >> oferta >> demanda;
    if (not productes.existeixProducte(id_prod)) {cout << "Error: No existeix el producte" << endl; return;}
    if (not ciutats.existeixCiutat(id_city)) {cout << "Error: No existeix la ciutat" << endl; return;}
    if (0<oferta) {cout << "Error: Oferta no valida" << endl; return;}
    if (0<=demanda) {cout << "Error: Demanda no valida" << endl; return;}
    
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    if (temp_city.teProducte(id_prod)) {cout << "Error: La ciutat ja té aquest producte" << endl; return;}
    
    Producte temp_prod = productes.consultarProducte(id_prod);
    int pes = temp_prod.consultarPes();
    int volum = temp_prod.consultarVolum();

    temp_city.afegirProdAlInventari(id_prod,oferta,demanda,pes,volum);
    ciutats.modificarCiutat(id_city,temp_city);
    cout << "Pes Total: " << temp_city.consultarPesTotal() << endl;
    cout << "Volum Total: " << temp_city.consultarVolumTotal() << endl;
}

void modificar_prod(Cjt_ciutats& ciutats, const Cjt_productes& productes) {
    string id_city;
    int id_prod, oferta, demanda;
    cin >> id_city >> id_prod >> oferta >> demanda;
    if (not productes.existeixProducte(id_prod)) {cout << "Error: No existeix el producte" << endl; return;}
    if (not ciutats.existeixCiutat(id_city)) {cout << "Error: No existeix la ciutat" << endl; return;}
    if (0<oferta) {cout << "Error: Oferta no valida" << endl; return;}
    if (0<=demanda) {cout << "Error: Demanda no valida" << endl; return;}
    
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    if (not temp_city.teInventari()) {cout << "Error: La ciutat no té inventari" << endl; return;}
    if (not temp_city.teProducte(id_prod)) {cout << "Error: La ciutat no té aquest producte" << endl; return;}
    
    Producte temp_prod = productes.consultarProducte(id_prod);
    int pes = temp_prod.consultarPes();
    int volum = temp_prod.consultarVolum();
    
    temp_city.modificarProdDelInventari(id_prod,oferta,demanda,pes,volum);
    ciutats.modificarCiutat(id_city,temp_city);
    cout << "Pes Total: " << temp_city.consultarPesTotal() << endl;
    cout << "Volum Total: " << temp_city.consultarVolumTotal() << endl;
}

void quitar_prod(Cjt_ciutats& ciutats, const Cjt_productes& productes) {
    string id_city;
    int id_prod;
    cin >> id_city >> id_prod;
    if (not productes.existeixProducte(id_prod)) {cout << "Error: No existeix el producte" << endl; return;}
    if (not ciutats.existeixCiutat(id_city)) {cout << "Error: No existeix la ciutat" << endl; return;}
    
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    if (not temp_city.teInventari()) {cout << "Error: La ciutat no té inventari" << endl; return;}
    if (not temp_city.teProducte(id_prod)) {cout << "Error: La ciutat no té aquest producte" << endl; return;}
    
    Producte temp_prod = productes.consultarProducte(id_prod);
    int pes = temp_prod.consultarPes();
    int volum = temp_prod.consultarVolum();
    
    temp_city.eliminarProdDelInventari(id_prod,pes,volum);
    ciutats.modificarCiutat(id_city,temp_city);
    cout << "Pes Total: " << temp_city.consultarPesTotal() << endl;
    cout << "Volum Total: " << temp_city.consultarVolumTotal() << endl;
}

void comerciar(Cjt_ciutats& ciutats, const Cjt_productes& productes) {
    string id_city1, id_city2;
    cin >> id_city1 >> id_city2;
    if (not ciutats.existeixCiutat(id_city1)) {cout << "Error: No existeix la ciutat1" << endl; return;}
    if (not ciutats.existeixCiutat(id_city2)) {cout << "Error: No existeix la ciutat2" << endl; return;}
    
    ciutats.comerciar(id_city1, id_city2, productes);
}

void consultar_prod(Cjt_ciutats& ciutats,Cjt_productes& productes) {
    string id_city;
    int id_prod;
    cin >> id_city >> id_prod;
    if (not productes.existeixProducte(id_prod)) {cout << "Error: No existeix el producte" << endl; return;}
    if (not ciutats.existeixCiutat(id_city)) {cout << "Error: No existeix la ciutat" << endl; return;}
    
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    if (not temp_city.teInventari()) {cout << "Error: La ciutat no té inventari" << endl; return;}
    if (not temp_city.teProducte(id_prod)) {cout << "Error: La ciutat no té aquest producte" << endl; return;}
    
    cout << "Oferta: " << temp_city.consultarOferta(id_prod) << endl;
    cout << "Demanda: " << temp_city.consultarDemanda(id_prod) << endl;
}

int main () {
    Cjt_ciutats ciutats;
    BinTree<string> cuenca;

    // === Introducció
    // Demanar productes
    int usr_quant_prod;
    cin >> usr_quant_prod;
    Cjt_productes productes(usr_quant_prod);
    for (int i = 0; i<usr_quant_prod; i++) {
        int usr_prod_pes, usr_prod_volum;
        cin >> usr_prod_pes >> usr_prod_volum; 
        productes.afegirProducte(usr_prod_pes,usr_prod_volum);
    }
    
    // Demanar cuenca
    cuenca = leer_rio(ciutats);

    // Demanar vaixell
    Vaixell barco;
    barco.llegir(productes);

    // Commandes
    string usr_op;
    while (cin >> usr_op and usr_op!="fin") {
        if (usr_op == "//") {
            getline(cin, usr_op);
            continue; // Ir a la siguiente iteración del bucle
        }
        else if (usr_op=="leer_rio" or usr_op=="lr") {
            cuenca = leer_rio(ciutats);
        }
        else if (usr_op=="leer_inventario" or usr_op=="li") {
            leer_inventario(ciutats, productes, 1);
        }
        else if (usr_op=="leer_inventarios" or usr_op=="ls") {
            int quant;
            cin >> quant;
            // FERRR
        }
        else if (usr_op=="modificar_barco" or usr_op=="mb") {
            modificar_barco(barco, productes);
        }
        else if (usr_op=="escribir_barco" or usr_op=="eb") {
            escribir_barco(barco);
        }
        else if (usr_op=="consultar_num" or usr_op=="cn") {
            // ?? Revisar format ??
            cout << productes.consultarQuantitatProd() << endl;
        }
        else if (usr_op=="agregar_productos" or usr_op=="ap") {
            agregar_productos(productes);
        }
        else if (usr_op=="escribir_producto" or usr_op=="ep") {
            escribir_producto(productes);
        }
        else if (usr_op=="escribir_ciudad" or usr_op=="ec") {
            escribir_ciudad(ciutats);
        }
        else if (usr_op=="poner_prod" or usr_op=="pp") {
            poner_prod(ciutats,productes);
        }
        else if (usr_op=="modificar_prod" or usr_op=="mp") {
            modificar_prod(ciutats,productes);
        }
        else if (usr_op=="quitar_prod" or usr_op=="qp") {
            quitar_prod(ciutats,productes);
        }
        else if (usr_op=="consultar_prod" or usr_op=="cp") {
            consultar_prod(ciutats,productes);
        }
        else if (usr_op=="comerciar" or usr_op=="co") {
            comerciar(ciutats,productes);
        }
        else if (usr_op=="redistribuir" or usr_op=="re") {
            cout << "TODO" << endl;
        }
        else if (usr_op=="hacer_viaje" or usr_op=="hv") {
            cout << "TODO" << endl;
        }
    }
}