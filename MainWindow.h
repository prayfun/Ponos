#pragma once

#include <QMainWindow>
#include <QSqlDatabase>


namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
	Q_OBJECT

	QSqlDatabase m_db;


	struct s_ShipDescr
	{
		int Id{};
		QString Name;
		QString Code;
	};

	using td_shipsMap=std::map<int/*Id*/,s_ShipDescr>;

	td_shipsMap m_shipsMap;

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void DB_Reopen();
	void DB_ReadShipsList();

	void RefillShipsListFromMap();
	void RefillShipInfo(const int Id);

private slots:

    void on_List_triggered();

    void on_About_triggered();

    void on_Quit_triggered();

private:
	Ui::MainWindow *ui;
};
