#ifndef STUDYSLIDERWIDGET_H
#define STURYSLIDERWIDGET_H

#include <QWidget>

#include <QSlider>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <QMap>
#include <QDateTime>

#include "study.h"


class StudySliderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StudySliderWidget(QWidget *parent = 0);
    ~StudySliderWidget(void);

    int GetSliderPosition();

signals:
    void SignalSliderPositionChanged(int idx);
    
public slots:
    void UpdateValues(int min = 0, int max = 1, int selected = 0, QString label = "");

protected:
    void InitializeWidget();

    QGridLayout* GetLayout();
    QSlider* GetSliderStudySelector();
    QLabel* GetLabelInfo();
    QLabel* GetLabelSelectedStudy();

private:
    QGridLayout* m_Layout;
    QLabel* m_LabelInfo;
    QLabel* m_LabelSelectedStudy;
    QSlider* m_SliderStudySelector;

};

#endif // STUDYSLIDERWIDGET_H
