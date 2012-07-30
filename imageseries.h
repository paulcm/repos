#ifndef IMAGESERIES_H
#define IMAGESERIES_H

#include <QDateTime>

class ImageSeries
{
public:

    enum Modality {
        CT = 0,
        PET = 1
    };

    ImageSeries(Modality modality, const QDateTime& dateTime);
    ~ImageSeries();

    int GetImageSeriesID() const;
    const QDateTime& GetImageSeriesDateTime() const;

    const Modality& GetModality() const;

    QString GetDateTimeStr() const;
    QString GetDateStr() const;
    QString GetTimeStr() const;
    QString GetModalityStr() const;

private:
    Modality m_Modality;
    QDateTime m_DateTimeImageSeries;


};

#endif // IMAGESERIES_H
