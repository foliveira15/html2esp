#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWebEngineWidgets>
#include <QSize>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view->setMinimumSize(800,500);
   atualizaPagina();
   ui->geral->addWidget(view);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::atualizaPagina()
{
    html = ui->headCode->toPlainText() + ui->bodyCode->toPlainText() + ui->footerCode->toPlainText();
    view->setHtml(html);
    view->show();

}


void MainWindow::on_headCode_textChanged()
{
    atualizaPagina();
}

void MainWindow::on_bodyCode_textChanged()
{
    atualizaPagina();
}

void MainWindow::on_footerCode_textChanged()
{
    atualizaPagina();
}
