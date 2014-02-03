#ifndef YAHOO_LOADER_H_INCLUDED
#define YAHOO_LOADER_H_INCLUDED

#include <QFile>
#include <QString>
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>

#include "ohlc_memory_provider.h"

class YahooLoader: public QObject {
	Q_OBJECT

	public:
		enum Period { DAY = 'd', WEEK = 'w', MONTH = 'm' };
	private:
		QUrl buildUrl(QString symbol, QDateTime start, QDateTime end, Period period);

		QString symbol;
		Period period;
		OHLCMemoryProvider* storage;

		QNetworkAccessManager manager;
	public:
		YahooLoader(QString symbol, Period period, OHLCMemoryProvider* storage);
		void load();
	
	private:
		QNetworkReply* reply;
		// QFile* file;

	public slots:
		void requestFinished(QNetworkReply* reply);
		void slotReadyRead();
		void slotError(QNetworkReply::NetworkError error);
		void slotSslErrors(QList<QSslError> errors);
		// void readData(const QHttpResponseHeader&);
		// void requestFinished(int id, bool error);
	
	signals:
		void dataLoaded();
};

#endif
