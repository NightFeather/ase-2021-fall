#include "attachmentlist.h"
#include "ui_attachmentlist.h"
#include "attachmentwidget.h"

AttachmentList::AttachmentList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttachmentList),
    m_attachments()
{
    ui->setupUi(this);
    connect(this, &AttachmentList::attachmentsChanged, this, &AttachmentList::refresh);
    connect(ui->addAttachment, &QToolButton::clicked, this, &AttachmentList::handleAddBtn);
}

AttachmentList::~AttachmentList()
{
    delete ui;
}

const QList<Attachment *> &AttachmentList::attachments() const
{
    return m_attachments;
}

void AttachmentList::setAttachments(const QList<Attachment *> &newAttachments)
{
    if (m_attachments == newAttachments)
        return;
    m_attachments = newAttachments;
    emit attachmentsChanged();
}

void AttachmentList::handleAddBtn()
{
    addAttachment(new Attachment("unknown"));
}

void AttachmentList::handleDelBtn()
{
    auto w = qobject_cast<AttachmentWidget*>(QObject::sender());
    if(w != nullptr) {
        delAttachment(w->attachment());
    }
}

void AttachmentList::addAttachment(Attachment *newAttachment)
{
    m_attachments.append(newAttachment);
    emit attachmentsChanged();
}

void AttachmentList::delAttachment(Attachment *target)
{
    m_attachments.removeOne(target);
    emit attachmentsChanged();
}

void AttachmentList::refresh()
{
    if(m_attachments.length() > 0) {
        ui->nothing->hide();
        QList<Attachment*> exists;

        for(auto& widget: ui->attachments->findChildren<AttachmentWidget*>()) {
            if(widget != nullptr) {
                if(!m_attachments.contains(widget->attachment())) {
                    ui->attachments->layout()->removeWidget(widget);
                    widget->setParent(nullptr);
                    widget->hide();
                    widget->deleteLater();
                } else {
                    exists.append(widget->attachment());
                }
            }
        }

        for(auto& item: m_attachments) {
            if(!exists.contains(item) && item != nullptr) {
                auto w = new AttachmentWidget(item, this);
                connect(w, &AttachmentWidget::removed, this, &AttachmentList::handleDelBtn);
                ui->attachments->layout()->addWidget(w);
            }
        }
    } else {
        ui->nothing->show();
        for(auto& widget: ui->attachments->findChildren<AttachmentWidget*>()) {
            if(widget != nullptr) {
                ui->attachments->layout()->removeWidget(widget);
                widget->setParent(nullptr);
                widget->hide();
                widget->deleteLater();
            }
        }
    }
}
