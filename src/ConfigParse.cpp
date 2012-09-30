#include <QDebug>
#include <QString>
#include <QList>
#include <QFile>
#include <QtXml>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

#include "ConfigParse.h"

#include "Station.h"

ConfigParse::ConfigParse(QString configfile)
{
    this->configfile = configfile;
    mqttServer = "";
    mqttAppName = "";
}

QString ConfigParse::getMosqServer()
{
    return mqttServer;
}

QString ConfigParse::getAppName()
{
    return mqttAppName;
}

bool ConfigParse::parse(QList<Station> *list)
{

    /*
       for(int i=1; i<6; i++)
       {
       QString name("Station");
       name.append(QString("%1").arg(i));
       qDebug() << name;
       list->append(Station(name,  "b", "c", "d", "e"));
       }
       */

    QDomDocument doc("configfile");
    QFile file(configfile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error can't open file";
        return false;
    }
    if (!doc.setContent(&file))
    {
        file.close();
        qDebug() << "Error can't parse file";
        return false;
    }
    file.close();

    QDomElement docElem = doc.documentElement();

    for(QDomNode n = docElem.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            if(e.tagName() == "mqtt_server")
            {
                mqttServer = e.text().trimmed();
            }
            if(e.tagName() == "mqtt_appname")
            {
                mqttAppName = e.text().trimmed();
            }

            if(e.tagName() == "station")
            {
                Station station;
                //qDebug() << qPrintable(e.tagName()); // the node really is an element.
                if(e.hasAttribute("name"))
                {
                    //qDebug() << qPrintable(e.tagName()) << qPrintable(e.attribute("name"));
                    station.setName( e.attribute("name") );
                }

                {
                    QDomNodeList tagId = e.elementsByTagName("topic");
                    for(int i=0; i<tagId.count(); i++)
                    {
                        QDomNode tag = tagId.at(i);
                        QDomElement tagE = tag.toElement();
                        //qDebug() << qPrintable(tagE.tagName()) << tagE.text();
                        station.setMosqTopic( tagE.text() );
                    }
                }

                if(station.isOK())
                {
                    list->append(station);
                }
            }
        }
        //qDebug() << "";
    }


    if(mqttServer.size() == 0)
    {
        qDebug() << "Error missing config mqtt_server";
        return false;
    }
    if(mqttAppName.size() == 0)
    {
        qDebug() << "Error missing config mqtt_appname";
        return false;
    }

    return true;
}
