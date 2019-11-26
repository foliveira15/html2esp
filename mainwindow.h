#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebEngineWidgets>
#include "about.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_headCode_textChanged();

    void on_bodyCode_textChanged();

    void on_footerCode_textChanged();

    void on_actionAbrir_triggered();

    void on_actionNovo_triggered();

    void on_actionSalvar_Como_triggered();

    void on_actionSalvar_triggered();

    void on_actionSair_triggered();

    void on_actionExportar_triggered();

    void on_actionSobre_triggered();

private:
    Ui::MainWindow *ui;
    void atualizaPagina();
    void atualizaCode();
    void closeEvent(QCloseEvent *event);
    QString html;
    QString head;
    QString body;
    QString footer;
    QWebEngineView *view = new QWebEngineView(this);
    QString local_arquivo;
    boolean salvo;
    about *About;
};
#endif // MAINWINDOW_H
