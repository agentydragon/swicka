#ifndef DATA_LOADER_H_INCLUDED
#define DATA_LOADER_H_INCLUDED

#include <QObject>

class DataLoader: public QObject {
	Q_OBJECT

	public:
		virtual void load() = 0;
	
	signals:
		void dataLoaded();
};

#endif
