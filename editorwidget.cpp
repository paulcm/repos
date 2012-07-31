#include "editorwidget.h"

#include "separator.h"

#include <QInputDialog>

EditorWidget::EditorWidget(QWidget *parent) :
    QWidget(parent)
  ,m_Layout(NULL)
  ,m_LabelInfoLabel(NULL)
  ,m_LabelFindingType(NULL)
  ,m_SpinBoxLeft(NULL)
  ,m_SpinBoxRight(NULL)
  ,m_SliderThresholdLeft(NULL)
  ,m_SliderThresholdRight(NULL)
  ,m_FrameLabelColor(NULL)
  ,m_ButtonAddToFinding(NULL)
{
    m_IconDefault.addPixmap(QPixmap(":/resources/editor/DefaultTool.png"));
    m_IconDraw.addPixmap(QPixmap(":/resources/editor/Draw.png"));
    m_IconErase.addPixmap(QPixmap(":/resources/editor/EraseLabel.png"));
    m_IconPaint.addPixmap(QPixmap(":/resources/editor/Paint.png"));
    m_IconRedo.addPixmap(QPixmap(":/resources/editor/NextCheckPoint.png"));
    m_IconThreshold.addPixmap(QPixmap(":/resources/editor/Threshold.png"));
    m_IconUndo.addPixmap(QPixmap(":/resources/editor/PreviousCheckPoint.png"));

    this->InitializeWidget();

    this->setDisabled(true);
}

EditorWidget::~EditorWidget()
{
}

void EditorWidget::InitializeWidget()
{
    static bool initialized = false;

    if(initialized == false)
    {
        QHBoxLayout* buttonRowLayout = new QHBoxLayout();
        buttonRowLayout->setMargin(0);
        buttonRowLayout->setSpacing(3);
        buttonRowLayout->addWidget(this->CreateEditorButton(m_IconDefault));
        buttonRowLayout->addWidget(this->CreateEditorButton(m_IconErase));
        buttonRowLayout->addWidget(this->CreateEditorButton(m_IconPaint));
        buttonRowLayout->addWidget(this->CreateEditorButton(m_IconDraw));
        buttonRowLayout->addWidget(this->CreateEditorButton(m_IconThreshold));
        QLabel* undoRedoLabel = new QLabel("Undo/Redo:",this);
        undoRedoLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        buttonRowLayout->addWidget(undoRedoLabel);
        buttonRowLayout->addWidget(this->CreateEditorButton(m_IconUndo, false));
        buttonRowLayout->addWidget(this->CreateEditorButton(m_IconRedo, false));

        buttonRowLayout->setStretch(5,2);

        this->GetLayout()->addLayout(buttonRowLayout,0,0,1,4,Qt::AlignLeft);
        this->GetLayout()->addWidget(this->GetLabelInfoLabel(),1,0,1,1);
        this->GetLayout()->addWidget(this->GetLabelFindingType(),1,1,1,1);
        this->GetLayout()->addWidget(this->GetFrameLabelColor(),1,2,1,2,Qt::AlignRight);

        this->GetLayout()->addWidget(new Separator(this),2,0,1,4);

        this->GetLayout()->addWidget(this->GetSpinBoxLeft(),3,0,1,1);
        this->GetLayout()->addWidget(this->GetSliderThresholdLeft(),3,1,1,1);
        this->GetLayout()->addWidget(this->GetSliderThresholdRight(),3,2,1,1);
        this->GetLayout()->addWidget(this->GetSpinBoxRight(),3,3,1,1);

        this->GetLayout()->addWidget(this->GetButtonAddToFinding(),4,0,1,4);

        this->GetLayout()->setColumnStretch(0,1);
        this->GetLayout()->setColumnStretch(1,2);
        this->GetLayout()->setColumnStretch(2,2);
        this->GetLayout()->setColumnStretch(3,1);

        connect(this->GetSpinBoxLeft(),SIGNAL(valueChanged(int)),this->GetSliderThresholdLeft(),SLOT(setValue(int)));
        connect(this->GetSpinBoxRight(),SIGNAL(valueChanged(int)),this->GetSliderThresholdRight(),SLOT(setValue(int)));
        connect(this->GetSliderThresholdLeft(), SIGNAL(valueChanged(int)), this->GetSpinBoxLeft(),SLOT(setValue(int)));
        connect(this->GetSliderThresholdRight(), SIGNAL(valueChanged(int)), this->GetSpinBoxRight(),SLOT(setValue(int)));

        initialized = true;
    }
}

void EditorWidget::SetLabelColorStyleSheet(const QString& cssColor)
{
    this->GetFrameLabelColor()->setStyleSheet(cssColor);
}

