#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
{
    ui->setupUi(this);
    n = new network(); //initializing network
    other = nullptr; // setting as nullptr
    logged = nullptr; // setting as nullptr until logged in
    int i = n->readUsers("/Users/home/Desktop/cpp62/Social5/social.txt"); // reading users into network, note name of file is social.txt
    n->readPosts("Aled Montes", "/Users/home/Desktop/cpp62/Social5/posts.txt"); // reading for 2 users for example
    n->readPosts("Xian Liang", "/Users/home/Desktop/cpp62/Social5/posts.txt");
    ui->pfLog->hide(); // hiding all other ui features except login page
    ui->frndTbl->hide();
    ui->PostTbl->hide();
    ui->backBtn->hide();
    ui->sugTbl->hide();
    ui->addBtn->hide();
    ui->outBtn->hide();

    //connect(ui->frndTbl, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(on_frndTbl_itemClicked(QTableWidgetItem*)));


}

SocialNetworkWindow::~SocialNetworkWindow()
{
    delete ui;
}


void SocialNetworkWindow::on_logBtn_clicked()
{
    QString mStr = ui->logEdit->toPlainText();
    std::string temp = mStr.toStdString();
    int tId = n->getId(temp);

    if(tId == -1) // checks to see valid user is entered
    {
        ui->nameLbl->setText("User Not Found,\n Please enter a valid user name"); // requests for re-entry
        ui->logEdit->clear();
    }
    else
    {
        logged = n->getUser(tId);
        ui->nameLbl->hide(); // hides login page
        ui->logEdit->hide();
        ui->logBtn->hide();
        userProfile();
    }

}

void SocialNetworkWindow::userProfile() // page display method
{
    ui->pfLog->show(); // displays profile information
    ui->frndTbl->show();
    ui->PostTbl->show();
    ui->PostTbl->setRowCount(0);
    if(other == nullptr || logged == other) // checks to see if currently in logged-in user
    {
        ui->outBtn->show();
        ui->backBtn->hide();// hides other user page details
        ui->addBtn->hide();
        ui->pfLog->setText("My Profile");
        std::vector<std::size_t> fV = logged->getFriends();
        ui->frndTbl->setRowCount(fV.size());
        ui->frndTbl->setColumnCount(1);
        ui->frndTbl->setColumnWidth(0,325);
        for(int i = 0; i< fV.size(); i++) // populates table of friends
        {
            user* temp = n->getUser(fV[i]);
            ui->frndTbl->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(temp->getName())));
        }
        //ui->postLbl->setText("Recent Posts: \n\n" + QString::fromStdString(n->displayPosts(logged->getName(), 5, false))); // displays posts, All posts since logged user
        std::vector<Post*> pS = logged->getPosts();
        if(pS.size() > 0)
        {
            //ui->PostTbl->setRowCount(pS.size());
            ui->PostTbl->setRowCount(5);
            ui->PostTbl->setColumnCount(1);
            ui->PostTbl->setColumnWidth(0,400);

            //for(int i = 0; i< pS.size(); i++) // shows suggested users/friends in sepperate table
            for(int i = pS.size()-1; i > pS.size()-6; i--)
            {
                Post* temp = pS[i];
                logged->addRecPost(temp);
                ui->PostTbl->setItem(pS.size()-i-1, 0, new QTableWidgetItem(QString::fromStdString(temp->getMessage())));
            }
        }


        int id = logged->getId();
        size_t hs = 0;
        std::vector<std::size_t> rec = n->suggestFriends(id, hs); //gets suggested friends
        ui->sugTbl->setRowCount(rec.size());
        ui->sugTbl->setColumnCount(1);
        ui->sugTbl->show();


        for(int i = 0; i< rec.size(); i++) // shows suggested users/friends in sepperate table
        {
            user* temp = n->getUser(rec[i]);
            ui->sugTbl->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(temp->getName())));
        }

    }
    else if(other != logged && other != nullptr) // if current user is not loggedin user
    {
        ui->outBtn->hide();
        ui->sugTbl->hide();
        ui->pfLog->setText(QString::fromStdString(other->getName()) + "'s Profile"); // display details of other user

        std::vector<Post*> pS = other->getPosts();
        if(pS.size() > 0)
        {

            ui->PostTbl->setRowCount(5);
            ui->PostTbl->setColumnCount(1);
            ui->PostTbl->setColumnWidth(0,400);

            int count = 0;
            int i = pS.size()-1;
            while(count < 5)
            {
                Post* temp = pS[i];
                std::string newStr = temp->displayPost();
                if(newStr[7] == ':') // checks if post is pUblic
                {
                    other->addPub(temp);
                    ui->PostTbl->setItem(count, 0, new QTableWidgetItem(QString::fromStdString(newStr)));
                    count++;
                }
                i--;
            }
        }



        ui->backBtn->show(); // shows buttun to return to logges user
        ui->addBtn->show();// shows buttun to add this user as friend

        std::vector<std::size_t> fV = other->getFriends();//table for other user
        ui->frndTbl->setRowCount(fV.size());
        ui->frndTbl->setColumnCount(1);
        for(int i = 0; i< fV.size(); i++) // populates table of friends
        {
            user* temp = n->getUser(fV[i]);
            ui->frndTbl->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(temp->getName())));
        }

    }
}

