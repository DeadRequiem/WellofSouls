#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "AudioHandler.h"
#include "Settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onButton1Clicked();
    void onButton2Clicked();
    void onButton3Clicked();
    void onButton4Clicked();
    void onButton5Clicked();
    void onButton6Clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem *backgroundItem;
    QGraphicsProxyWidget *buttonProxy1;
    QGraphicsProxyWidget *buttonProxy2;
    QGraphicsProxyWidget *buttonProxy3;
    QGraphicsProxyWidget *buttonProxy4;
    QGraphicsProxyWidget *buttonProxy5;
    QGraphicsProxyWidget *buttonProxy6;

    AudioHandler* audioHandler;
    Settings* settings;
    bool closing; // Add this flag

    void setupUI();
    void setupButton(QPushButton*& button, const QString& text);
    void applyCommonStyle(QPushButton* button);
    void connectButtonClickedSignal(QPushButton* button, void (MainWindow::*slot)());
    void updateButtonPosition();
    void handleExit(); // Add this line
};

#endif // MAINWINDOW_H
