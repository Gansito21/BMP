#include <sd_defines.h>
#include <sd_diskio.h>
#include <SD.h>

#define led 32 //prenderemos un led cunado se almacene u valor

//Lecturas desde el sensor barometrico
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;
File readings; //Esto es para la memoria

char payload[50]; //Iniciamos con 50 caracteres para 
//escribirlos en la SD

//Iniciamos la comunicacion serial
void setup() {
  Serial.begin(115200);
  bmp.begin(0x76); //La direccion es 0x76
  SD.begin(); //Inicializamos SD

  pinMode(led,OUTPUT);
}

void loop() {
  //Serial.print(bmp.readPressure());
  //utilizaremos la funcion sprintf()
  //sprintf(payload,"Temperatura:%8.2f,Presion:%8.2f",bmp.readTemperature(),bmp.readPressure());
  //Escribimos las lecturas en payload
  sprintf(payload,"%.2f,%.2f",bmp.readTemperature(),bmp.readPressure());
  Serial.println(payload);
  
  //Abrimos archivo y escribimos
  digitalWrite(led,HIGH);
  readings = SD.open("/lecturas.csv",FILE_APPEND);
  readings.println(payload);
  readings.close();
  digitalWrite(led,LOW);
  
  delay(500);
  

}