void SocialNetworkWindow :: displayPost()
{
    ui->frndTbl->hide();
    ui->PostTbl->hide();
    ui->backBtn->hide();
    ui->sugTbl->hide();
    ui->addBtn->hide();
    ui->pfLog->hide();



}


void SocialNetworkWindow::on_frndTbl_itemClicked(QTableWidgetItem *item) //When a friend is clicked
{
    QString iName = item->text();
    int i = n->getId(iName.toStdString());
    other = n->getUser(i); // sets other user pointer to selected user
    ui->pfLog->hide(); // hides current (logged) page details
    ui->frndTbl->hide();
    ui->PostTbl->hide();
    userProfile(); // calls page display method again
}


void SocialNetworkWindow::on_backBtn_clicked()
{
    other = nullptr; // sets other to a nullptr
    ui->pfLog->hide(); // hides page details
    ui->frndTbl->hide();
    ui->PostTbl->hide();
    ui->backBtn->hide();
    userProfile(); // calls page display method again to return to logged user page
}


void SocialNetworkWindow::on_sugTbl_itemDoubleClicked(QTableWidgetItem *item)
{
    QString iName = item->text();
    n->addConnection(logged->getName(), iName.toStdString());
    userProfile(); // refreshes page with new friend in list and gives new recommendations
}



void SocialNetworkWindow::on_addBtn_clicked()
{
    n->addConnection(logged->getName(), other->getName()); // adds other to logged as friend
    userProfile();
}


//opens postdialog in sepperate window
void SocialNetworkWindow::on_PostTbl_itemDoubleClicked(QTableWidgetItem *item)
{
    int i = ui->PostTbl->currentRow();

    if(other == nullptr || logged == other) // checks to see if currently in logged-in user
    {
        std::vector<Post*> pS = logged->getRecPosts();
        Post *selectedPost = pS[i];

        pd = new PostDialog(this); // created instance of post window
        pd->setUser(logged);
        pd->setPost(selectedPost);
        pd->show();


    }
    else if(other != logged && other != nullptr) // if current user is not loggedin user
    {
        std::vector<Post*> pS = other->getPub();

        Post *selectedPost = pS[i];

        pd = new PostDialog(this);
        pd->setUser(logged);
        pd->setPost(selectedPost);
        pd->show();

    }

}



//sends user back to log in page
void SocialNetworkWindow::on_outBtn_clicked()
{
    if (other != nullptr)
    {
        other->getRecPosts().clear();
    }

    if (logged != nullptr)
    {
        logged->getRecPosts().clear();
    }

    other = nullptr;
    logged = nullptr;
    ui->pfLog->hide();
    ui->frndTbl->hide();
    ui->PostTbl->hide();
    ui->backBtn->hide();
    ui->sugTbl->hide();
    ui->addBtn->hide();
    ui->outBtn->hide();

    ui->nameLbl->setText("Enter your name:");
    ui->nameLbl->show(); // hides login page
    ui->logEdit->clear();
    ui->logEdit->show();
    ui->logBtn->show();



}

