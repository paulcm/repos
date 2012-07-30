#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <QString>
#include "imageseries.h"

class Segmentation
{
public:
    Segmentation(const QString& name, ImageSeries* imageSeries);
    ~Segmentation();

    const QString& GetSegmentationName() const;
    ImageSeries* GetImageSeries();

    void SetSegmentationName(const QString& name);

private:
    QString m_StringSegmentationName;
    ImageSeries* m_ImageSeries;
};

#endif // SEGMENTATION_H
