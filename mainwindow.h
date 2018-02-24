#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_sortPushButton_clicked();

    void on_vertexPushButton_clicked();

    void on_edgesPushButton_clicked();

    void on_generateRandomFile_clicked();

private:
    Ui::MainWindow *ui;
    QString openFile(QString extention,QString& file_name);
    void showWidgets(bool hide);
};

#endif // MAINWINDOW_H
