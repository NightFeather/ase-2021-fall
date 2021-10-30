#include "attachmentwidget.h"
#include "ui_attachmentwidget.h"

AttachmentWidget::AttachmentWidget(Attachment *item, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttachmentWidget),
    m_attachment(item)
{
    ui->setupUi(this);
    ui->title->setText(item->title());
    ui->preview->setVisible(item->hasPreview());
    ui->edit->setVisible(item->editable());

    if(item->hasPreview()){
        ui->preview->setPixmap((*item->preview()).scaledToHeight(ui->preview->height()));
    }

    connect(ui->edit, &QPushButton::clicked, this, &AttachmentWidget::edit);
    connect(ui->remove, &QPushButton::clicked, this, &AttachmentWidget::remove);
}

AttachmentWidget::~AttachmentWidget()
{
    delete ui;
}

void AttachmentWidget::remove()
{
    emit removed();
}

void AttachmentWidget::edit()
{
    emit edited();
}

Attachment *AttachmentWidget::attachment() const
{
    return m_attachment;
}

void AttachmentWidget::setAttachment(Attachment *newAttachment)
{
    m_attachment = newAttachment;
}
