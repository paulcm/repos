#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QIcon>
#include <QLabel>
#include <QGridLayout>
#include <QSplitter>
#include <QPushButton>
#include <QFrame>
#include <QList>
#include <QComboBox>
#include <QTableWidget>
#include <QCheckBox>
#include <QScrollArea>
#include <QSlider>
#include <QTreeWidget>
#include <QRadioButton>
#include <QPixmap>
#include <QMap>

//namespace Ui {
//class MainWindow;
//}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum VIEW_TYPE {
        CONVENTIONAL,
        FOUR_UP
    };


signals:
    void sig_ReportCreated(bool created);

protected:
    void InitializeImageViewWidgets();
    void ChangeImageView(VIEW_TYPE type);

    void InitializeTopPanelElements();
    void InitializeBottomPanelElements();
    
    QFrame* CreateSeparator(QWidget* parent = NULL);
    QPushButton* CreateTopPanelButton(const QString& text, QWidget* parent = NULL);

protected slots:
    void on_TopPanelButtonClicked(bool checked);
    void on_ShowTopPanelWidget(bool show, QPushButton* button);
    void on_ReportComboboxImageWidgetActivation(int selectedID);
    void on_PatientsComboboxFillTable(int selectedID);
    void on_TableCheckboxClicked(bool checked);
    void on_TimepointSliderMoved(int value);
    void on_FindingsComboboxSelectionChanged(int index);
    void on_DisplayROIButtonClicked();
    void on_EnableFindingsWidgetContent(bool enable);
    void on_AddSegmentationToFinding();
    void on_ShowSegmentationTypeWidget(bool show);
    void on_AnalysisViewChanged(bool show);
    void on_BottomPanelTreeWidgetItemPressed(QTreeWidgetItem* item, int column = 0);

private:
    //Ui::MainWindow *ui;



    //Central Widget
    QGridLayout* m_CentralWidgetLayout;
    QLabel* m_CentralWidgetLabel;

    //Dock Widget
    QDockWidget* m_DockWidgetLeft;
    QSplitter* m_DockWidgetLeftSplitter;
    QWidget* m_ModulePanelTop;
    QWidget* m_ModulePanelBottom;


    //Icons for Buttons
    QIcon m_ButtonIconOpened;
    QIcon m_ButtonIconClosed;
    QIcon m_ButtonIconShow;
    QIcon m_ButtonIconHide;


    //ImageViewWidgets
    QWidget* m_ImageViewWidget3D;
    QLabel* m_ImageViewWidget3DTitlebarLabel;
    QLabel* m_ImageViewWidget3DRenderAreaLabel;

    QWidget* m_ImageViewWidgetAxial;
    QLabel* m_ImageViewWidgetAxialTitlebarLabel;
    QLabel* m_ImageViewWidgetAxialRenderAreaLabel;

    QWidget* m_ImageViewWidgetSagittal;
    QLabel* m_ImageViewWidgetSagittalTitlebarLabel;
    QLabel* m_ImageViewWidgetSagittalRenderAreaLabel;

    QWidget* m_ImageViewWidgetCoronal;
    QLabel* m_ImageViewWidgetCoronalTitlebarLabel;
    QLabel* m_ImageViewWidgetCoronalRenderAreaLabel;


    //Top Panel Buttons
    QPushButton* m_HelpButton;
    QPushButton* m_ReportButton;
    QPushButton* m_ImagesButton;
    QPushButton* m_FindingsButton;
    QPushButton* m_AnalysisButton;

    QList<QPushButton*> m_TopPanelButtons;
    QList<QWidget*> m_TopPanelWidgets;
    QList<QCheckBox*> m_ImagesTableCheckBoxes;


    //Bottom Panel Elements
    QSlider* m_BottomPanelTimepointSlider;
    QTreeWidget* m_BottomPanelTreeWidget;
    QLabel* m_BottomPanelCurrentTimepointLabel;

    //ReportWidget
    QWidget* m_ReportWidget;
    QWidget* CreateReportWidget(QWidget* parent = NULL);
    QComboBox* m_ReportComboBox;

    //ImagesWidget
    QWidget* m_ImagesWidget;
    QComboBox* m_ImagesSelectPatientComboBox;
    QTableWidget* m_ImagesSelectImageTable;
    QWidget* CreateImagesWidget(QWidget* parent = NULL);

    //FindingsWidget
    QWidget* m_FindingsWidget;
    QComboBox* m_FindingsSelectComboBox;
    QPushButton* m_FindingsDisplayROIButton;
    QRadioButton* m_FindingsNewSegmentationRadioButton;
    QRadioButton* m_FindingsSelectSegmentationRadioButton;
    QLabel* m_FindingsOrLabel;
    QWidget* m_FindingsNewSegmentationWidget;
    QWidget* m_FindingsSelectSegmentationWidget;
    QPushButton* m_FindingsAddSegmentationButton;
    QWidget* CreateFindingsWidget(QWidget* parent = NULL);

    //AnalysisWidget
    QWidget* m_AnalysisWidget;
    QRadioButton* m_AnalysisQualitativeRadioButton;
    QRadioButton* m_AnalysisQuantitativeRadioButton;
    QList<QCheckBox*> m_AnalysisCheckboxes;
    QPushButton* m_AnalysisPrintReportButton;
    QWidget* CreateAnalysisWidget(QWidget* parent = NULL);

    //Dates and Times
    QStringList m_Dates, m_Times;

};

#endif // MAINWINDOW_H
