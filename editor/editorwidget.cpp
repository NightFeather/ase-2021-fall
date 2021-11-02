#include "editorwidget.h"
#include "ui_editorwidget.h"
#include "attachmentwidget.h"
#include <QMessageBox>
#include <QTimer>

EditorWidget::EditorWidget(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::EditorWidget),
    m_manager(new NoteManager),
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

void EditorWidget::open(QUuid id)
{
    m_note = m_manager.get(id);
    if(m_note == nullptr) {
        QMessageBox::warning(nullptr, "Warning", "Non-existent note");
        if(context()) {
            QTimer::singleShot(0, this, [this]() { context()->backPage(); });
            return;
        } else {
            create();
        }
    }
    emit noteChanged();
}

void EditorWidget::create()
{
    m_note = new Note;
    m_note->setTitle("Created");
    emit noteChanged();
}

void EditorWidget::refresh()
{
    if(m_note != nullptr) {
        readFrom(m_note);
    }
}

void EditorWidget::save()
{
    if(m_note != nullptr) {
        writeTo(m_note);
        m_manager.save(m_note);
    }
    context()->backPage();
}

void EditorWidget::discard()
{
    refresh();
    context()->backPage();
}

void EditorWidget::store()
{
    if(context() != nullptr) {
        auto args = context()->currentPage().args();
        Note note;
        writeTo(&note);
        args.insert("_laststate", QVariant::fromValue(note));
    }
}

void EditorWidget::restore()
{
    if(context() != nullptr) {
        auto args = context()->currentPage().args();
        if(args.contains("_laststate")) {
            auto laststate = args.value("_laststate");
            if(laststate.canConvert<Note>()) {
                readFrom(new Note(laststate.value<Note>()));
            }
        }
    }
}

void EditorWidget::writeTo(Note *note)
{
    note->setTitle(ui->what->text());
    note->setPersons(ui->who->text().split(", "));
    note->setWhen(ui->when->dateTime());
    note->setLocation(ui->where->text());
    note->setAttachments(ui->attachments->attachments());
}

void EditorWidget::readFrom(Note *note)
{
    ui->what->setText(note->title());
    ui->who->setText(note->persons().join(", "));
    ui->when->setDateTime(note->when());
    ui->where->setText(note->location());
    ui->attachments->setAttachments(note->attachments());
}

bool EditorWidget::handle(const QHash<QString, QVariant> &args)
{
    if(args.value("action") == "new") {
        create();
        return true;
    } else if (args.value("action") == "open") {
        open(args.value("id", QUuid()).toUuid());
        return true;
    } else {
        return false;
    }
}
