#include "Identidad.h"
#include "Sniffer.h"
#include "JSONGen.h"
#include <iostream>
#include <thread>
#include <csignal>

std::string archivoGlobal;

void terminar(int) {

    exportarJSON(archivoGlobal);

    std::cout << "\nJSON guardado correctamente\n";

    exit(0);
}

int main() {

    std::string iface;
    int intervalo;

    std::cout << "Interfaz de red: ";
    std::cin >> iface;

    std::cout << "Intervalo monitoreo (ms): ";
    std::cin >> intervalo;

    std::cout << "Archivo JSON salida: ";
    std::cin >> archivoGlobal;

    signal(SIGINT, terminar);

    std::thread t1(monitorearIdentidad, iface, intervalo);
    std::thread t2(iniciarSniffer, iface);

    t1.join();
    t2.join();

    return 0;
}