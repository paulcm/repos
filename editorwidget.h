#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QIcon>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>

class EditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EditorWidget(QWidget *parent = 0);
    ~EditorWidget();
    
    void SetFindingType(const QString& findingType);
    void SetLabelColorStyleSheet(const QString& cssColor);

signals:
    void SignalEditorButtonClicked();
    void SignalCreateNewSegmentation(const QString& name);

public slots:
    void setDisabled(bool disable);
    void setEnabled(bool enable);

protected slots:
    void SlotAddSegmentationClicked();

protected:
    QGridLayout* GetLayout();

    QLabel* GetLabelInfoLabel();
    QLabel* GetLabelFindingType();

    QSpinBox* GetSpinBoxLeft();
    QSpinBox* GetSpinBoxRight();

    QSlider* GetSliderThresholdLeft();
    QSlider* GetSliderThresholdRight();

    QPushButton* GetButtonAddToFinding();
    QFrame* GetFrameLabelColor();

    void InitializeWidget();

    QPushButton* CreateEditorButton(const QIcon& icon, bool enabled = true);

private:
    QGridLayout* m_Layout;

    QLabel* m_LabelInfoLabel;
    QLabel* m_LabelFindingType;

    QSpinBox* m_SpinBoxLeft;
    QSpinBox* m_SpinBoxRight;

    QSlider* m_SliderThresholdLeft;
    QSlider* m_SliderThresholdRight;

    QFrame* m_FrameLabelColor;
    QPushButton* m_ButtonAddToFinding;

    QIcon m_IconDefault;
    QIcon m_IconDraw;
    QIcon m_IconErase;
    QIcon m_IconPaint;
    QIcon m_IconRedo;
    QIcon m_IconThreshold;
    QIcon m_IconUndo;

};

#endif // EDITORWIDGET_H
