#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QTableWidgetItem>
#include "network.h"
#include "user.h"
#include "postdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SocialNetworkWindow; }
QT_END_NAMESPACE

class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr);
    ~SocialNetworkWindow();

    //pre: none
    //post: displays either logged or other user page
    void userProfile();
    void displayPost();


private slots:
    //pre: login btn clicked
    //post: logs user in if valid name given
    void on_logBtn_clicked();

    //pre: none
    //post: navigates to item clicked profile
    void on_frndTbl_itemClicked(QTableWidgetItem *item);

    //pre: currently on other users page
    //post: returns to origional users page
    void on_backBtn_clicked();

    //pre: none
    //post: adds selected recomended friend to logged users friends
    void on_sugTbl_itemDoubleClicked(QTableWidgetItem *item);

    //pre: currently on other users page
    //post: creats connection between other user and logged user
    void on_addBtn_clicked();

    void on_PostTbl_itemDoubleClicked(QTableWidgetItem *item);


    void on_outBtn_clicked();

private:
    Ui::SocialNetworkWindow *ui;
    network *n; // creating pointers for users and netork objects
    user *logged;
    user *other;
    PostDialog *pd;

};
#endif // SOCIALNETWORKWINDOW_H
