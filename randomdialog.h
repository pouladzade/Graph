#ifndef RANDOMGEN_H
#define RANDOMGEN_H
#include <QWidget>


namespace Ui {
class RandomDialog;
}

class RandomDialog : public QWidget
{
     Q_OBJECT

public:
    explicit RandomDialog(QWidget *parent = 0);
    ~RandomDialog();

private slots:
    void on_vertexPushButton_clicked();

    void on_edgePushButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::RandomDialog *ui;
    QString saveFile(const QString& extention,const QString& text);
    int generateRandomNo(int base);

};

#endif // RANDOMGEN_H
