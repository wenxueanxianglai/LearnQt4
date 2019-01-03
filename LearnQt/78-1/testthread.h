#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QThread>

class TestThread : public QThread
{
	Q_OBJECT

public:
	TestThread(QObject *parent = nullptr);
	~TestThread();

signals:
	void testSignal();

public slots:
	void testSlot();

protected:
	void run();
private:
	
};

#endif // TESTTHREAD_H
