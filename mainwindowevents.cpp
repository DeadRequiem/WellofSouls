#include "mainwindow.h"
#include <QTimer>
#include <QDir>

namespace WellOfSouls {

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if (backgroundItem) {
        QString imagePath = QDir::currentPath() + "/art/beg.jpg";
        backgroundItem->setPixmap(QPixmap(imagePath).scaled(view->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        backgroundItem->setPos(0, 0); // Ensure background starts from top-left corner
        scene->setSceneRect(0, 0, view->width(), view->height()); // Adjust scene size
    }

    updateButtonPosition();
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

} // namespace WellOfSouls
