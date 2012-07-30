#include "segmentation.h"

Segmentation::Segmentation(const QString& name, ImageSeries *imageSeries)
{
    m_StringSegmentationName = name;
    m_ImageSeries = imageSeries;
}

Segmentation::~Segmentation()
{
}

void Segmentation::SetSegmentationName(const QString &name)
{
    m_StringSegmentationName = name;
}

const QString& Segmentation::GetSegmentationName() const
{
    return m_StringSegmentationName;
}

ImageSeries* Segmentation::GetImageSeries()
{
    return m_ImageSeries;
}



