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
#include "GameSelectorWidget.h"  // Include the new widget
#include "ServerSelect.h"  // Include the ServerSelect widget

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
    void onButton2Clicked();  // Slot for Button 2
    void onButton3Clicked();
    void onButton4Clicked();
    void onButton5Clicked();
    void onButton6Clicked();
    void resetUI();  // Slot to reset the UI
    void showServerSelect();  // Slot to show ServerSelect
    void startSinglePlayerGame();  // Slot to start single player game

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

    GameSelectorWidget* gameSelectorWidget;  // Custom widget
    ServerSelect* serverSelectWidget;  // ServerSelect widget

    void setupUI();
    void applyCommonStyle(QPushButton* button);
    void updateButtonPosition();
    void handleExit();
    void connectButtonClickedSignal(QPushButton* button, void (MainWindow::*member)());
    void hideButtons();  // Helper method to hide buttons 1-6
    void showButtons();  // Helper method to show buttons 1-6
    void changeBackgroundImage(const QString& imagePath);  // Helper method to change background image
};

#endif // MAINWINDOW_H
