#include "NumericButton.h"
#include <QDebug>

NumericButton::NumericButton(QObject *parent) : QObject(parent) {}

void NumericButton::handleKeyPress(int value) {
    qDebug() << "Key Pressed:" << value;
    // Add your handling code here
}

void NumericButton::handleDeletePress() {
    qDebug() << "Delete Pressed";
    // Add your handling code here
}

void NumericButton::handleEnterPress() {
    qDebug() << "Enter Pressed";
    // Add your handling code here
}

void NumericButton::handleLetterPress(const QString &letter) {
    qDebug() << "Letter Pressed:" << letter;
    // Add your handling code here
}
