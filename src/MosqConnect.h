#ifndef  __MOSQCONNECT_H
#define  __MOSQCONNECT_H

#include <mosquittopp.h>
#include "Station.h"

class MosqConnect : public mosqpp::mosquittopp
{
    private:
        QList<Station> *list;

	public:
		MosqConnect(const char *id, const char *host, int port, QList<Station> *list);
		~MosqConnect();

		void on_connect(int rc);
		void on_message(const struct mosquitto_message *message);
		void on_subscribe(int mid, int qos_count, const int *granted_qos);

        void publishData(QString topic, QString mess);

};

#endif  // __MOSQCONNECT_H
