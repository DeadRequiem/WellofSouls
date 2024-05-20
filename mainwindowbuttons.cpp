#include "mainwindow.h"
#include <QPushButton>

namespace WellOfSouls {

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

void MainWindow::connectButtonClickedSignal(QPushButton* button, void (MainWindow::*member)())
{
    connect(button, &QPushButton::clicked, this, member);
}

void MainWindow::hideButtons()
{
    if (buttonProxy1) buttonProxy1->setVisible(false);
    if (buttonProxy2) buttonProxy2->setVisible(false);
    if (buttonProxy3) buttonProxy3->setVisible(false);
    if (buttonProxy4) buttonProxy4->setVisible(false);
    if (buttonProxy5) buttonProxy5->setVisible(false);
    if (buttonProxy6) buttonProxy6->setVisible(false);
}

void MainWindow::showButtons()
{
    if (buttonProxy1) buttonProxy1->setVisible(true);
    if (buttonProxy2) buttonProxy2->setVisible(true);
    if (buttonProxy3) buttonProxy3->setVisible(true);
    if (buttonProxy4) buttonProxy4->setVisible(true);
    if (buttonProxy5) buttonProxy5->setVisible(true);
    if (buttonProxy6) buttonProxy6->setVisible(true);
}

} // namespace WellOfSouls
