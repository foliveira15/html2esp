#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWebEngineWidgets>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    local_arquivo = "";
    salvo = true;
   view->setMinimumSize(500,500);
   atualizaPagina();
   atualizaCode();
   ui->centro->addWidget(view);
   statusBar()->showMessage(tr("Pronto!"));

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

    QString codigoFinal = head + body + footer;

    ui->espCode->setPlainText(codigoFinal.replace(R"(")",R"(\")"));


}


void MainWindow::on_headCode_textChanged()
{
    atualizaPagina();
    salvo = false;
}

void MainWindow::on_bodyCode_textChanged()
{
    atualizaPagina();
    salvo = false;
}

void MainWindow::on_footerCode_textChanged()
{
    atualizaPagina();
    salvo = false;
}

void MainWindow::on_actionAbrir_triggered()
{
    QString filtro = "Arquivos HTML (*.htm *.html)";
    QString nome_arquivo = QFileDialog::getOpenFileName(this,"Abrir Arquivo",QDir::homePath(),filtro);
    QFile arquivo(nome_arquivo);
    local_arquivo = nome_arquivo;
    if(!arquivo.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"","Arquivo não pode ser aberto");
        return;
    }
    QTextStream entrada(&arquivo);
    QString texto = entrada.readAll();
    ui->headCode->setPlainText(texto.split("<body").first().trimmed());
    ui->bodyCode->setPlainText(texto.split("</head>").last().split("</html>").first().trimmed());
    ui->footerCode->setPlainText(texto.split("</body>").last().trimmed());
    arquivo.close();
    salvo = true;
}

void MainWindow::on_actionNovo_triggered()
{
    local_arquivo = "";
    ui->headCode->clear();
    ui->bodyCode->clear();
    ui->footerCode->clear();
    ui->headCode->setFocus();
    salvo = true;
}

void MainWindow::on_actionSalvar_Como_triggered()
{
    QString nome_arquivo = QFileDialog::getSaveFileName(this,"Salvar Como",QDir::homePath(),"Arquivo HTML (*.html)");
    local_arquivo = nome_arquivo + ".html";
    QFile arquivo(nome_arquivo);
    if(!arquivo.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"","Arquivo não pode ser salvo");
        return;
    }
    QTextStream saida(&arquivo);
    QString texto = ui->headCode->toPlainText() + ui->bodyCode->toPlainText() + ui->footerCode->toPlainText();
    saida << texto;
    arquivo.flush();
    arquivo.close();
    salvo = true;

}

void MainWindow::on_actionSalvar_triggered()
{
    if (local_arquivo == ""){
        QString nome_arquivo = QFileDialog::getSaveFileName(this,"Salvar Como",QDir::homePath(),"Arquivo HTML (*.html)");
        local_arquivo = nome_arquivo + ".html";
    }
    QFile arquivo(local_arquivo);
    if(!arquivo.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"","Arquivo não pode ser salvo");
        return;
    }
    QTextStream saida(&arquivo);
    QString texto = ui->headCode->toPlainText() + ui->bodyCode->toPlainText() + ui->footerCode->toPlainText();
    saida << texto;
    arquivo.flush();
    arquivo.close();
    salvo = true;
}

void MainWindow::on_actionSair_triggered()
{
    close();
}

void MainWindow::on_actionExportar_triggered()
{
    QString nome_arquivo = QFileDialog::getSaveFileName(this,"Exportar",QDir::homePath(),"Arquivo Header C (*.h)") + ".h";

    QFile arquivo(nome_arquivo);
    if(!arquivo.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"","Arquivo não pode ser exportado");
        return;
    }
    QTextStream saida(&arquivo);
    QString texto = ui->espCode->toPlainText();
    saida << texto;
    arquivo.flush();
    arquivo.close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (salvo) {
        event->accept();
    } else {

        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this,"Deseja sair?","Arquivo não salvo! Deseja gravar antes de sair?",
                                         QMessageBox::Yes|QMessageBox::No);
        if(resposta == QMessageBox::Yes){
            on_actionSalvar_triggered();
        }
        event->accept();
    }
}


void MainWindow::on_actionSobre_triggered()
{
    About = new about(this);
    About->show();
}
