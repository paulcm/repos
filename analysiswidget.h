#ifndef ANALYSISWIDGET_H
#define ANALYSISWIDGET_H

#include <QWidget>

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>
#include <QList>

class AnalysisWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnalysisWidget(QWidget *parent = 0);
    ~AnalysisWidget();
    


    void UpdateStudiesList(QStringList input);

signals:
    void SignalShowReportSummaryDialog();
    void SignalAddStudyToView(int studyIdx);
    void SignalRemoveStudyFromView(int studyIdx);

    void SignalQualitativeSelected();
    void SignalQuantitativeSelected();


protected slots:
    void SlotStudyCheckboxToggled(bool toggled);

protected:
    QVBoxLayout* GetLayout();

    QLabel* GetLabelSelectStudy();

    QPushButton* GetButtonReportSummary();
    QRadioButton* GetRadioButtonQualitative();
    QRadioButton* GetRadioButtonQuantitative();

    void InitializeWidget();

private:
    QVBoxLayout* m_Layout;
    QHBoxLayout* m_HBoxLayoutAnalysisTypeBoxes;

    QLabel* m_LabelSelectStudy;

    QPushButton* m_ButtonReportSummary;
    QRadioButton* m_RadioButtonQualitative;
    QRadioButton* m_RadioButtonQuantitative;

    QList<QCheckBox*> m_StudySelectCheckBoxes;
};

#endif // ANALYSISWIDGET_H
