#ifndef ATTACHMENTLIST_H
#define ATTACHMENTLIST_H

#include <QWidget>
#include <datatypes/attachment.h>

namespace Ui {
class AttachmentList;
}

class AttachmentList : public QWidget
{
    Q_OBJECT

public:
    explicit AttachmentList(QWidget *parent = nullptr);
    ~AttachmentList();

    const QList<Attachment *> &attachments() const;
    void setAttachments(const QList<Attachment *> &newAttachments);

public slots:
    void handleAddBtn();
    void handleDelBtn();
    void addAttachment(Attachment*);
    void delAttachment(Attachment*);
    void refresh();

signals:
    void attachmentsChanged();

private:
    Ui::AttachmentList *ui;
    QList<Attachment*> m_attachments;
};

#endif // ATTACHMENTLIST_H
