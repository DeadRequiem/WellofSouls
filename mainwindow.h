#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QPushButton>

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

private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *backgroundItem;
    QGraphicsProxyWidget *buttonProxy1;
    QGraphicsProxyWidget *buttonProxy2;
    QGraphicsProxyWidget *buttonProxy3;
    QGraphicsProxyWidget *buttonProxy4;
    QGraphicsProxyWidget *buttonProxy5;
    QGraphicsProxyWidget *buttonProxy6;

    void setupUI();
    void setupButton(QPushButton*& button, const QString& text);
    void updateButtonPosition();
    void applyCommonStyle(QPushButton* button);
    void connectButtonClickedSignal(QPushButton* button, void (MainWindow::*slot)());

public slots:
    void onButton1Clicked();
    void onButton2Clicked();
    void onButton3Clicked();
    void onButton4Clicked();
    void onButton5Clicked();
    void onButton6Clicked();
};

#endif // MAINWINDOW_H
