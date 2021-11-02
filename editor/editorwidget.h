#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include <navigate/pagewidget.h>
#include <datatypes/note.h>
#include <storage/notemanager.h>

namespace Ui {
class EditorWidget;
}

class EditorWidget : public PageWidget
{
    Q_OBJECT

public:
    explicit EditorWidget(QWidget *parent = nullptr);
    ~EditorWidget();

    void open(QUuid);
    void create();

public slots:
    void refresh();
    void save();
    void discard();

protected:
    void store();
    void restore();
    void writeTo(Note*);
    void readFrom(Note*);

signals:
    void noteChanged();

private:
    Ui::EditorWidget *ui;
    NoteManager m_manager;
    Note* m_note;

    // PageWidget interface
public:
    virtual bool handle(const QHash<QString, QVariant> &) override;
};

#endif // EDITORWIDGET_H
