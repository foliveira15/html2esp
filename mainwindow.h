#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebEngineWidgets>

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

private:
    Ui::MainWindow *ui;
    void atualizaPagina();
    QString html;
    QString head;
    QString body;
    QString footer;
    QWebEngineView *view = new QWebEngineView(this);
};
#endif // MAINWINDOW_H
