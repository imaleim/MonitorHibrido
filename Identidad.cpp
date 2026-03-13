#include "Identidad.h"
#include "JSONGen.h"
#include <fstream>
#include <iostream>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netdb.h>  
#include <thread>
#include <chrono>

std::string obtenerMAC(const std::string& iface) {
    std::ifstream file("/sys/class/net/" + iface + "/address");
    std::string mac;
    getline(file, mac);
    return mac;
}

std::string obtenerIP(const std::string& iface) {
    struct ifaddrs *ifaddr, *ifa;
    char host[NI_MAXHOST];

    getifaddrs(&ifaddr);

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {

        if (ifa->ifa_addr == NULL) continue;

        if (ifa->ifa_addr->sa_family == AF_INET &&
            iface == ifa->ifa_name) {

            getnameinfo(ifa->ifa_addr,
                        sizeof(struct sockaddr_in),
                        host, NI_MAXHOST,
                        NULL, 0, NI_NUMERICHOST);

            freeifaddrs(ifaddr);
            return std::string(host);
        }
    }

    freeifaddrs(ifaddr);
    return "";
}

void monitorearIdentidad(std::string iface, int intervalo) {

    std::string mac_prev = obtenerMAC(iface);
    std::string ip_prev = obtenerIP(iface);

    while (true) {

        std::string mac = obtenerMAC(iface);
        std::string ip = obtenerIP(iface);

        if (mac != mac_prev) {
            std::cout << "[EVENTO] Cambio MAC "
                      << mac_prev << " -> " << mac << std::endl;
            
            guardarCambioMAC(mac_prev, mac); 
            mac_prev = mac;
        }

        if (ip != ip_prev) {
            std::cout << "[EVENTO] Cambio IP "
                      << ip_prev << " -> " << ip << std::endl;
            
            guardarAnomalia("Cambio de IP detectado"); 
            ip_prev = ip;
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(intervalo));
    }
}