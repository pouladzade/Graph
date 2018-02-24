#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include"string-parser.h"
#include<QFileDialog>
#include<QFile>
#include<QTextStream>
#include<randomdialog.h>
#include<dfs.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionGenerate, SIGNAL(triggered()), this, SLOT(on_generateRandomFile_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sortPushButton_clicked()
{
    Graph graph;
    QString out_text    = "";
    QString vertex_text = ui->vertexTextEdit->toPlainText();
    QString edge_text   = ui->edgesTextEdit->toPlainText();

    auto vertices =  extractNumbers(vertex_text.toStdString()," ");
    auto edges =  extractEdges(edge_text.toStdString(),","," ");

    for(auto vertex : vertices)
        graph.addVertex(Vertex(vertex));

    for(auto edge: edges)
        graph.addEdge(Vertex(edge.first),Vertex(edge.second));

    for(auto vertex_number : vertices)
    {
        auto vertex_edges = graph.getEdges(vertex_number);
        out_text += QString(" V %1) ").arg(QString::number(vertex_number));
        for(auto vx : vertex_edges)
        {
            out_text += QString(" ---> %1 ").arg(QString::number(vx->getIndex()));
        }
        out_text += "\r\n";
    }

    DFS dfs(&graph);
    Index start_index = ui->dfsLineEdit->text().toInt();
    dfs.search(start_index);
    auto visited = dfs.getVisited();


    out_text += QString("\r\n vertices connected to  %1  are :\r\n").arg(ui->dfsLineEdit->text());

    for(auto path : visited)
        out_text += QString(" %1-->%2 ").arg(QString::number(path.first)).arg(QString::number(path.second));

    out_text += " \r\nThe order of visiting nodes is:\r\n";
    for(auto path : visited)
        out_text += QString(" [%1] ").arg(QString::number(path.second));



    ui->OutputTextEdit->setText(out_text);
}

void MainWindow::on_vertexPushButton_clicked()
{
    QString file_name = "";
    QString file_text = openFile("vertex",file_name);
    ui->vertexLineEdit->setText(file_name);
    ui->vertexTextEdit->setText(file_text);
}

void MainWindow::on_edgesPushButton_clicked()
{
    QString file_name = "";
    QString file_text = openFile("edge",file_name);
    ui->edgesLineEdit->setText(file_name);
    ui->edgesTextEdit->setText(file_text);
}

void MainWindow::on_generateRandomFile_clicked()
{
    RandomDialog* dlg = new RandomDialog();
    showWidgets(false);
    dlg->show();
    showWidgets(true);
}

QString MainWindow::openFile(QString extention,QString& file_name)
{
    QString file_text = "";
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    extention = QString("Text (*.%1)").arg(extention);

    file_name = QFileDialog::getOpenFileName(this,
        tr("Open Text"), "", extention);

    if (file_name.isEmpty())
        return "";

    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    while (!in.atEnd()) {
        file_text += in.readLine();
    }
    return file_text;
}

void MainWindow::showWidgets(bool hide)
{
    ui->actionGenerate->setVisible(hide);
    ui->verticalLayoutWidget->setVisible(hide);
    ui->centralWidget->setVisible(hide);
    ui->edgesLineEdit->setVisible(hide);
    ui->edgesPushButton->setVisible(hide);
    ui->edgesTextEdit->setVisible(hide);
    ui->vertexLabel->setVisible(hide);
    ui->edgesLabel->setVisible(hide);
    ui->outputLabel->setVisible(hide);
    ui->mainToolBar->setVisible(hide);
    ui->OutputTextEdit->setVisible(hide);
    ui->sortPushButton->setVisible(hide);
    ui->statusBar->setVisible(hide);
    ui->vertexLineEdit->setVisible(hide);
    ui->vertexPushButton->setVisible(hide);
    ui->vertexTextEdit->setVisible(hide);
    ui->verticalLayoutWidget->setVisible(hide);
}
