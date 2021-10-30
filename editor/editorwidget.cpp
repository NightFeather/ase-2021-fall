#include "editorwidget.h"
#include "ui_editorwidget.h"
#include "attachmentwidget.h"
#include <QMessageBox>

EditorWidget::EditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorWidget),
    m_note(nullptr)
{
    ui->setupUi(this);
    connect(this, &EditorWidget::noteChanged, this, &EditorWidget::showNote);
    setNote(new Note);
}

EditorWidget::~EditorWidget()
{
    delete ui;
}

Note *EditorWidget::note() const
{
    return m_note;
}

void EditorWidget::setNote(Note *newNote)
{
    if (m_note == newNote)
        return;
    delete m_note;
    m_note = newNote;
    emit noteChanged();
}

void EditorWidget::showNote()
{
    ui->what->setText(m_note->title());
    ui->who->setText(m_note->persons().join(", "));
    ui->when->setText(m_note->timestamp().toString());
    ui->where->setText(m_note->location());
}

void EditorWidget::refresh()
{

}

void EditorWidget::save()
{

}

void EditorWidget::discard()
{

}

