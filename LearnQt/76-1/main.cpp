
#include <QtCore/QCoreApplication>
#include <QDebug>
#include "QThread"
#include "QMutex"

QMutex g_Mutex_1;
QMutex g_Mutex_2;

class ThreadA : public QThread
{
protected:
	void run()
	{
		while(true)
		{
			g_Mutex_1.lock();
			g_Mutex_2.lock();

			qDebug() << this->objectName() << " : " << "do working";

			g_Mutex_2.unlock();
			g_Mutex_1.unlock();

			sleep(100);
		}

	}
};

class ThreadB : public QThread
{
protected:
	void run()
	{
		while(true)
		{
			g_Mutex_1.lock();
			g_Mutex_2.lock();

			qDebug() << this->objectName() << " : " << "do working";

			g_Mutex_2.unlock();
			g_Mutex_1.unlock();
			sleep(100);
		}

	}
};

// ËÀËø
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	ThreadA ta;
	ThreadB tb;

	ta.setObjectName("Thread A");
	tb.setObjectName("Thread B");

	ta.start();
	tb.start();

	return a.exec();
}
