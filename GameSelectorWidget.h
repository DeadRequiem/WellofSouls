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
    QLabel *imageLabel;
    QLabel *titleLabel;
    QPushButton *closeButton;
    QWidget *titleBarWidget;
    QPointF dragPosition;

private slots:
    void closeWindow();
    void cancel();
    void playGame();  // Slot for Play Game button
    void showHelp();  // Slot for Help button
    void showBio();   // Slot for Bio button
    void configureNetwork();  // Slot for Configure Network Options button
    void soloGameSelected();  // Slot for Solo Game radio button
    void multiplayerGameSelected();  // Slot for Multiplayer Game radio button

signals:
    void requestClose();  // Signal to reset the UI
    void playSinglePlayer();  // Signal for playing single player
    void playMultiplayer();  // Signal for playing multiplayer
};

#endif // GAMESELECTORWIDGET_H
