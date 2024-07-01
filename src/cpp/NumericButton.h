#ifndef NUMERICBUTTON_H
#define NUMERICBUTTON_H

#include <QObject>

class NumericButton : public QObject {
    Q_OBJECT
public:
    explicit NumericButton(QObject *parent = nullptr);

public slots:
    void handleKeyPress(int value);
    void handleDeletePress();
    void handleEnterPress();
    void handleLetterPress(const QString &letter);
};


#endif // NUMERICBUTTON_H
