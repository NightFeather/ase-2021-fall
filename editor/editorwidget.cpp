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
    ui->when->setDateTime(QDateTime::currentDateTime());
    connect(this, &EditorWidget::noteChanged, this, &EditorWidget::refresh);
    connect(ui->save, &QPushButton::clicked, this, &EditorWidget::save);
    connect(ui->discard, &QPushButton::clicked, this, &EditorWidget::discard);
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

void EditorWidget::refresh()
{
    if(m_note != nullptr) {
        ui->what->setText(m_note->title());
        ui->who->setText(m_note->persons().join(", "));
        ui->when->setDateTime(m_note->timestamp());
        ui->where->setText(m_note->location());
        ui->attachments->setAttachments(m_note->attachments());
    }
}

void EditorWidget::save()
{
    if(m_note != nullptr) {
        m_note->setTitle(ui->what->text());
        m_note->setPersons(ui->who->text().split(", "));
        m_note->setTimestamp(ui->when->dateTime());
        m_note->setLocation(ui->where->text());
        m_note->setAttachments(ui->attachments->attachments());
    }
}

void EditorWidget::discard()
{
    refresh();
}

