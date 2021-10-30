#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include <datatypes/note.h>

namespace Ui {
class EditorWidget;
}

class EditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditorWidget(QWidget *parent = nullptr);
    ~EditorWidget();

    Note *note() const;
    void setNote(Note *newNote);

public slots:
    void refresh();
    void save();
    void discard();

signals:
    void noteChanged();

private:
    Ui::EditorWidget *ui;
    Note* m_note;
};

#endif // EDITORWIDGET_H
