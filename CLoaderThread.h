#pragma once

#include <QReadWriteLock>
#include <QThread>
#include <QImage>
#include <QUrl>

class CLoaderThread:public QThread
{
	Q_OBJECT

	QImage m_image;
	QReadWriteLock m_mutex;
	QUrl m_url;
public:
	std::atomic<bool> m_done=false;

	CLoaderThread(QUrl m_url):m_url(m_url)
	{
	}

	QImage GetImage()
	{
		QReadLocker lock(&m_mutex);
		return m_image;
	}

	void run() override;
};
