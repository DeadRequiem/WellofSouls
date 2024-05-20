#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AudioHandler.h"
#include "Settings.h"
#include "GameSelectorWidget.h"
#include "ServerSelect.h"
#include <QDebug>
#include <QDir>
#include <QTimer>
#include <QCloseEvent>
#include <QPushButton>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QMessageBox>

namespace WellOfSouls {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(nullptr)
    , view(nullptr)
    , backgroundItem(nullptr)
    , buttonProxy1(nullptr)
    , buttonProxy2(nullptr)
    , buttonProxy3(nullptr)
    , buttonProxy4(nullptr)
    , buttonProxy5(nullptr)
    , buttonProxy6(nullptr)
    , gameSelectorProxy(nullptr)
    , serverSelectProxy(nullptr)
    , audioHandler(nullptr)
    , settings(nullptr)
    , closing(false)
    , gameSelectorWidget(nullptr)
    , serverSelectWidget(nullptr)
{
    ui->setupUi(this);
    this->setMinimumSize(622, 471);

    settings = new Settings(this);
    audioHandler = new AudioHandler(settings, this);

    setupUI();

    // Application icon
    QIcon appIcon(":/ico/ico/ico32.png");
    qApp->setWindowIcon(appIcon);

    // Window icon
    QIcon windowIcon(":/ico/ico/ico32.png");
    window()->setWindowIcon(windowIcon);

    // Window title
    setWindowTitle("Well of Souls 2");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete audioHandler;
    delete settings;
}

void MainWindow::setupUI()
{
    // Create QGraphicsView and QGraphicsScene
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Hide scroll bars
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFrameStyle(QFrame::NoFrame);

    // Set initial background pixmap
    QString imagePath = QDir::currentPath() + "/art/beg.jpg";
    QPixmap backgroundPixmap(imagePath);
    if (!backgroundPixmap.isNull()) {
        backgroundItem = new QGraphicsPixmapItem(backgroundPixmap);
        scene->addItem(backgroundItem);
    } else {
        qWarning() << "Failed to load background pixmap from path:" << imagePath;
    }

    // Create and style buttons
    QPushButton* btnCheckforWorld = new QPushButton("Check On-Line for New Worlds");
    applyCommonStyle(btnCheckforWorld);
    QPushButton* btnPlayNow = new QPushButton("Play now!");
    applyCommonStyle(btnPlayNow);
    QPushButton* btnPurchaseGoldenSoul = new QPushButton("Change Purchase Message");
    applyCommonStyle(btnPurchaseGoldenSoul);
    QPushButton* btnOpenHelpFile = new QPushButton("Read the attractive help file");
    applyCommonStyle(btnOpenHelpFile);
    QPushButton* btnVisitSynRealPage = new QPushButton("Visit synthetic-reality.com");
    applyCommonStyle(btnVisitSynRealPage);
    QPushButton* btnExitGame = new QPushButton("Depart this realm");
    applyCommonStyle(btnExitGame);

    // Add buttons to the scene and connect signals
    buttonProxy1 = scene->addWidget(btnCheckforWorld);
    connectButtonClickedSignal(btnCheckforWorld, &MainWindow::onButton1Clicked);

    buttonProxy2 = scene->addWidget(btnPlayNow);
    connectButtonClickedSignal(btnPlayNow, &MainWindow::onButton2Clicked);

    buttonProxy3 = scene->addWidget(btnPurchaseGoldenSoul);
    connectButtonClickedSignal(btnPurchaseGoldenSoul, &MainWindow::onButton3Clicked);

    buttonProxy4 = scene->addWidget(btnOpenHelpFile);
    connectButtonClickedSignal(btnOpenHelpFile, &MainWindow::onButton4Clicked);

    buttonProxy5 = scene->addWidget(btnVisitSynRealPage);
    connectButtonClickedSignal(btnVisitSynRealPage, &MainWindow::onButton5Clicked);

    buttonProxy6 = scene->addWidget(btnExitGame);
    connectButtonClickedSignal(btnExitGame, &MainWindow::onButton6Clicked);

    updateButtonPosition(); // Initial positioning of buttons

    // Install event filter to capture key press events
    view->installEventFilter(this);

    // Create and add the GameSelectorWidget
    gameSelectorWidget = new GameSelectorWidget();
    gameSelectorProxy = scene->addWidget(gameSelectorWidget);
    gameSelectorProxy->setVisible(false);  // Hide by default

    // Connect signals from GameSelectorWidget to the appropriate slots
    connect(gameSelectorWidget, &GameSelectorWidget::requestClose, this, &MainWindow::resetUI);
    connect(gameSelectorWidget, &GameSelectorWidget::playSinglePlayer, this, &MainWindow::startSinglePlayerGame);
    connect(gameSelectorWidget, &GameSelectorWidget::playMultiplayer, this, &MainWindow::showServerSelect);

    // Initialize ServerSelect widget and its proxy
    serverSelectWidget = new ServerSelect();
    serverSelectProxy = scene->addWidget(serverSelectWidget);
    serverSelectProxy->setVisible(false); // Hide by default
}

void MainWindow::resetUI()
{
    // Show buttons 1-6
    showButtons();

    // Change background image to beg.jpg
    changeBackgroundImage(QDir::currentPath() + "/art/beg.jpg");

    // Hide GameSelectorWidget and ServerSelect widget
    gameSelectorProxy->setVisible(false);
    serverSelectProxy->setVisible(false);
}

void MainWindow::showServerSelect()
{
    qDebug() << "Navigating to ServerSelect";

    // Hide the GameSelectorWidget
    gameSelectorProxy->setVisible(false);

    // Hide buttons
    hideButtons();

    // Display the ServerSelect widget
    serverSelectProxy->setVisible(true);
    serverSelectProxy->setPos((view->width() - serverSelectProxy->size().width()) / 2,
                              (view->height() - serverSelectProxy->size().height()) / 2);
}

void MainWindow::startSinglePlayerGame()
{
    qDebug() << "Starting Single Player Game";

    // Placeholder action for starting a single-player game
    // Replace with actual single-player game logic
    QMessageBox::information(this, "Single Player", "Starting single player game...");
}

void MainWindow::onButton1Clicked()
{
    qDebug() << "Check for World Button clicked!";
}

void MainWindow::onButton2Clicked()
{
    // Hide buttons 1-6
    hideButtons();

    // Change background image to where.jpg
    changeBackgroundImage(QDir::currentPath() + "/art/where.jpg");

    // Show GameSelectorWidget and center it
    gameSelectorProxy->setVisible(true);
    gameSelectorProxy->setPos((view->width() - gameSelectorProxy->size().width()) / 2,
                              (view->height() - gameSelectorProxy->size().height()) / 2);
}

void MainWindow::onButton3Clicked()
{
    qDebug() << "Purchase Golden Soul Button clicked!";
}

void MainWindow::onButton4Clicked()
{
    qDebug() << "Open Help File Button clicked!";
}

void MainWindow::onButton5Clicked()
{
    qDebug() << "Visit SynReal Page Button clicked!";
}

void MainWindow::onButton6Clicked()
{
    qDebug() << "Exit Game Button clicked!";
    closing = true;
    handleExit();
}

void MainWindow::changeBackgroundImage(const QString& imagePath)
{
    if (backgroundItem) {
        backgroundItem->setPixmap(QPixmap(imagePath).scaled(view->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        backgroundItem->setPos(0, 0);
        scene->setSceneRect(0, 0, view->width(), view->height());
    }
}

} // namespace WellOfSouls
