#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QMetaObject>

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
    QPushButton* button1 = nullptr;
    QPushButton* button2 = nullptr;
    QPushButton* button3 = nullptr;
    QPushButton* button4 = nullptr;
    QPushButton* button5 = nullptr;
    QPushButton* button6 = nullptr;

    setupButton(button1, "Check On-Line for New Worlds");
    setupButton(button2, "Play now!");
    setupButton(button3, "Change Purchase Message");
    setupButton(button4, "Read the attractive help file");
    setupButton(button5, "Visit synthetic-reality.com");
    setupButton(button6, "Depart this realm");

    // Add buttons to the scene and connect signals
    buttonProxy1 = scene->addWidget(button1);
    connectButtonClickedSignal(button1, &MainWindow::onButton1Clicked);

    buttonProxy2 = scene->addWidget(button2);
    connectButtonClickedSignal(button2, &MainWindow::onButton2Clicked);

    buttonProxy3 = scene->addWidget(button3);
    connectButtonClickedSignal(button3, &MainWindow::onButton3Clicked);

    buttonProxy4 = scene->addWidget(button4);
    connectButtonClickedSignal(button4, &MainWindow::onButton4Clicked);

    buttonProxy5 = scene->addWidget(button5);
    connectButtonClickedSignal(button5, &MainWindow::onButton5Clicked);

    buttonProxy6 = scene->addWidget(button6);
    connectButtonClickedSignal(button6, &MainWindow::onButton6Clicked);

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
    // Calculate new button positions based on the window size
    int windowWidth = view->width();
    int windowHeight = view->height();

    // Values to set button position relative to screen size
    int button1X = windowWidth * 0.1; // 10% from the left
    int button1Y = windowHeight * 0.2; // 20% from the top

    int button2X = windowWidth * 0.15; // 15% from the left
    int button2Y = windowHeight * 0.3; // 30% from the top

    int button3X = windowWidth * 0.2; // 20% from the left
    int button3Y = windowHeight * 0.4; // 40% from the top

    int button4X = windowWidth * 0.25; // 25% from the left
    int button4Y = windowHeight * 0.5; // 50% from the top

    int button5X = windowWidth * 0.3; // 30% from the left
    int button5Y = windowHeight * 0.6; // 60% from the top

    int button6X = windowWidth * 0.35; // 35% from the left
    int button6Y = windowHeight * 0.7; // 70% from the top

    buttonProxy1->setPos(button1X, button1Y);
    buttonProxy2->setPos(button2X, button2Y);
    buttonProxy3->setPos(button3X, button3Y);
    buttonProxy4->setPos(button4X, button4Y);
    buttonProxy5->setPos(button5X, button5Y);
    buttonProxy6->setPos(button6X, button6Y);
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
    qDebug() << "Button 1 clicked!";
}

void MainWindow::onButton2Clicked()
{
    qDebug() << "Button 2 clicked!";
}

void MainWindow::onButton3Clicked()
{
    qDebug() << "Button 3 clicked!";
}

void MainWindow::onButton4Clicked()
{
    qDebug() << "Button 4 clicked!";
}

void MainWindow::onButton5Clicked()
{
    qDebug() << "Button 5 clicked!";
}

void MainWindow::onButton6Clicked()
{
    qDebug() << "Button 6 clicked!";
}
