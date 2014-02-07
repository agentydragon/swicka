#ifndef YAHOO_LOADER_H_INCLUDED
#define YAHOO_LOADER_H_INCLUDED

#include <QFile>
#include <QString>
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>

#include "data_loader.h"
#include "ohlc_memory_provider.h"
#include "yahoo_csv_loader.h"

class YahooLoader: public DataLoader {
	Q_OBJECT

	public:
		enum Period { DAY = 'd', WEEK = 'w', MONTH = 'm' };
	private:
		QUrl buildUrl(QString symbol, QDateTime start, QDateTime end, Period period);

		QString symbol;
		Period period;
		OHLCMemoryProvider* storage;

		QNetworkAccessManager* manager;
		YahooCSVLoader* csvLoader;
	public:
		YahooLoader(QString symbol, Period period, OHLCMemoryProvider* storage);
		virtual void load();

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
		//
	private slots:
		void csvLoaded();
	
	signals:
		void dataLoaded();
};

#endif
