#include <Arduino.h>

// Please include ArtnetEther.h to use Artnet on the platform
// which can use both WiFi and Ethernet
// #include <ArtnetEther.h>
// this is also valid for other platforms which can use only Ethernet
#include <Artnet.h>

// Ethernet stuff
const IPAddress ip(192, 168, 0, 12);
uint8_t mac[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB};

ArtnetReceiver artnet;
uint32_t universe1 = 1; // 0 - 15
uint8_t lastData = 0;

void callback(const uint8_t *data, const uint16_t size)
{
  // you can also use pre-defined callbacks
  //     Serial.print("artnet data (universe : ");
  // Serial.print(universe1);
  // Serial.print(", size = ");
  // Serial.print(size);
  // Serial.print(") :");
  // for (size_t i = 0; i < size; ++i) {
  //     Serial.print(data[i]);
  //     Serial.print(",");
  // }
  // Serial.println();
  if (data[0] != lastData)
  {
    lastData = data[0];
    Serial.print("artnet data (universe : ");
    Serial.print(universe1);
    Serial.print(", size = ");
    Serial.print(size);
    switch (data[0])
    {
    case 1:
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
      Serial.println("Set + -");
      break;
    case 2:
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
      Serial.println("Set - +");
      break;

    default:
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      Serial.println("Set - -");
      break;
    }
  }
}

void setup()
{
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);

  Serial.begin(115200);

  Ethernet.begin(mac, ip);
  artnet.begin();
  // artnet.subscribe_net(0);     // optionally you can change
  // artnet.subscribe_subnet(0);  // optionally you can change
  // you can also use pre-defined callbacks
  artnet.subscribe(universe1, callback);
}

void loop()
{
  artnet.parse(); // check if artnet packet has come and execute callback
}