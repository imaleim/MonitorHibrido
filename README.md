# Proyecto: Monitor híbrido de identidad digital y tráfico anómalo en C++


### Descripción general

Herramienta desarrollada en C++ para Linux que monitorea cambios en la identidad digital del sistema (direcciones IP y MAC), captura tráfico de red en tiempo real y detecta posibles anomalías en el tráfico.
El programa registra todos los eventos detectados y genera un archivo JSON con la información de cada evento.

---------

### ***Integrantes del Equipo***

- ***Luis Santiago Cantu / GitHub - Sqntii***
  
  - Módulo Identidad
  - ev4.json

- ***Alejandra Itzel Ojeda / GitHub - imaleim***
  - Módulo Sniffer
  - Main

- ***Joustin Joel Martinez / Github - Joustin21***
  - Módulo Análisis
  - Módulo JSONGen

--------

### ***Requisitos***

- Ubuntu / Debian

- g++ (C++17)

- libpcap

- nlohmann/json

### ***Instalación de dependencias:***

    sudo apt install g++ libpcap-dev nlohmann-json3-dev

### ***Compilacion***

Desde la carpeta del proyecto ejecutar:

    g++ Main.cpp Identidad.cpp Sniffer.cpp Analisis.cpp JSONGen.cpp -o monitor -lpcap -pthread

Esto generará el ejecutable:
    
    monitor

### ***Ejecución***

Ejecutar el programa con permisos de administrador:

    sudo ./monitor

El sistema solicitará los siguientes datos:

    Interfaz de red: eth0
    Intervalo monitoreo (ms): 500
    Archivo JSON salida: eventos.json

Durante la ejecución se mostrarán eventos detectados en consola como:

    [ARP] paquete detectado
    [ICMP] paquete detectado
    [TCP] paquete detectado
    [EVENTO] Cambio MAC
    [ANOMALIA] demasiados ICMP

Para finalizar el programa se presiona:

    CTRL + C

Al detenerse, el programa guarda automáticamente el archivo JSON con los eventos registrados.

### ***Enfoque técnico***

El proyecto implementa varios componentes para monitorear actividad de red:

- Lectura de direcciones IP y MAC utilizando getifaddrs() y archivos del sistema (/sys/class/net).

- Captura de paquetes de red con libpcap en modo promiscuo.

- Detección de protocolos ARP, ICMP, TCP y UDP.

- Clasificación de anomalías basada en:

  - cambios de IP

  - cambios de MAC

  - múltiples paquetes ICMP consecutivos

- Generación de reportes en JSON utilizando nlohmann/json.


### ***Ejemplo de JSON generado***

    [
     {
      "event": "arp_packet",
      "source_ip": "unknown",
      "header_bytes": "0 50 56 ec 9e d6 0 c 29 e4 43 6c",
      "timestamp": "2026-03-13T02:07:40Z"
     },
     {
      "event": "anomaly",
      "description": "Demasiados paquetes ICMP detectados",
      "timestamp": "2026-03-13T02:07:48Z"
     },
     {
      "event": "mac_change",
      "old_value": "00:0c:29:e4:43:6c",
      "new_value": "00:11:22:33:44:55",
      "timestamp": "2026-03-13T02:10:11Z"
     }
    ]
