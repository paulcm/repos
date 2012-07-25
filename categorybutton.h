#ifndef CATEGORYBUTTON_H
#define CATEGORYBUTTON_H

#include <QPushButton>

class CategoryButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CategoryButton(const QString &text, QWidget *parent = 0);
    ~CategoryButton();

    enum ButtonState
    {
        OPEN,
        CLOSED
    };

    const ButtonState& GetButtonState();

signals:
    void SignalButtonState(ButtonState state);

public slots:
    
protected slots:
    void SlotClicked();

private:
    QIcon m_IconOpened;
    QIcon m_IconClosed;

    ButtonState m_State;

    int clickCounter;

};

#endif // CATEGORYBUTTON_H
