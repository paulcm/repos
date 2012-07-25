#ifndef SEPARATOR_H
#define SEPARATOR_H

#include <QFrame>

class Separator : public QFrame
{
    Q_OBJECT
public:
    explicit Separator(QWidget *parent = 0);
    ~Separator();
};

#endif // SEPARATOR_H
