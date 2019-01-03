#include "myobject.h"
#include <QDebug>
#include "QThread"

MyObject::MyObject(QObject *parent)
	: QObject(parent)
{

}

MyObject::~MyObject()
{

}

void MyObject::getStarted()
{
	qDebug() << "void MyObject::getStarted() tid = " << QThread::currentThread();
}

void MyObject::getFinished()
{
	qDebug() << "void MyObject::getFinished() tid = " << QThread::currentThread();
}

void MyObject::getTerminated()
{
	qDebug() << "void MyObject::getTerminated() tid = " << QThread::currentThread();
}
