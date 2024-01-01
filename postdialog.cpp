#include "postdialog.h"
#include "ui_postdialog.h"

PostDialog::PostDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PostDialog)
{
    ui->setupUi(this);
    ui->reactTbl->hide();

    //setting each toggle button as checkable
    ui->dlBtn->setCheckable(true);
    ui->likeBtn->setCheckable(true);
    ui->surBtn->setCheckable(true);
    ui->laughBtn->setCheckable(true);

    ui->likeCnt->setCheckable(true);
    ui->surCnt->setCheckable(true);
    ui->laughCnt->setCheckable(true);
    ui->dlCnt->setCheckable(true);

    ui->likeCnt->setChecked(false);


}

PostDialog::~PostDialog()
{
    delete ui;
}


//seting *p pointer to post from mainclass
void PostDialog::setPost(Post *post)
{
    this->p = post;
    std::string newStr = p->displayPost();

    //displaying post message
    ui->FdLbl->setText(QString::fromStdString(newStr));

    //setting each count button each time window opened
    QString temp = QString::number(p->getLikesVec().size());
    ui->likeCnt->setText(temp);

    temp = QString::number(p->getSurprises().size());
    ui->surCnt->setText(temp);

    temp = QString::number(p->getLaughs().size());
    ui->laughCnt->setText(temp);

    temp = QString::number(p->getDislikes().size());
    ui->dlCnt->setText(temp);


    //checking if user reacted, if so toggle respective button
    //
    //like
    if(!p->addLike(u->getName()))
    {
        ui->likeBtn->setChecked(true);

    }
    else
    {
        ui->likeBtn->setChecked(false);
        p->removeLike(u->getName());
    }

    //dl
    if(!p->addDislike(u->getName()))
    {
        ui->dlBtn->setChecked(true);

    }
    else
    {
        ui->dlBtn->setChecked(false);
        p->removeDl(u->getName());
    }

    //surprise
    if(!p->addSurprise(u->getName()))
    {
        ui->surBtn->setChecked(true);

    }
    else
    {
        ui->surBtn->setChecked(false);
        p->removeSurprise(u->getName());
    }

    //laugh
    if(!p->addLaugh(u->getName()))
    {
        ui->laughBtn->setChecked(true);

    }
    else
    {
        ui->laughBtn->setChecked(false);
        p->removeLaugh(u->getName());
    }

}

//setting *u pointer to user obj passed from socialwindow
void PostDialog::setUser(user *us)
{
    this->u = us;

}


//function to display table of users depending on reaction vector passed
void PostDialog :: uTable(const std::vector<std::string>& vc)
{
    ui->reactTbl->clearContents();
    ui->reactTbl->setColumnCount(1);
    ui->reactTbl->setColumnWidth(0,258);
    ui->reactTbl->setRowCount(vc.size());
    for(int i = 0; i < vc.size(); i++)
    {
        //std::cout << vc[i];
        ui->reactTbl->setItem(i,0,new QTableWidgetItem(QString::fromStdString(vc[i])));
    }
}



//Buttons for each reaciton:

//like
//if like button clicked
void PostDialog::on_likeBtn_toggled(bool checked)
{
    if(checked) //if toggled on
    {
        p->addLike(u->getName());
        ui->dlBtn->setCheckable(false); // preventing users from using other reactions while currently liked
        ui->laughBtn->setCheckable(false);
        ui->surBtn->setCheckable(false);
        ui->likeBtn->setChecked(true);
    }
    else if(!checked) //toggled off
    {
        ui->dlBtn->setCheckable(true);
        ui->laughBtn->setCheckable(true);
        ui->surBtn->setCheckable(true);
        p->removeLike(u->getName());
    }
    QString temp = QString::number(p->getLikesVec().size());
    ui->likeCnt->setText(temp); // updates the like count button
    uTable(p->getLikesVec());

}


//toggle count button and display/hide table of reacted users
void PostDialog::on_likeCnt_toggled(bool checked)
{
    if(checked)
    {
        uTable(p->getLikesVec());
        ui->dlCnt->setChecked(false);
        ui->surCnt->setChecked(false);
        ui->laughCnt->setChecked(false);
        ui->reactTbl->show();
\
    }
    else if(!checked)
    {
        ui->reactTbl->hide();
    }
}


//surprise

void PostDialog::on_surBtn_toggled(bool checked)
{
    if(checked)
    {
        p->addSurprise(u->getName());

        ui->dlBtn->setCheckable(false);
        ui->laughBtn->setCheckable(false);
        ui->likeBtn->setCheckable(false);
    }
    else if(!checked)
    {
        p->removeSurprise(u->getName());

        ui->dlBtn->setCheckable(true);
        ui->laughBtn->setCheckable(true);
        ui->likeBtn->setCheckable(true);
    }
    QString temp = QString::number(p->getSurprises().size());
    ui->surCnt->setText(temp);
    uTable(p->getSurprises());
}

void PostDialog::on_surCnt_toggled(bool checked)
{
    if(checked)
    {
        uTable(p->getSurprises());
        ui->dlCnt->setChecked(false);
        ui->likeCnt->setChecked(false);
        ui->laughCnt->setChecked(false);
        ui->reactTbl->show();
    }
    else if(!checked)
    {
        ui->reactTbl->hide();
    }
}

//laugh

void PostDialog::on_laughBtn_toggled(bool checked)
{
    if(checked)
    {
        p->addLaugh(u->getName());

        ui->dlBtn->setCheckable(false);
        ui->surBtn->setCheckable(false);
        ui->likeBtn->setCheckable(false);
    }
    else if(!checked)
    {
        p->removeLaugh(u->getName());

        ui->dlBtn->setCheckable(true);
        ui->surBtn->setCheckable(true);
        ui->likeBtn->setCheckable(true);
    }
    QString temp = QString::number(p->getLaughs().size());
    ui->laughCnt->setText(temp);
    uTable(p->getLaughs());
}


void PostDialog::on_laughCnt_toggled(bool checked)
{
    if(checked)
    {
        uTable(p->getLaughs());
        ui->dlCnt->setChecked(false);
        ui->surCnt->setChecked(false);
        ui->likeCnt->setChecked(false);
        ui->reactTbl->show();
    }
    else if(!checked)
    {
        ui->reactTbl->hide();
    }
}


//dislike

void PostDialog::on_dlBtn_toggled(bool checked)
{
    if(checked)
    {
        p->addDislike(u->getName());
        ui->likeBtn->setCheckable(false);
        ui->surBtn->setCheckable(false);
        ui->laughBtn->setCheckable(false);
    }
    else if(!checked)
    {
        p->removeDl(u->getName());
        ui->likeBtn->setCheckable(true);
        ui->surBtn->setCheckable(true);
        ui->laughBtn->setCheckable(true);
    }
    QString temp = QString::number(p->getDislikes().size());
    ui->dlCnt->setText(temp);
    uTable(p->getDislikes());
}

void PostDialog::on_dlCnt_toggled(bool checked)
{
    if(checked)
    {
        uTable(p->getDislikes());
        ui->likeCnt->setChecked(false);
        ui->surCnt->setChecked(false);
        ui->laughCnt->setChecked(false);
        ui->reactTbl->show();
    }
    else if(!checked)
    {
        ui->reactTbl->hide();
    }
}

















