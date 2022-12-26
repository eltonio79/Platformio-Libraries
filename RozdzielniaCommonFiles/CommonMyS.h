#ifndef CommonMyS_h
#define CommonMyS_h

/////////////////////////////// ETHERNET CONFIGURATION ///////////////////////////////

#define MY_GATEWAY_MQTT_CLIENT
#define MY_GATEWAY_W5100
#define MY_W5100_SPI_EN 10

//#define USE_STATIC_IP // if not defined it uses DHCP (default)
#ifdef USE_STATIC_IP
#define MY_IP_ADDRESS 192,168,1,100
#define MY_IP_SUBNET_ADDRESS 255,255,255,0
#define MY_IP_GATEWAY_ADDRESS 192,168,1,1
#endif

///////////////////////////////// MQTT CONFIGURATION //////////////////////////////////

// Set client id and version 
#define MY_MQTT_CLIENT_ID MY_HOSTNAME
#define MY_MQTT_CLIENT_VERSION "2.3.2"

#define MY_CONTROLLER_IP_ADDRESS 192, 168, 1, 7 // use controller IP address
#ifndef MY_CONTROLLER_IP_ADDRESS 
#define MY_CONTROLLER_URL_ADDRESS "homeassistant.dom.lan" // use controller URL
#endif
#define MY_PORT 1883

#define MY_MQTT_USER     "_USERNAME_MQTT_"
#define MY_MQTT_PASSWORD "_PASSWORD_MQTT_"

#define MY_ROZDZIELNIA_PREFIX "Rozdzielnia" 
#define MY_HOSTNAME MY_ROZDZIELNIA_PREFIX " " MY_ROZDZIELNIA_NAME
#define MY_MAC_ADDRESS 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, MY_ROZDZIELNIA_ID
#define MY_MQTT_TOPIC_PREFIX MY_ROZDZIELNIA_PREFIX "/"
#define MY_MQTT_PUBLISH_TOPIC_PREFIX MY_MQTT_TOPIC_PREFIX MY_ROZDZIELNIA_NAME "/Out"
#define MY_MQTT_SUBSCRIBE_TOPIC_PREFIX MY_MQTT_TOPIC_PREFIX MY_ROZDZIELNIA_NAME "/In"

/////////////////////////////////// RADIO CONFIGURATION /////////////////////////////////

// Enables and select radio type (if attached)
//#define MY_RADIO_NRF24

// radio on the software SPI bus (ethernet shield conflict..)
//#define MY_SOFTSPI
//#define MY_SOFT_SPI_SCK_PIN A0
//#define MY_SOFT_SPI_MOSI_PIN A1
//#define MY_SOFT_SPI_MISO_PIN A2
//#define MY_RF24_CE_PIN A3
//#define MY_RF24_CS_PIN A4

////////////////////////////// GATEWAY STATUS CONFIGURATION ////////////////////////////

//#define MY_INCLUSION_MODE_FEATURE
//#define MY_INCLUSION_MODE_DURATION 60
//#define MY_INCLUSION_BUTTON_FEATURE
//#define MY_INCLUSION_MODE_BUTTON_PIN 3

#define MY_DEFAULT_LED_BLINK_PERIOD 2000

#define MY_DEFAULT_ERR_LED_PIN 16
#define MY_DEFAULT_RX_LED_PIN 14
#define MY_DEFAULT_TX_LED_PIN 15

#define MY_TRANSPORT_WAIT_READY_MS 2500 // reconnect to controller delay

/////////////////////////// ADDITIONAL TOOLS AND CONFIGURATION /////////////////////////

// Wait times
#define LONG_WAIT 500
#define SHORT_WAIT 50

// Enable debug prints Over the Air (redirect debug prints to given node ID)
// #define MY_DEBUG_OTA (0)
// #define MY_OTA_LOG_RECEIVER_FEATURE
// #define MY_OTA_LOG_SENDER_FEATURE

// Enable debug prints to serial monitor (not work with OTA debug in the same time)
#ifndef MY_DEBUG_OTA
    // #define MY_DEBUG
#endif

// Enable terminal treatment
// #define MY_TERMINAL

#include <MySensors.h>

#endif // CommonMyS_h
