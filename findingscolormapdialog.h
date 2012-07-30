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

    int GetSelectedLabelColor();

signals:
    void SignalApply();
    void SignalClose();
    
protected slots:
    void SlotApply();

protected:
    QGridLayout* GetLayout();
    QLabel* GetLabelMapInfo();
    QLabel* GetLabelColorInfo();
    QComboBox* GetComboBoxColorMap();
    QComboBox* GetComboBoxLabelColors();
    QPushButton* GetButtonApply();
    QPushButton* GetButtonCancel();

    void InitializeDialog();

private:
    QGridLayout* m_Layout;
    QLabel* m_LabelMapInfo;
    QLabel* m_LabelColorInfo;
    QComboBox* m_ComboBoxColorMap;
    QComboBox* m_ComboBoxLabelColors;
    QPushButton* m_ButtonApply;
    QPushButton* m_ButtonCancel;
    
    QIcon m_IconColorMap;
    QIcon m_IconColorTumor;
    QIcon m_IconColorNode;
    QIcon m_IconColorMetastasis;
    QIcon m_IconColorReference;

    bool m_Applied;

};

#endif // FINDINGSCOLORMAPDIALOG_H
