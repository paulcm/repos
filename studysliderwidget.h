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
    explicit StudySliderWidget(QMap<QDateTime,Study*>* m_StudiesPtr, QWidget *parent = 0);
    ~StudySliderWidget(void);

signals:
    void SignalSliderPositionChanged(int idx);
    
public slots:
    void UpdateSliderValues();

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


    QMap<QDateTime,Study*>* m_StudiesPtr;




};

#endif // STUDYSLIDERWIDGET_H
