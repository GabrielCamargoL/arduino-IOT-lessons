// Driver para USB-Serial
// https://github.com/Xinyuan-LilyGO/CH9102_Driver/raw/main/CH9102_WIN.EXE

// Site para configuração do Arduino
// https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/

// Link com o repositório dos arquivos
// https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

// 1662470276 - 98CDAC7BB31005
// tecmeter/data/43010337153421317  Pkg {'volt': 394.0, 'cur': 407.0, 'eap': 3972228700000, 'erp': 24800000000, 'mda': 931.0, 'da': 401.0, 'fp': 999.0, 'battery': 2.9, 'signal': 10} 



#include<WiFi.h>
#include "BluetoothSerial.h"
#define LED 2

String uid;
BluetoothSerial SerialBT;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  uid = WiFi.macAddress();
  uid.replace(":","");
  uid[12] = '\0';
  
  Serial.begin(115200);
  Serial.println(uid);
  SerialBT.begin(uid);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  Serial.println("LED ON");
  SerialBT.println("LED ON");
 
  delay(1000);
  digitalWrite(LED, LOW);
  Serial.println("LED OFF");
  SerialBT.println("LED OFF");
  delay(1000);
}

#include<WiFi.h>
#include<EEPROM.h>
#include "BluetoothSerial.h"
#define LED 2

typedef struct {
  int tipo; //1-gms 2-wifi
  int tcoleta;
  int ttrans;
} Config_t;

Config_t config;

String uid;
BluetoothSerial SerialBT;

void initEEPROM(){
  EEPROM.begin(512);
  config.tipo = 2;
  config.tcoleta = 5;
  config.ttrans = 5;
  EEPROM.put(0, config);
  EEPROM.commit();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  uid = WiFi.macAddress();
  uid.replace(":","");
  uid[12] = '\0';
  
  Serial.begin(115200);
  Serial.println(uid);
  SerialBT.begin(uid);
  //initEEPROM();
  EEPROM.begin(512);
  EEPROM.get(0,config);
  Serial.print("Configs salvas: ");
  Serial.print(config.tipo); Serial.print(" ");
  Serial.print(config.tcoleta); Serial.print(" ");
  Serial.println(config.ttrans);
}



void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  Serial.println("LED ON");
  SerialBT.println("LED ON");
 
  delay(1000);
  digitalWrite(LED, LOW);
  Serial.println("LED OFF");
  SerialBT.println("LED OFF");
  delay(1000);
}