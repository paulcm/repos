#include "imageseries.h"

ImageSeries::ImageSeries(Modality modality, const QDateTime &dateTime) : m_ImageSeriesID(-1)

{
    m_Modality = modality;
    m_DateTimeImageSeries = dateTime;
}

ImageSeries::~ImageSeries()
{
}

void ImageSeries::SetImageSeriesID(int id)
{
    m_ImageSeriesID = id;
}

int ImageSeries::GetImageSeriesID() const
{
    return m_ImageSeriesID;
}

const ImageSeries::Modality& ImageSeries::GetModality() const
{
    return m_Modality;
}

const QDateTime& ImageSeries::GetImageSeriesDateTime() const
{
    return m_DateTimeImageSeries;
}

QString ImageSeries::GetDateTimeStr() const
{
    return m_DateTimeImageSeries.toString("yyyy.MM.dd HH:MM");
}

QString ImageSeries::GetDateStr() const
{
    return m_DateTimeImageSeries.date().toString("yyyy.MM.dd");
}

QString ImageSeries::GetTimeStr() const
{
    return m_DateTimeImageSeries.time().toString("HH:MM:SS ap");
}

QString ImageSeries::GetModalityStr() const
{
    if(m_Modality == CT)
        return QString("CT");
    else if(m_Modality == PET)
        return QString("PET");

    else
        return QString("unknown");
}



