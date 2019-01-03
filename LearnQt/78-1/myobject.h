#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>

class MyObject : public QObject
{
	Q_OBJECT

public:
	MyObject(QObject *parent = nullptr);
	~MyObject();

public slots:
	void getStarted();
	void getFinished();
	void getTerminated();
private:
	
};

#endif // MYOBJECT_H
