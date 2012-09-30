#include <cstdio>
#include <cstring>

#include <QString>
#include <QDebug>
#include <QRegExp>
#include <QDateTime>
#include <QUrl>

#include <mosquittopp.h>

#include "MosqConnect.h"
//#include "QuickSurf.h"
#include "Station.h"
//#include "RoomTemperatureDataParser.h"


MosqConnect::MosqConnect(const char *id, const char *host, int port, QList<Station> *list) : mosquittopp(id)
{
    this->list = list;
    int keepalive = 60;

    // Connect immediately. 
    connect(host, port, keepalive);
};

void MosqConnect::on_connect(int rc)
{
    printf("Connected with code %d.\n", rc);
    if(rc == 0){
        // Only attempt to subscribe on a successful connect. 

        for(int i=0; i<list->size(); i++)
        {
            Station station = list->at(i);
            qDebug() << "subscribe" << station.getMosqTopic();
            subscribe(NULL, station.getMosqTopic().toAscii());
        }
    }
}

void MosqConnect::on_message(const struct mosquitto_message *message)
{
    /*
       struct mosquitto_message{
       int mid;
       char *topic;
       void *payload;
       int payloadlen;
       int qos;
       bool retain;
       };
       */

    //Move from "void* with payloadlen" to a QString.
    char* messData = (char*)malloc(sizeof(char)*(message->payloadlen+1));
    memcpy(messData, message->payload, message->payloadlen);
    messData[message->payloadlen] = '\0';

    //printf("Message %s - %s.\n", message->topic, messData);

    QString mess = QString(messData);
    free(messData);

    QString topic = QString(message->topic);

    qDebug() << "\nNew message:" << (QDateTime::currentDateTime()).toString("hh:mm:ss") << topic << mess;

}

void MosqConnect::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
    printf("Subscription succeeded. mid=%d qos=%d granter_qos=%d\n", mid, qos_count, *granted_qos);
}


void MosqConnect::publishData(QString topic, QString mess)
{
    qDebug() << topic << mess;
    publish(NULL, topic.toAscii(), mess.size(), mess.toAscii());
    /*
    if(!strcmp(message->topic, "temperature/celsius")){
        memset(buf, 0, 51*sizeof(char));
        // Copy N-1 bytes to ensure always 0 terminated. 
        memcpy(buf, message->payload, 50*sizeof(char));
        temp_celsius = atof(buf);
        temp_farenheit = temp_celsius*9.0/5.0 + 32.0;
        snprintf(buf, 50, "%f", temp_farenheit);
        publish(NULL, "temperature/farenheit", strlen(buf), buf);
    }
*/
}



