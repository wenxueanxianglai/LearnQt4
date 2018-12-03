#include <QSemaphore>
#include <QThread>
#include <QDebug>


static const int SIZE = 5;
static unsigned char g_buff[SIZE] = {0};

static QSemaphore g_sem_free(SIZE);
static QSemaphore g_sem_used(0);

class CMyProductor : public QThread
{
protected:
	void run()
	{
		while( true )
		{
			int value = qrand() % 256;
			g_sem_free.acquire();

			for (int i = 0; i < 5; ++i)
			{
				if (!g_buff[i])
				{
					g_buff[i] = value;

					qDebug() << this->objectName() << "generate: {" << i << ", " << value << "}";

					break;
				}
			}

			g_sem_used.release();
		}
	}
};

class CMyCustomer : public QThread
{
protected:
	void run()
	{
		while ( true )
		{
			g_sem_used.acquire();

			for (int i = 0; i < 5; ++i)
			{
				if (g_buff[i])
				{
					int value = g_buff[i];
					g_buff[i] = 0;

					qDebug() << this->objectName() << "consume: {" << i << ", " << value << "}";
				}
			}

			g_sem_free.release();
		}
	}
};