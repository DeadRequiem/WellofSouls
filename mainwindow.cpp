#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AudioHandler.h"
#include "Settings.h"
#include <QDebug>
#include <QDir>
#include <QTimer>
#include <QCloseEvent>
#include <QPushButton>
#include <QGraphicsTextItem>

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
    , audioHandler(nullptr)
    , settings(nullptr)
    , closing(false)
    , currentScreen(Screen::First)
{
    ui->setupUi(this);
    this->setMinimumSize(622, 471);
    setupUI();

    settings = new Settings(this);

    audioHandler = new AudioHandler(settings, this);
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
    QPushButton* btnCheckforWorld = nullptr;
    QPushButton* btnPlayNow = nullptr;
    QPushButton* btnPurchaseGoldenSoul = nullptr;
    QPushButton* btnOpenHelpFile = nullptr;
    QPushButton* btnVisitSynRealPage = nullptr;
    QPushButton* btnExitGame = nullptr;

    setupButton(btnCheckforWorld, "Check On-Line for New Worlds");
    setupButton(btnPlayNow, "Play now!");
    setupButton(btnPurchaseGoldenSoul, "Change Purchase Message");
    setupButton(btnOpenHelpFile, "Read the attractive help file");
    setupButton(btnVisitSynRealPage, "Visit synthetic-reality.com");
    setupButton(btnExitGame, "Depart this realm");

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
}

void MainWindow::setupButton(QPushButton*& button, const QString& text)
{
    button = new QPushButton(text);
    applyCommonStyle(button);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    // Resize background to fit the window
    if (backgroundItem) {
        QString imagePath = QDir::currentPath() + "/art/beg.jpg";
        backgroundItem->setPixmap(QPixmap(imagePath).scaled(view->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        backgroundItem->setPos(0, 0); // Ensure background starts from top-left corner
        scene->setSceneRect(0, 0, view->width(), view->height()); // Adjust scene size
    }

    // Update button positions relative to the window size
    updateButtonPosition();
}

void MainWindow::updateButtonPosition()
{
    int windowWidth = view->width();
    int windowHeight = view->height();

    if (buttonProxy1)
        buttonProxy1->setPos(0.1 * windowWidth, 0.2 * windowHeight);

    if (buttonProxy2)
        buttonProxy2->setPos(0.15 * windowWidth, 0.3 * windowHeight);

    if (buttonProxy3)
        buttonProxy3->setPos(0.2 * windowWidth, 0.4 * windowHeight);

    if (buttonProxy4)
        buttonProxy4->setPos(0.25 * windowWidth, 0.5 * windowHeight);

    if (buttonProxy5)
        buttonProxy5->setPos(0.3 * windowWidth, 0.6 * windowHeight);

    if (buttonProxy6)
        buttonProxy6->setPos(0.35 * windowWidth, 0.7 * windowHeight);
}

void MainWindow::applyCommonStyle(QPushButton* button)
{
    QFont font = button->font();
    font.setPointSize(34);
    button->setFont(font);
    button->setStyleSheet(
        "QPushButton { color: #00ff00; border: none; background: transparent; }"
        "QPushButton:hover { color: #ffcc00; }"
        );
}

void MainWindow::connectButtonClickedSignal(QPushButton* button, void (MainWindow::*slot)())
{
    QObject::connect(button, &QPushButton::clicked, this, slot);
}

void MainWindow::onButton1Clicked()
{
    qDebug() << "Check for World Button clicked!";
}

void MainWindow::onButton2Clicked()
{
    qDebug() << "Play Game Button clicked!";

    // Change background for the second screen
    QString imagePath = QDir::currentPath() + "/art/where.jpg";
    QPixmap newBackgroundPixmap(imagePath);
    if (!newBackgroundPixmap.isNull()) {
        // Resize the background image to fit the screen
        backgroundItem->setPixmap(newBackgroundPixmap.scaled(view->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    } else {
        qWarning() << "Failed to load background pixmap from path:" << imagePath;
    }

    // Hide buttons
    hideButtons();

    // Add a text field for the second screen
    QGraphicsTextItem *textField = new QGraphicsTextItem("Where Do You Want To Play?");
    QFont font;
    font.setPointSize(34); // Change font size to 34
    textField->setFont(font);
    // Change text color to #FFFF00 using integer values
    textField->setDefaultTextColor(QColor(255, 255, 0));
    // Position the text field to match the "Check On-Line for New Worlds" button on the first screen
    textField->setPos(buttonProxy1->pos().x(), buttonProxy1->pos().y());
    scene->addItem(textField);

    // Switch to the second screen
    currentScreen = Screen::Second;
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

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!closing) {
        qDebug() << "Close event triggered!";
        closing = true;
        handleExit();
        event->ignore(); // Ignore the initial close event to delay closing
    } else {
        event->accept(); // Accept the close event if it was triggered programmatically
    }
}

void MainWindow::handleExit()
{
    // Play the audio file
    //QString audioFilePath = QDir::currentPath() + "/audio/ExitThanks.mp3";
    //qDebug() << "Attempting to play audio file:" << audioFilePath;
    //audioHandler->playAudioFile(audioFilePath);

    // Timer to close the application after a delay
    QTimer::singleShot(100, this, &QWidget::close); // Increase delay to 3000 ms to ensure audio plays
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == view && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (currentScreen == Screen::Second && keyEvent->key() == Qt::Key_Escape) {
            qDebug() << "Escape key pressed on the second screen!";
            // Switch back to the first screen
            switchToFirstScreen();
            return true; // Consume the event
        }
    }
    // Call base class implementation to handle other events
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::hideButtons()
{
    if (buttonProxy1)
        buttonProxy1->setVisible(false);

    if (buttonProxy2)
        buttonProxy2->setVisible(false);

    if (buttonProxy3)
        buttonProxy3->setVisible(false);

    if (buttonProxy4)
        buttonProxy4->setVisible(false);

    if (buttonProxy5)
        buttonProxy5->setVisible(false);

    if (buttonProxy6)
        buttonProxy6->setVisible(false);
}

void MainWindow::switchToFirstScreen()
{
    // Restore initial background for the first screen
    QString imagePath = QDir::currentPath() + "/art/beg.jpg";
    QPixmap initialBackgroundPixmap(imagePath);
    if (!initialBackgroundPixmap.isNull()) {
        backgroundItem->setPixmap(initialBackgroundPixmap.scaled(view->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    } else {
        qWarning() << "Failed to load background pixmap from path:" << imagePath;
    }

    // Remove the text field for the second screen
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        if (item->type() == QGraphicsTextItem::Type) {
            scene->removeItem(item);
            delete item;
        }
    }

    // Show buttons
    if (buttonProxy1)
        buttonProxy1->setVisible(true);

    if (buttonProxy2)
        buttonProxy2->setVisible(true);

    if (buttonProxy3)
        buttonProxy3->setVisible(true);

    if (buttonProxy4)
        buttonProxy4->setVisible(true);

    if (buttonProxy5)
        buttonProxy5->setVisible(true);

    if (buttonProxy6)
        buttonProxy6->setVisible(true);

    // Switch to the first screen
    currentScreen = Screen::First;
}

