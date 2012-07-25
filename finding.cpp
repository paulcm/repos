#include "finding.h"

Finding::Finding(const QString& name) : m_FindingID(-1)
{
    m_StringFindingName = name;
}

Finding::~Finding()
{
    for(int i=0; i < m_MapSegmentations.values().size(); ++i)
    {
        delete m_MapSegmentations.values().at(i);
    }

    m_MapSegmentations.clear();
}

void Finding::SetFindingID(int id)
{
    m_FindingID = id;
}

int Finding::GetFindingID()
{
    return m_FindingID;
}

const QString& Finding::GetFindingName()
{
    return m_StringFindingName;
}

QList<Segmentation*> Finding::GetAllSegmentations() const
{
   return m_MapSegmentations.values();
}

Segmentation* Finding::GetSegmentation(ImageSeries* series) const
{
   return m_MapSegmentations.value(series,NULL);
}


bool Finding::AddSegmentation(ImageSeries* series, Segmentation *segmentation)
{
    if(m_MapSegmentations.contains(series))
        return false;

    if(series && segmentation)
    {
        m_MapSegmentations.insert(series,segmentation);
    }

    return false;
}

bool Finding::RemoveSegmentation(ImageSeries* series)
{
    int ret = m_MapSegmentations.remove(series);

    if(ret == 0)
        return false;
    else
        return true;
}

