#pragma once
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QList>



class MyCustomer : public QThread
{
protected:
	int m_need;		//����Ҫ���ʽ��ܶ�
	volatile int m_current;	//Ŀǰӵ�е��ʽ�����
	QMutex m_mutex;


	void run()
	{
		bool bCondition = false;

		qDebug() << objectName() << "begin to apply money";

		do 
		{
			m_mutex.lock();

			bCondition = (m_current < m_need);

			m_mutex.unlock();

			msleep(1);

		} while (bCondition);


		qDebug() << objectName() << "end(get enough money)";
	}

public:
	MyCustomer(int current, int need) 
	{
		m_current = current;
		m_need = need;
	}

	void addMoney(int m)
	{
		m_mutex.lock();
	
		m_current += m;

		m_mutex.unlock();
	}

	int backMoney()
	{
		int ret = 0;

		m_mutex.lock();

		ret = m_current;

		m_current = 0;

		m_mutex.unlock();

		return ret;
	}

	int current()
	{
		int ret = 0;

		m_mutex.lock();

		ret = m_current;

		m_mutex.unlock();

		return ret;
	}

	int need()
	{
		return m_need;
	}
};

class MyBank : public QThread
{
protected:
	QList<MyCustomer*> m_list;
	int m_total;		//��ʶ��ǰ���п���ʽ�

	void run()
	{
	
		int index = -1;
		qDebug() << objectName() << "begin: " << m_total;

		do 
		{
			//////////////////////////////////////////////////////////////////////////
			//1. �����Ƿ�����������Ĵ��� ���Ի�
			for (int i = 0; i < m_list.count(); ++i)
			{
				if ( m_list[i]->current() == m_list[i]->need() )
				{
					qDebug() << objectName() << "take back money from " << m_list[i]->objectName() << " " << m_list[i]->need();

					m_total += m_list[i]->backMoney();
				}
			}

			qDebug() << objectName() << " current: " << m_total;
			//@end
			//////////////////////////////////////////////////////////////////////////
			
			//////////////////////////////////////////////////////////////////////////
			//2. ���ҵ�ǰ��С�������  ���ҽ���Ҫ���Ǯ������ toGet ���˱�����index
			int toGet = 0x00FFFFFFF;
			index = -1;

			for (int i = 0; i < m_list.count(); ++i)
			{
				if ( m_list[i]->isRunning())
				{
					int temp = m_list[i]->need() - m_list[i]->current();

					if ( toGet > temp)
					{
						index = i;
						toGet = temp;
					}
				}

			}
			//@end
			//////////////////////////////////////////////////////////////////////////


			//////////////////////////////////////////////////////////////////////////
			// 3. ����������˰�~ 1��1��ĸ�
			if (index >= 0)
			{
				if (toGet <= m_total)
				{
					qDebug() << objectName() << " give money to: " << m_list[index]->objectName();

					m_total--;

					m_list[index]->addMoney(1);
				}
				else
				{
					qDebug() << objectName() << " terminate: " << m_list[index]->objectName();

					m_total += m_list[index]->backMoney();

					m_list[index]->terminate();
				}
			}

			sleep(1);

		} while ( index >= 0 );

		qDebug() << objectName() << " end: " << m_total;
	}

public:
	MyBank(int total)
	{
		m_total = total;
	}

	void addCustomer(MyCustomer* pCu)
	{
		m_list.append(pCu);
	}
};

void TestBankAlgorithm()
{
	MyCustomer p(4, 8);
	MyCustomer q(2, 3);
	MyCustomer r(2, 9);

	MyBank bank(2);
	bank.setObjectName("Bank");
	
	p.setObjectName("P");
	q.setObjectName("Q");
	r.setObjectName("R");

	bank.addCustomer(&p);
	bank.addCustomer(&q);
	bank.addCustomer(&r);

	p.start();
	q.start();
	r.start();

	bank.start();


	while(1);
}