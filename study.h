#ifndef STUDY_H
#define STUDY_H

#include <QList>
#include "imageseries.h"

class Study
{
public:

    enum Modality {
        CTPET = 0
    };

    Study(Modality modality, const QDateTime& dateTime);
    ~Study();

    const QDateTime& GetStudyDateTime() const;
    const Modality& GetModality() const;

    ImageSeries* GetImageSeries(ImageSeries::Modality modality) const;

    QString GetDateTimeStr() const;
    QString GetDateStr() const;
    QString GetTimeStr() const;
    QString GetModalityStr() const;


private:
    Modality m_Modality;
    QDateTime m_DateTimeStudy;
    ImageSeries* m_ImageSeriesCT;
    ImageSeries* m_ImageSeriesPET;


};

#endif // STUDY_H
