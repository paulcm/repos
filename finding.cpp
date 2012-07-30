#include "finding.h"

Finding::Finding(const QString& name)
{
    m_StringFindingName = name;
}

Finding::~Finding()
{
    for(int i=0; i < m_ListSegmentations.size(); ++i)
    {
        delete m_ListSegmentations.value(i);
    }

    m_ListSegmentations.clear();
}

void Finding::SetFindingName(const QString& name)
{
    m_StringFindingName = name;
}


const QString& Finding::GetFindingName()
{
    return m_StringFindingName;
}


QList<Segmentation*>* Finding::GetAllSegmentations()
{
    return &m_ListSegmentations;
}

QList<Segmentation*> Finding::GetSegmentations(const QDateTime &dateTime)
{
    QList<Segmentation*> resultList;

    for(int i=0; i < m_ListSegmentations.size(); ++i)
    {
        Segmentation* tempSegmentation = m_ListSegmentations.value(i);

        if(tempSegmentation->GetImageSeries()->GetImageSeriesDateTime() == dateTime)
            resultList.append(tempSegmentation);
    }

   return resultList;
}



bool Finding::AddSegmentation(Segmentation *segmentation)
{

    if(m_ListSegmentations.contains(segmentation))
        return false;


    m_ListSegmentations.append(segmentation);

    return true;
}

bool Finding::RemoveSegmentation(Segmentation* segmentation)
{
    if(!m_ListSegmentations.contains(segmentation))
        return false;

    m_ListSegmentations.removeOne(segmentation);

    return true;
}

