#ifndef POSTDIALOG_H
#define POSTDIALOG_H
#include "Post.h"
#include "user.h"

#include <QDialog>

namespace Ui {
class PostDialog;
}

class PostDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PostDialog(QWidget *parent = nullptr);
    ~PostDialog();

    void setPost(Post *post);
    void setUser(user *us);

    void uTable(const std::vector<std::string>& vc);

private slots:
    void on_dlBtn_toggled(bool checked);

    void on_likeBtn_toggled(bool checked);

    void on_surBtn_toggled(bool checked);

    void on_laughBtn_toggled(bool checked);

    void on_likeCnt_toggled(bool checked);

    void on_surCnt_toggled(bool checked);

    void on_laughCnt_toggled(bool checked);

    void on_dlCnt_toggled(bool checked);

private:
    Ui::PostDialog *ui;
    Post *p;
    user *u;
};

#endif // POSTDIALOG_H
