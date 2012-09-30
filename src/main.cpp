#include <QDebug>
#include <QFile>
#include <getopt.h> /* getopt_long */

#include "Station.h"
#include "ConfigParse.h"
#include "MosqConnect.h"
#include "metar.h"

void print_usage()
{
    qDebug("Usage");
    qDebug(" -c / --config [file]");
    qDebug("   What config file to use");
    exit(0);
}


int main(int argc, char *argv[])
{
    qDebug() << "FunTechHouse METAR 2 MQTT";

    int verbose = 0;
    QFile configFile;

    //A letter with : after means it would like a arg
    const char* short_options = "c:htv";
    const struct option long_options[] = {
        { "help",    0, NULL, 'h'},
        { "verbose", 0, NULL, 'v'},
        { "config",  1, NULL, 'c'},
        { "test",    0, NULL, 't'},
        { NULL,      0, NULL, 0}
    };

    int next_option;

    do
    {
        next_option = getopt_long(argc, argv, short_options, long_options, NULL);
        //printf("next_option %x, %c (%d)\n", next_option, next_option, next_option);

        switch(next_option)
        {
            case -1 :
                {
                    break;
                }
            case 'h':
                {
                    print_usage();
                    break;
                }
            case 'v':
                {
                    verbose++;
                    break;
                }
            case 'c':
                {
                    configFile.setFileName( QString(optarg) );
                    break;
                }
            case 't':
                {
                    //test the config file so it is ok in some way...
                    break;
                }
            default:
                {
                    printf("Error\n");
                    abort();
                    break;
                }
        }
    }while(next_option != -1);


    if(verbose != 0)
    {
        qDebug() << "Verbose level" << verbose;
        //enable info prints in some way...
    }

    if(!configFile.exists())
    {
        qDebug() << "Error Can't find config file" << configFile.fileName();
        exit(1);
    }

    ConfigParse config(configFile.fileName());
    QList<Station> *list;
    list = new QList<Station>;

    if(!config.parse(list))
    {
        qDebug() << "Error Parse config failed";
        exit(1);
    }

    if(list->size() == 0)
    {
        qDebug() << "Error Kind off empty config" << configFile.fileName();
        exit(1);
    }

    if(verbose > 0)
    {
        qDebug() << "";
        qDebug() << "Configfile contains stations:" << list->size();

        for(int i=0; i<list->size(); i++)
        {
            Station station = list->at(i);
            station.print();
        }
        qDebug() << "";
    }

	class MosqConnect *mqtt;
	int rc;

	mosqpp::lib_init();

	mqtt = new MosqConnect(
           config.getAppName().toAscii(), 
           config.getMosqServer().toAscii(), 
            1883,
            list
            );

	while(1)
    {
        rc = mqtt->loop();
		if(rc)
        {
            qDebug() << "reconnect" << rc;
			mqtt->reconnect();
		}

        for(int i=0; i<list->size(); i++)
        {
            Station station = list->at(i);
            if(verbose > 0)
            {
                qDebug() << station.getName();
            }
            QString metarData = "";
            /// @todo Impl curl get data from server 
            //QString metarData = ...getMetarDataFromServer(station.getName();
            if(metarData.size() > 0)
            {
                METAR metar;
                metar.init();
                if(!metar.parse(metarData))
                {
                    /// @todo Fill pub string will data from the parser
                    //QString mess("temperature=%1 dewpoint=%2").arg(metar.getTemperature()).arg(metar.getDewpoint());
                    //mqtt->publishData( station.getMosqTopic(), mess);
                }
            }
        }

        //sleep 20min
        sleep(1);

	}

	mosqpp::lib_cleanup();

}
