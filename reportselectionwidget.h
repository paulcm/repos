#ifndef REPORTSELECTIONWIDGET_H
#define REPORTSELECTIONWIDGET_H

#include <QWidget>

#include <QLabel>
#include <QComboBox>
#include <QGridLayout>

#include <QMap>

#include "report.h"
#include "nodecombobox.h"

class ReportSelectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReportSelectionWidget(QList<Report*>* reports, QWidget *parent = 0);
    ~ReportSelectionWidget();
    
signals:
    void SignalChangeReport(const QString& name);
    void SignalCreateNewReport(const QString& reportName);
    void SignalRenameReport(const QString& oldname, const QString& newname);
    void SignalDeleteReport(const QString& name);

public slots:
    void UpdateReportSelectorNodeComboBox(Report* currentReport);

protected:
    QGridLayout* GetLayout();
    QLabel* GetLabelSelect();
    NodeComboBox* GetNodeComboBoxSelectReport();

    QList<QString>* UpdateListReportNames();

    void InitializeWidget();

protected slots:
   // void SlotReportSelectionComboBoxSelectionChanged(const QString& selected);

private:
    QGridLayout* m_Layout;
    QLabel* m_LabelSelect;
    NodeComboBox* m_NodeComboBoxSelectReport;

    QList<Report*> m_ListReports;

    QString m_ComboBoxItemNone;
    QString m_ComboBoxItemRename;
    QString m_ComboBoxItemCreate;
    QString m_ComboBoxItemDelete;
    QString m_ComboBoxSplitter;

    QString m_LastSelected;

    QList<Report*>* m_ReportsPtr;
    QList<QString> m_ListReportNames;
};

#endif // REPORTSELECTIONWIDGET_H
