#include "randomdialog.h"
#include "ui_randomdialog.h"
#include<QFileDialog>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<stdlib.h>
#include<set>

RandomDialog::RandomDialog(QWidget *parent):
    QWidget(parent)
{
     ui = new Ui::RandomDialog;
     ui->setupUi(this);
}

RandomDialog::~RandomDialog()
{
    delete ui;
}

void RandomDialog::on_vertexPushButton_clicked()
{
    int count = ui->vertexCountLineEdit->text().toInt();

    QString text = "";
    for(int i=0 ; i<count ; i++)
    {
        text += QString("%1 ").arg(QString::number(i));
    }

    QString file_name = saveFile("vertex",text);

    if(file_name.isEmpty())
        return;

    ui->vertexLineEdit->setText(file_name);
    ui->textBrowser->setText(text);
}

void RandomDialog::on_edgePushButton_clicked()
{
    int count = ui->edgeCountLineEdit->text().toInt();

    QString text = "";

    // using set to prevent duplicate edges!
    std::set<std::pair<int,int>> edges_set;
    for(int i=0 ; i<count ; i++)
    {
        auto edge = std::make_pair(generateRandomNo(count),generateRandomNo(count));
        edges_set.insert(edge);
    }

    for(auto edge : edges_set)
    {
        text += QString("%1,%2 ").arg(QString::number(edge.first),QString::number(edge.second));
    }

    QString file_name = saveFile("edge",text);
    if(file_name.isEmpty())
        return;

    ui->edgeLineEdit->setText(file_name);
    ui->textBrowser->setText(text);
}

void RandomDialog::on_buttonBox_accepted()
{
    close();
}

void RandomDialog::on_buttonBox_rejected()
{
    close();
}

QString RandomDialog::saveFile(const QString& ext,const QString& text )
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QString extention = QString("Text (*.%1)").arg(ext);

    QString file_name = QFileDialog::getSaveFileName(this,
        tr("Save Text"), "", extention);

    if (file_name.isEmpty())
        return file_name;

    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::information(this, tr("Can't open file!"),file.errorString(),QMessageBox::Ok);
        return file_name;
    }
    QTextStream out_stream(&file);

    out_stream << text;

    return file_name;
}

int RandomDialog::generateRandomNo(int base)
{
    return rand()%base;
}
