#include "CMyTextBrowser.h"
#include "CLoaderThread.h"
#include <QDebug>

QVariant CMyTextBrowser::loadResource(int type, const QUrl& name)
{
	qDebug()<<"loadResource: "<<name;

	if (type == QTextDocument::ImageResource)
	{
		CLoaderThread trd(name);
		trd.start();

		while(!trd.m_done){}

		trd.wait();

		auto im=trd.GetImage();
		if(!im.isNull())
		{
			return im;
		}
	}

	return QTextBrowser::loadResource(type,name);
}
