#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtSql>
#include <QPainter>
#include <QMessageBox>
#include <optional>
#include "About.h"
#include "ui_About.h"
#include "Quit.h"
#include "ui_Quit.h"


namespace DB
{
	const QString MainDatabaseName="ships.db3";

	namespace Ships
	{
		const QString tablename="Ships";

		namespace fields
		{
			const QString Id  ="_id";
			const QString Name="Name";
			const QString Code="Code";
		}

		const QString urlprefix__=tablename+"/"+fields::Id+"/";//N
		inline QString MakeUrlFor_Id(const int Id)
		{
			return DB::Ships::urlprefix__+QString::number(Id);
		}

		inline std::optional<int> GetIdFrom_Url(const QUrl& url)
		{
			const auto prefix=DB::Ships::urlprefix__;
			auto s=url.toString();

			if(s.left(prefix.size())!=prefix)return {};

			bool ok=false;
			auto Id=s.mid(prefix.size()).toInt(&ok);
			if(!ok)return {};

			return Id;
		}
	};
}

MainWindow::~MainWindow()
{
	delete ui;
}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	m_db=QSqlDatabase::addDatabase("QSQLITE");

//	connect(ui->DB_Reopen             ,&QToolButton::clicked,[this]{DB_Reopen()             ;});
//	connect(ui->DB_ReadShipsList      ,&QToolButton::clicked,[this]{DB_ReadShipsList()      ;});
//	connect(ui->RefillShipsListFromMap,&QToolButton::clicked,[this]{RefillShipsListFromMap();});

	connect(ui->ShipsList,&QTextBrowser::anchorClicked,[this](const QUrl& url)
	{
		qDebug()<<"url clicked: "<<url;

		if(auto Id=DB::Ships::GetIdFrom_Url(url))
		{
			RefillShipInfo(*Id);
		}
		else
		{
			qDebug()<<"can't recognize url";
		}
	});

	DB_Reopen();
	DB_ReadShipsList();
}

void MainWindow::DB_Reopen()
{
	m_db.close();

	m_db.setDatabaseName(QDir(qApp->applicationDirPath()).filePath(DB::MainDatabaseName));
	if(m_db.open())
	{
		qDebug()<<"opened!";
	}
	else
	{
		qDebug()<<"can't open";
	}
}

void MainWindow::DB_ReadShipsList()
{
	m_shipsMap.clear();
	[&]
	{
		if(!m_db.isOpen())
		{
			qDebug()<<"is not opened";
			return;
		}

		using namespace DB::Ships;

		auto q=m_db.exec("select * from "+tablename);
		if(q.lastError().type()!=QSqlError::ErrorType::NoError)
		{
			qDebug()<<"exec error";
			return;
		}

		while(q.next())
		{
			s_ShipDescr item;
			item.Id  =q.value(fields::Id).toInt();
			item.Name=q.value(fields::Name).toString();
			item.Code=q.value(fields::Code).toString();

			m_shipsMap.emplace(item.Id,item);
		}
	}();

	RefillShipsListFromMap();
}

void MainWindow::RefillShipsListFromMap()
{
	ui->ShipsList->clear();

	QString links;

	links+=R"(<table>)";// style="height:300px" border="2"

	for(const auto& [Id,Descr]:m_shipsMap)
	{
		links+="<tr>";
		{
			links+="<td>";
			{
				links+=R"(<a href=")"+DB::Ships::MakeUrlFor_Id(Id)+R"(">)"+Descr.Name+R"(</a>)";
			}
			links+="</td>";
		}
		links+="</tr>";
	}

	links+="</table>";

	ui->ShipsList->setHtml(links);
}

void MainWindow::RefillShipInfo(const int Id)
{
	ui->ShipsList->clear();

	QString content="Information was not found";

	auto it=m_shipsMap.find(Id);
	if(it!=m_shipsMap.end())
	{
		content=it->second.Code;
	}

	ui->ShipsList->setHtml(content);
}

void MainWindow::on_List_triggered()
{
    DB_ReadShipsList();
}

void MainWindow::on_About_triggered()
{
    About *_about = new About;
    _about->setWindowIcon(QIcon("C:\\Users\\dop3f\\Documents\\ShipsBrowser\\Logos\\Icon.png"));
    _about->setWindowTitle("О программе");
    _about->show();
}

void MainWindow::on_Quit_triggered()
{
    Quit *_quit = new Quit;
    _quit->setWindowIcon(QIcon("C:\\Users\\dop3f\\Documents\\ShipsBrowser\\Logos\\Icon.png"));
    _quit->setWindowTitle("Завершение программы");
    _quit->show();
}
