
#include <QtCore/QCoreApplication>
#include "testthread.h"
#include "myobject.h"
#include "QDebug"
#include "QThread"


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	qDebug() << "main() tid = " << QThread::currentThread();

	TestThread t;
	MyObject m;

	QObject::connect(&t, SIGNAL(started()), &m, SLOT(getStarted()));
	QObject::connect(&t, SIGNAL(finished()), &m, SLOT(getFinished()));
	QObject::connect(&t, SIGNAL(terminated()), &m, SLOT(getTerminated()));
	t.start();

	return a.exec();
}
