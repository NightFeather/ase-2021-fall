#ifndef ATTACHMENTWIDGET_H
#define ATTACHMENTWIDGET_H

#include <QWidget>
#include <datatypes/attachment.h>

namespace Ui {
class AttachmentWidget;
}

class AttachmentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AttachmentWidget(Attachment*, QWidget *parent = nullptr);
    ~AttachmentWidget();

    Attachment *attachment() const;
    void setAttachment(Attachment *newAttachment);

public slots:
    virtual void remove();
    virtual void edit();

signals:
    void edited();
    void removed();

private:
    Ui::AttachmentWidget *ui;
    Attachment* m_attachment;
};

#endif // ATTACHMENTWIDGET_H
