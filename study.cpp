#include "study.h"

Study::Study(Modality modality, const QDateTime &dateTime)
{
    m_Modality = modality;
    m_DateTimeStudy = QDateTime(dateTime);

    m_ImageSeriesCT = new ImageSeries(ImageSeries::CT, dateTime);
    m_ImageSeriesPET = new ImageSeries(ImageSeries::PET, dateTime);
}

Study::~Study()
{
    delete m_ImageSeriesCT;
    delete m_ImageSeriesPET;
}

const QDateTime& Study::GetStudyDateTime() const
{
    return m_DateTimeStudy;
}

const Study::Modality& Study::GetModality() const
{
    return m_Modality;
}

ImageSeries *Study::GetImageSeries(ImageSeries::Modality modality) const
{
    if(modality == ImageSeries::CT)
        return m_ImageSeriesCT;

    else if(modality == ImageSeries::PET)
        return m_ImageSeriesPET;

    else
        return NULL;
}

QString Study::GetDateTimeStr() const
{
    return m_DateTimeStudy.toString("MM/dd/yyyy HH:MM");
    //return m_DateTimeStudy.toString("yyyy.MM.dd HH:MM");
}

QString Study::GetDateStr() const
{
    return m_DateTimeStudy.date().toString("MM/dd/yyyy");
}

QString Study::GetTimeStr() const
{
    return m_DateTimeStudy.time().toString("HH:mm:ss ap");
}

QString Study::GetModalityStr() const
{
    if(m_Modality == CTPET)
        return QString("CT/PET");

    else
        return QString("unknown");
}

