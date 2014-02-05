#include <QDebug>
#include <QFile>
#include <QNetworkReply>

#include "yahoo_loader.h"

#include <assert.h>

// TODO: QTemporaryFile

YahooLoader::YahooLoader(QString symbol, Period period, OHLCMemoryProvider* storage) {
	this->symbol = symbol;
	this->period = period;
	this->storage = storage;

	connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
}

void YahooLoader::requestFinished(QNetworkReply* reply) {
	qDebug() << "Request finished (with reply)";
	if (reply->error()) {
		qDebug() << "ERROR: status code " << reply->error();
	} else {
		qDebug() << "Reading incoming data...";
		/*
		file->write(reply->readAll());
		file->flush();
		file->close();
		*/
		csvLoader = new YahooCSVLoader(reply, storage);
		connect(csvLoader, SIGNAL(dataLoaded()), this, SLOT(csvLoaded()));
		csvLoader->load();
	}
}

void YahooLoader::csvLoaded() {
	qDebug() << "CSV loaded.";
	emit dataLoaded();
}

QUrl YahooLoader::buildUrl(QString symbol, QDateTime start, QDateTime end, Period period) {
	QUrl url;
	url.setScheme("https");
	url.setHost("ichart.yahoo.com");
	url.setPath("/table.csv");

	QList<QPair<QString, QString> > query;
	query.push_back(QPair<QString, QString>("s", symbol));

	query.push_back(QPair<QString, QString>("a", QString::number(start.date().month() - 1)));
	query.push_back(QPair<QString, QString>("b", QString::number(start.date().day())));
	query.push_back(QPair<QString, QString>("c", QString::number(start.date().year())));

	query.push_back(QPair<QString, QString>("d", QString::number(end.date().month() - 1)));
	query.push_back(QPair<QString, QString>("e", QString::number(end.date().day())));
	query.push_back(QPair<QString, QString>("f", QString::number(end.date().year())));

	query.push_back(QPair<QString, QString>("g", QString((char) period)));

	// TODO: url.setQueryItems(query);
	QString queryString = "";
	for (QList<QPair<QString, QString> >::iterator i = query.begin(); i != query.end(); i++) {
		queryString += i->first + "=" + i->second;
		if (i + 1 != query.end()) {
			queryString += "&";
		}
	}

	url.setQuery(queryString);

	return url;
}

void YahooLoader::slotReadyRead() {
	qDebug() << "Reading incoming data...";
	// file->write(reply->readAll());
}

void YahooLoader::slotError(QNetworkReply::NetworkError error) {
	// TODO
	qDebug() << "Error: " << error;
}

void YahooLoader::slotSslErrors(QList<QSslError> errors) {
	// TODO
	qDebug() << "SSL errors: " << errors;
}

void YahooLoader::load() {
	// TODO: storage size must coincide with the period...
	QUrl url = buildUrl(symbol, storage->getMinimum(), storage->getMaximum(), period);
	qDebug() << "built URL: " << url;

	reply = manager.get(QNetworkRequest(url));
	qDebug() << "request launched: " << reply;

	// connect(reply, SIGNAL(finished()), this, SLOT(requestFinished()));
	connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
	connect(reply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(slotSslErrors(QList<QSslError>)));

	/*
	file = new QFile("/tmp/qt-downloaded");
	if (!file->open(QFile::Append)) {
		throw "nemuzu psat do souboru";
	}
	*/
}
