#ifndef FINDINGSCOLORMAPDIALOG_H
#define FINDINGSCOLORMAPDIALOG_H

#include <QDialog>

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QIcon>

class FindingsColorMapDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FindingsColorMapDialog(QWidget *parent = 0);
    ~FindingsColorMapDialog();
    
    bool GetApplied();
    void SetApplied(bool applied);

signals:
    void SignalApply();
    void SignalClose();
    
protected slots:
    void SlotApply();

protected:
    QGridLayout* GetLayout();
    QLabel* GetLabelInfo();
    QComboBox* GetComboBoxColorMap();
    QPushButton* GetButtonApply();
    QPushButton* GetButtonCancel();

    void InitializeDialog();

private:
    QGridLayout* m_Layout;
    QLabel* m_LabelInfo;
    QComboBox* m_ComboBoxColorMap;
    QPushButton* m_ButtonApply;
    QPushButton* m_ButtonCancel;
    
    QIcon m_IconColorMap;

    bool m_Applied;

};

#endif // FINDINGSCOLORMAPDIALOG_H
