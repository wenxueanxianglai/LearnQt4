#include "testthread.h"
#include <QDebug>

TestThread::TestThread(QObject *parent)
	: QThread(parent)
{
	connect(this, SIGNAL(testSignal()), this, SLOT(testSlot()));
}

TestThread::~TestThread()
{

}

void TestThread::testSlot()
{
	qDebug() << "void TestThread::testSlot() tid = " << QThread::currentThread();
}

void TestThread::run()
{
	qDebug() << "TestThread::run() ---- begin tid = " << QThread::currentThread();

	for (int i = 0; i < 10; ++i)
	{
		qDebug() << "TestThread::run() = " << i;

	}

	emit testSignal();

	qDebug() << "TestThread::run() ---- end tid = " << QThread::currentThread();
}
