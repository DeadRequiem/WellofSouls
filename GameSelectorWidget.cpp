#include "GameSelectorWidget.h"
#include <QKeyEvent>
#include <QDebug>

GameSelectorWidget::GameSelectorWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);

    // Create the title bar
    titleLabel = new QLabel("Where would you like to play today? (tm)");
    closeButton = new QPushButton("X");
    closeButton->setFixedSize(30, 30);

    connect(closeButton, &QPushButton::clicked, this, &GameSelectorWidget::closeWindow);
    connect(closeButton, &QPushButton::clicked, this, &GameSelectorWidget::requestClose);  // Emit signal to reset UI

    titleBarWidget = new QWidget(this);
    QHBoxLayout *titleBarLayout = new QHBoxLayout(titleBarWidget);
    titleBarLayout->addWidget(titleLabel);
    titleBarLayout->addStretch();
    titleBarLayout->addWidget(closeButton);
    titleBarLayout->setContentsMargins(0, 0, 0, 0);
    titleBarWidget->setLayout(titleBarLayout);

    titleBarWidget->setStyleSheet("background-color: #CCCCCC;");

    // Create the radio buttons
    soloGameRadioButton = new QRadioButton("Solo Game -- Play alone by yourself (no network required).");
    multiplayerGameRadioButton = new QRadioButton("Multiplayer Game -- Play with others, using a network or modem.");
    multiplayerGameRadioButton->setChecked(true);

    connect(soloGameRadioButton, &QRadioButton::clicked, this, &GameSelectorWidget::soloGameSelected);
    connect(multiplayerGameRadioButton, &QRadioButton::clicked, this, &GameSelectorWidget::multiplayerGameSelected);

    // Create the buttons
    playGameButton = new QPushButton("Play Game");
    cancelButton = new QPushButton("Cancel");
    helpButton = new QPushButton("Help");
    bioButton = new QPushButton("Bio");
    configureButton = new QPushButton("Configure Network Options");

    connect(playGameButton, &QPushButton::clicked, this, &GameSelectorWidget::playGame);
    connect(cancelButton, &QPushButton::clicked, this, &GameSelectorWidget::cancel);
    connect(cancelButton, &QPushButton::clicked, this, &GameSelectorWidget::requestClose);  // Emit signal to reset UI
    connect(helpButton, &QPushButton::clicked, this, &GameSelectorWidget::showHelp);
    connect(bioButton, &QPushButton::clicked, this, &GameSelectorWidget::showBio);
    connect(configureButton, &QPushButton::clicked, this, &GameSelectorWidget::configureNetwork);

    // Create the image label
    imageLabel = new QLabel();
    QPixmap pixmap(":/path/to/your/image.png"); // Update with the correct path to your image
    imageLabel->setPixmap(pixmap);
    imageLabel->setFixedSize(pixmap.size());

    // Create layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QGroupBox *gameArenaGroupBox = new QGroupBox("Select Game Arena");
    QVBoxLayout *gameArenaLayout = new QVBoxLayout(gameArenaGroupBox);
    QVBoxLayout *rightButtonLayout = new QVBoxLayout();
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // Add widgets to layouts
    gameArenaLayout->addWidget(soloGameRadioButton);
    gameArenaLayout->addWidget(multiplayerGameRadioButton);

    buttonLayout->addWidget(helpButton);
    buttonLayout->addWidget(bioButton);
    buttonLayout->addWidget(configureButton);

    rightButtonLayout->addWidget(playGameButton);
    rightButtonLayout->addWidget(cancelButton);
    rightButtonLayout->addStretch();

    bottomLayout->addLayout(buttonLayout);
    bottomLayout->addStretch();
    bottomLayout->addLayout(rightButtonLayout);

    mainLayout->addWidget(titleBarWidget);
    mainLayout->addWidget(gameArenaGroupBox);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
}

void GameSelectorWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPosition() - frameGeometry().topLeft();
        event->accept();
    }
}

void GameSelectorWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move((event->globalPosition() - dragPosition).toPoint());
        event->accept();
    }
}

void GameSelectorWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        emit requestClose();
    }
    QWidget::keyPressEvent(event);
}

void GameSelectorWidget::closeWindow()
{
    close();
}

void GameSelectorWidget::cancel()
{
    close();
}

void GameSelectorWidget::playGame()
{
    if (soloGameRadioButton->isChecked()) {
        emit playSinglePlayer();
    } else if (multiplayerGameRadioButton->isChecked()) {
        emit playMultiplayer();
    }
}

void GameSelectorWidget::showHelp()
{
    qDebug() << "Help button clicked!";
}

void GameSelectorWidget::showBio()
{
    qDebug() << "Bio button clicked!";
}

void GameSelectorWidget::configureNetwork()
{
    qDebug() << "Configure Network Options button clicked!";
}

void GameSelectorWidget::soloGameSelected()
{
    qDebug() << "Solo Game radio button selected!";
}

void GameSelectorWidget::multiplayerGameSelected()
{
    qDebug() << "Multiplayer Game radio button selected!";
}
