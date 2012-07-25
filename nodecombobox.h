#ifndef NODECOMBOBOX_H
#define NODECOMBOBOX_H

#include <QComboBox>

class NodeComboBox : public QComboBox
{
    Q_OBJECT
public:

    enum Operator
    {
        CREATE,
        RENAME,
        DELETE,
        SEPPARATOR
    };

    explicit NodeComboBox(const QString& description, QList<QString>* values, QWidget*parent = 0);
    ~NodeComboBox();

    void HideOperator(Operator op);

    void SetCurrentIndex(const QString& text);

    static QString NONE_VALUE;

signals:
    void SignalCreate();
    void SignalSelected(const QString& name);
    void SignalRename(const QString& name);
    void SignalDelete(const QString& name);
    
public slots:
    void Update(const QString& indexAtText = "");

protected slots:
    void SlotSelectionChanged(const QString& selected);

protected:
    bool IsSelectedEntryNode(const QString& name);


private:

    QList<QString>* m_Values;
    QString m_Description;

    QList<QString> m_DefaultValues;


    QString m_StringCreate;
    QString m_StringRename;
    QString m_StringDelete;
    QString m_StringSeparator;

    QString m_LastSelectedNode;
};

#endif // NODECOMBOBOX_H
