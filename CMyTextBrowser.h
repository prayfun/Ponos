#pragma once

#include <QTextBrowser>

class CMyTextBrowser : public QTextBrowser
{
	Q_OBJECT

public:
	CMyTextBrowser(QWidget *parent = nullptr)
		:QTextBrowser(parent)
	{
	}

	~CMyTextBrowser()override
	{
	}

	QVariant loadResource(int type, const QUrl &name) override;
};
