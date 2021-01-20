#include "CLoaderThread.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QAbstractEventDispatcher>

void CLoaderThread::run()
{
	//блок {} обязателен
	{
		QWriteLocker lock(&m_mutex);
		m_image={};
	}

	QNetworkAccessManager http;
	connect(&http, &QNetworkAccessManager::finished,[this](QNetworkReply* reply)
	{
		auto ba=reply->readAll();

		//блок {} обязателен
		{
			QWriteLocker lock(&m_mutex);
			m_image.loadFromData(ba);
		}

		reply->deleteLater();
		requestInterruption();
	});

	http.get(QNetworkRequest(m_url));

	QTimer::singleShot(5000,[this]()
	{
		requestInterruption();
	});

	while(!isInterruptionRequested())
	{
		if(!eventDispatcher()->processEvents(QEventLoop::AllEvents))
		{
			msleep(1);
		}
	}

	m_done=true;
}