void EditorWidget::SlotAddSegmentationClicked()
{
    QString name = QInputDialog::getText(NULL,"Create Segmentation","Name:");
    name = name.trimmed();

    if(!name.isEmpty())
        emit SignalCreateNewSegmentation(name);
}

QPushButton* EditorWidget::CreateEditorButton(const QIcon& icon, bool enabled)
{
    QPushButton* resultButton = new QPushButton(this);
    resultButton->setFixedSize(32,28);

    resultButton->setIcon(icon);

    connect(resultButton, SIGNAL(clicked()), this, SIGNAL(SignalEditorButtonClicked()) );

    resultButton->setEnabled(enabled);

    return resultButton;
}

void EditorWidget::SetFindingType(const QString& findingType)
{
    this->GetLabelFindingType()->setText(findingType);
}

QGridLayout* EditorWidget::GetLayout()
{
    if(m_Layout == NULL)
    {
        m_Layout = new QGridLayout(this);
    }

    return m_Layout;
}

QLabel* EditorWidget::GetLabelInfoLabel()
{
    if(m_LabelInfoLabel == NULL)
    {
        m_LabelInfoLabel = new QLabel("Label:",this);
    }

    return m_LabelInfoLabel;
}

QLabel* EditorWidget::GetLabelFindingType()
{
    if(m_LabelFindingType == NULL)
    {
        m_LabelFindingType = new QLabel(this);
    }

    return m_LabelFindingType;
}

QSpinBox* EditorWidget::GetSpinBoxLeft()
{
    if(m_SpinBoxLeft == NULL)
    {
        m_SpinBoxLeft = new QSpinBox(this);
        m_SpinBoxLeft->setValue(10);
        m_SpinBoxLeft->setMinimum(0);
        m_SpinBoxLeft->setMaximum(19);
    }

    return m_SpinBoxLeft;
}

QSpinBox* EditorWidget::GetSpinBoxRight()
{
    if(m_SpinBoxRight == NULL)
    {
        m_SpinBoxRight = new QSpinBox(this);
        m_SpinBoxRight->setValue(30);
        m_SpinBoxRight->setMinimum(20);
        m_SpinBoxRight->setMaximum(40);
    }

    return m_SpinBoxRight;
}

QSlider* EditorWidget::GetSliderThresholdLeft()
{
    if(m_SliderThresholdLeft == NULL)
    {
        m_SliderThresholdLeft = new QSlider(Qt::Horizontal,this);
        m_SliderThresholdLeft->setValue(10.0);
        m_SliderThresholdLeft->setMinimum(0);
        m_SliderThresholdLeft->setMaximum(19.9);
    }

    return m_SliderThresholdLeft;
}

QSlider* EditorWidget::GetSliderThresholdRight()
{
    if(m_SliderThresholdRight == NULL)
    {
        m_SliderThresholdRight = new QSlider(Qt::Horizontal,this);
        m_SliderThresholdRight->setValue(30.0);
        m_SliderThresholdRight->setMinimum(20.0);
        m_SliderThresholdRight->setMaximum(40.0);
    }

    return m_SliderThresholdRight;
}

QPushButton* EditorWidget::GetButtonAddToFinding()
{
    if(m_ButtonAddToFinding == NULL)
    {
        m_ButtonAddToFinding = new QPushButton("Add Segmentation to current Finding",this);
        m_ButtonAddToFinding->setFixedHeight(24);

        connect(m_ButtonAddToFinding,SIGNAL(clicked()), this, SLOT(SlotAddSegmentationClicked()));
    }

    return m_ButtonAddToFinding;
}

QFrame* EditorWidget::GetFrameLabelColor()
{
    if(m_FrameLabelColor == NULL)
    {
        m_FrameLabelColor = new QFrame(this);
        m_FrameLabelColor->setFrameStyle(QFrame::Box | QFrame::Sunken);
        m_FrameLabelColor->setFixedSize(100,24);

        m_FrameLabelColor->setStyleSheet("background-color: rgb(10,10,10)");
    }

    return m_FrameLabelColor;
}


void EditorWidget::setDisabled(bool disable)
{
    if(disable)
    {
        this->GetLabelFindingType()->setText("");
        this->GetFrameLabelColor()->setStyleSheet("background-color: rgb(255,255,255)");
    }

    QWidget::setDisabled(disable);
}

void EditorWidget::setEnabled(bool enable)
{
    if(!enable)
    {
        this->GetLabelFindingType()->setText("");
        this->GetFrameLabelColor()->setStyleSheet("background-color: rgb(255,255,255)");
    }

    QWidget::setEnabled(enable);
}

