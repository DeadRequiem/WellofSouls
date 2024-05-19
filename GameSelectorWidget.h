#ifndef GAMESELECTORWIDGET_H
#define GAMESELECTORWIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPixmap>
#include <QStyle>
#include <QMouseEvent>
#include <QPointF>

class GameSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    GameSelectorWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QRadioButton *soloGameRadioButton;
    QRadioButton *multiplayerGameRadioButton;
    QPushButton *playGameButton;
    QPushButton *cancelButton;
    QPushButton *helpButton;
    QPushButton *bioButton;
    QPushButton *configureButton;
    QLabel *titleLabel;
    QPushButton *closeButton;
    QWidget *titleBarWidget;
    QPointF dragPosition;

private slots:
    void closeWindow();
    void cancel();
    void playGame();
    void showHelp();
    void showBio();
    void configureNetwork();
    void soloGameSelected();
    void multiplayerGameSelected();

signals:
    void requestClose();  // Signal to reset the UI
};

#endif // GAMESELECTORWIDGET_H
