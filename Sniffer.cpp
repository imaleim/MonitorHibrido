#include "Sniffer.h"
#include "JSONGen.h"
#include "Analisis.h"
#include <sstream>
#include <arpa/inet.h>
#include <pcap.h>
#include <iostream>
#include <netinet/ip.h>
#include <netinet/if_ether.h>

void packetHandler(u_char*,
                   const struct pcap_pkthdr* header,
                   const u_char* packet) {

    const struct ether_header* eth =
        (struct ether_header*)packet;

    if (ntohs(eth->ether_type) == ETHERTYPE_ARP) {

    std::cout << "[ARP] paquete detectado\n";

    registrarARP();

    std::stringstream bytes;

    for (int i = 0; i < 24; i++) {
        bytes << std::hex << (int)packet[i] << " ";
    }

    guardarARPPacket("unknown", bytes.str());

    return;
}

    if (ntohs(eth->ether_type) == ETHERTYPE_IP) {

        const struct ip* iphdr =
            (struct ip*)(packet + sizeof(ether_header));

        switch (iphdr->ip_p) {

            case IPPROTO_ICMP:
                std::cout << "[ICMP] paquete detectado\n";
                registrarICMP();
                break;

            case IPPROTO_TCP:
                std::cout << "[TCP] paquete detectado\n";
                break;

            case IPPROTO_UDP:
                std::cout << "[UDP] paquete detectado\n";
                break;
        }
    }
}

void iniciarSniffer(const std::string& iface) {

    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t* handle =
        pcap_open_live(iface.c_str(),
                       BUFSIZ,
                       1,
                       1000,
                       errbuf);

    if (!handle) {
        std::cerr << "Error pcap\n";
        return;
    }

    pcap_loop(handle, 0, packetHandler, NULL);

    pcap_close(handle);
}