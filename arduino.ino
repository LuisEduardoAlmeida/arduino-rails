#include <SPI.h>
#include <Ethernet.h>

//Configurações do Ethernet Shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 172,19,5, 200 }; // ip que o arduino assumirá
byte gateway[] = { 172,19,1, 250 };  // ip do roteador
byte subnet[] = { 255, 255, 0, 0 };
const int canalAnalogico=0;
int sensor;

int serverPort = 80;
int led_port = 13;

EthernetServer server(serverPort);

String readString;

void setup() {
  Ethernet.begin(mac, ip, gateway, subnet);
  Serial.begin(9600);
  server.begin();
  Serial.print("Server online.");

  pinMode(led_port, OUTPUT);
}

void loop() {
  EthernetClient client = server.available();
  if (client) {

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '1') {
          digitalWrite(led_port, HIGH);
          Serial.println("Led status: 1 (ON)");
          client.println("Led status: 1 (ON)"); //aqui envia do arduino para o android
        }
        if (c == '0') {
          digitalWrite(led_port, LOW);
          Serial.println("Led status: 0 (OFF)");
          client.println("Led status: 0 (OFF)"); //aqui envia do arduino para o android
        }        
        if (!client.connected()) {
          client.stop();
        }  
      }
    }
    delay(1);
    client.stop();
  }
}
require 'socket'
s = Socket.new Socket::AF_INET, Socket::SOCK_STREAM
s.connect Socket.pack_sockaddr_in(80, '172.19.5.200')
client = s.write 'C'
