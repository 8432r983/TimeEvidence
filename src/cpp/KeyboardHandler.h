#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <QObject>

class KeyboardHandler : public QObject{
    Q_OBJECT
public:
    explicit KeyboardHandler(QObject *parent = nullptr);

public slots:
    void handleKeyPress(int value);
    void handleDeletePress();
    void handleEnterPress();
    void handleLetterPress(const QString &letter);
};



#endif // KEYBOARDHANDLER_H
