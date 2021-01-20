#ifndef QUIT_H
#define QUIT_H

#include <QMainWindow>

namespace Ui {
class Quit;
}

class Quit : public QMainWindow
{
    Q_OBJECT

public:
    explicit Quit(QWidget *parent = nullptr);
    ~Quit();

private slots:
    void on_Yes_clicked();

    void on_No_clicked();

private:
    Ui::Quit *ui;
};

#endif // QUIT_H
