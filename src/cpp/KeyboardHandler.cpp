#include "KeyboardHandler.h"
#include <QDebug>

KeyboardHandler::KeyboardHandler(QObject *parent) : QObject(parent) {}

void KeyboardHandler::handleKeyPress(int value){
    qDebug() << "key pressed: "<< value;
}

void KeyboardHandler::handleDeletePress() {
    qDebug() << "Delete Pressed";
}

void KeyboardHandler::handleEnterPress() {
    qDebug() << "Enter Pressed";
}

void KeyboardHandler::handleLetterPress(const QString &letter) {
    qDebug() << "Letter Pressed:" << letter;
}

