#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "Credentials.h"
#include "mqtt/MQTTConnector.h"
#include <PubSubClient.h>

#include <ArduinoJson.hpp>
#include <ArduinoJson.h>

void DeserializeObject(String payload){    
    //Procesamiento de la trama JSON.
    MQTTPublish(TOPICJSONSTATUS, "Processing JSON frame...");     
    StaticJsonDocument<300> doc;
    deserializeJson(doc, payload);

    //Configurar día de la semana como texto.    
    String dateTime = doc["datetime"];       
    int dayOfTheWeek = doc["day_of_week"];
    String year = "2021 ,";      
    String meses[12] = {"de Enero de ", " de Febrero de ", " de Marzo de ", " de Abril de "," de Mayo de "," de Junio de "," de Julio de "," de Agosto de ", " de Septiembre de "," de Octubre de ", " de Noviembre de "," de Diciembre de "};
    String dias[7] = {"Lunes, ", "Martes ", "Miércoles, ", "Jueves, ","Viernes, ","Sábado, ","Domingo ,"};
    char *formatoFecha = "";  
    String diaTexto;
    String mes;
    diaTexto = dias[dayOfTheWeek - 1];        
    strcat(formatoFecha,diaTexto.c_str());
    mes = mes + dateTime[5];
    mes = mes + dateTime[6];           
    
    char dia[2];
    dia[0] = dateTime[8]; //dia        
    dia[1] = dateTime[9];   

    char hora[5];
    hora[0] = dateTime[11]; //hora        
    hora[1] = dateTime[12]; 
    hora[2] = ':';
    hora[2] = dateTime[13];         
    hora[3] = dateTime[14];         
        
    strcat(formatoFecha,dia);        
    strcat(formatoFecha, (meses[mes.toInt()-1] + year).c_str());    
    strcat(formatoFecha,hora);        

    MQTTPublish(TOPICOUTPUT, formatoFecha);                                                                                                                                                                  
}