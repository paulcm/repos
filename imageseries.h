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

    void SetImageSeriesID(int id);

    int GetImageSeriesID() const;
    const QDateTime& GetImageSeriesDateTime() const;

    const Modality& GetModality() const;

    QString GetDateTimeStr() const;
    QString GetDateStr() const;
    QString GetTimeStr() const;
    QString GetModalityStr() const;

private:
    int m_ImageSeriesID;
    Modality m_Modality;
    QDateTime m_DateTimeImageSeries;


};

#endif // IMAGESERIES_H
