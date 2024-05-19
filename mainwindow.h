#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QStackedWidget>
#include <QFrame>
#include <QVBoxLayout>
#include "AudioHandler.h"
#include "Settings.h"
#include "GameSelectorWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
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
    void resetUI();

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
    QGraphicsProxyWidget *gameSelectorProxy;

    AudioHandler* audioHandler;
    Settings* settings;
    bool closing;

    GameSelectorWidget* gameSelectorWidget;

    void setupUI();
    void applyCommonStyle(QPushButton* button);
    void updateButtonPosition();
    void handleExit();
    void connectButtonClickedSignal(QPushButton* button, void (MainWindow::*member)());
    void hideButtons();
    void showButtons();
    void changeBackgroundImage(const QString& imagePath);
};

#endif // MAINWINDOW_H
