#include "MainWindow.h"
#include <QIcon>
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
    w.setWindowTitle("Энциклопедия кораблей");
    w.setWindowIcon(QIcon("C:\\Users\\dop3f\\Documents\\ShipsBrowser\\Logos\\Icon.png"));
	w.show();
	return a.exec();
}
