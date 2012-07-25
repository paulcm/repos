#include "segmentation.h"

Segmentation::Segmentation(const QString& name, Study* study)
{
    m_StringSegmentationName = name;
    m_Study = study;
}

Segmentation::~Segmentation()
{
}

const QString& Segmentation::GetSegmentationName() const
{
    return m_StringSegmentationName;
}

Study* Segmentation::GetStudy() const
{
    return m_Study;
}



