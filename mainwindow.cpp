#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QMetaObject>

enum ButtonPositions {
    TenPercent = 10,
    FifteenPercent = 15,
    TwentyPercent = 20,
    TwentyFivePercent = 25,
    ThirtyPercent = 30,
    ThirtyFivePercent = 35,
    FourtyPercent = 40,
    FiftyPercent = 50,
    SixtyPercent = 60,
    SeventyPercent = 70
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(622, 471);
    setupUI();
}

MainWindow::~MainWindow()
{
    delete ui;
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

    // Set background pixmap
    QString imagePath = QDir::currentPath() + "/art/beg.jpg";
    QPixmap backgroundPixmap(imagePath);
    if (!backgroundPixmap.isNull()) {
        backgroundItem = new QGraphicsPixmapItem(backgroundPixmap);
        scene->addItem(backgroundItem);
    } else {
        qWarning() << "Failed to load background pixmap from path:" << imagePath;
    }

    // Create and style buttons
    QPushButton* CheckforWorldButton = nullptr;
    QPushButton* PlayGameButton = nullptr;
    QPushButton* PurchaseGoldenSoulButton = nullptr;
    QPushButton* OpenHelpFileButton = nullptr;
    QPushButton* VisitSynRealPageButton = nullptr;
    QPushButton* ExitGameButton = nullptr;

    setupButton(CheckforWorldButton, "Check On-Line for New Worlds");
    setupButton(PlayGameButton, "Play now!");
    setupButton(PurchaseGoldenSoulButton, "Change Purchase Message");
    setupButton(OpenHelpFileButton, "Read the attractive help file");
    setupButton(VisitSynRealPageButton, "Visit synthetic-reality.com");
    setupButton(ExitGameButton, "Depart this realm");

    // Add buttons to the scene and connect signals
    buttonProxy1 = scene->addWidget(CheckforWorldButton);
    connectButtonClickedSignal(CheckforWorldButton, &MainWindow::onButton1Clicked);

    buttonProxy2 = scene->addWidget(PlayGameButton);
    connectButtonClickedSignal(PlayGameButton, &MainWindow::onButton2Clicked);

    buttonProxy3 = scene->addWidget(PurchaseGoldenSoulButton);
    connectButtonClickedSignal(PurchaseGoldenSoulButton, &MainWindow::onButton3Clicked);

    buttonProxy4 = scene->addWidget(OpenHelpFileButton);
    connectButtonClickedSignal(OpenHelpFileButton, &MainWindow::onButton4Clicked);

    buttonProxy5 = scene->addWidget(VisitSynRealPageButton);
    connectButtonClickedSignal(VisitSynRealPageButton, &MainWindow::onButton5Clicked);

    buttonProxy6 = scene->addWidget(ExitGameButton);
    connectButtonClickedSignal(ExitGameButton, &MainWindow::onButton6Clicked);

    updateButtonPosition(); // Initial positioning of buttons
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

    buttonProxy1->setPos(TenPercent * windowWidth / 100, TwentyPercent * windowHeight / 100);
    buttonProxy2->setPos(FifteenPercent * windowWidth / 100, ThirtyPercent * windowHeight / 100);
    buttonProxy3->setPos(TwentyPercent * windowWidth / 100, FourtyPercent * windowHeight / 100);
    buttonProxy4->setPos(TwentyFivePercent * windowWidth / 100, FiftyPercent * windowHeight / 100);
    buttonProxy5->setPos(ThirtyPercent * windowWidth / 100, SixtyPercent * windowHeight / 100);
    buttonProxy6->setPos(ThirtyFivePercent * windowWidth / 100, SeventyPercent * windowHeight / 100);
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
}
