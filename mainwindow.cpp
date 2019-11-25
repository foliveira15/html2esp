#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWebEngineWidgets>
#include <QSize>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view->setMinimumSize(500,500);
   atualizaPagina();
   atualizaCode();
   ui->centro->addWidget(view);

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
    atualizaCode();
}

void MainWindow::atualizaCode()
{
    head = "const char INDEX_HEAD[] PROGMEM = R""=====(\n" + ui->headCode->toPlainText() + ")====="";\n\n";
    body = "const char INDEX_BODY[] PROGMEM = R""=====(\n" + ui->bodyCode->toPlainText() + ")====="";\n\n";
    footer = "const char INDEX_FOOTER[] PROGMEM = R""=====(\n" + ui->footerCode->toPlainText() + ")====="";";
    ui->espCode->setPlainText(head);
    ui->espCode->appendPlainText(body);
    ui->espCode->appendPlainText(footer);
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
