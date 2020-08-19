//LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // posiciona o endereço lcd
//DHT

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

int DHTPIN   =         2 ;        // Pin que esta conectado o DHT sensor.
int temperatura = 0;
int umidade = 0;

#define DHTTYPE           DHT11    


DHT_Unified dht(DHTPIN, DHTTYPE);

#define rele_lampada  7
#define rele_cooler  8

void setup() {
  pinMode (rele_lampada, OUTPUT);
  pinMode (rele_cooler, OUTPUT);
  pinMode (2, INPUT);
  Serial.begin(9600); 
  delay (1000);
  // Inicializando o sensor
  dht.begin();
  Serial.println("DHTxx Unified Sensor Example");
 
 // Captando as  informaçoes de temperatura do sensor
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
 
 // Captando as  informações de umidade do sensor
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
 
  //inicialização LCD
  lcd.begin();
  lcd.setCursor(3, 0);
  lcd.print("COMPOSTEIRA");
  lcd.setCursor(3, 1);
  lcd.print("ELETRONICA");
  delay(5000);
  lcd.clear();
 
}

void loop() {

//Exibindo valores de temperatura
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    temperatura = event.temperature;

lcd.setCursor(0,0);
lcd.print("Temp : ");
lcd.print(" ");
lcd.setCursor(7,0);
lcd.print(event.temperature, 1);
lcd.setCursor(12,0);
lcd.print("C");
  }
 // Exibindo valores de umidade
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    umidade = event.relative_humidity;

lcd.setCursor(0,1);
lcd.print("Umid : ");
lcd.print(" ");
lcd.setCursor(7,1);
lcd.print(event.relative_humidity);
lcd.setCursor(12,1);
lcd.print("%");
  }
Serial.print(temperatura);
Serial.print(" ");
Serial.println(umidade);

//CONTROLE
  if (temperatura <= 23) {
  digitalWrite(rele_lampada, LOW);
    
  }
  if(temperatura >= 25){
   digitalWrite(rele_lampada, HIGH);
  
  } 
  if (umidade >= 75) {
    digitalWrite(rele_cooler, LOW);
    
  }
  if(umidade <= 70){
    digitalWrite(rele_cooler, HIGH);
   
  }
 
}
