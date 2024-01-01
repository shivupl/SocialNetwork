#include "user.h"

user :: user(std::size_t id, std::string name, std::size_t year, std::size_t zip, std::vector<std::size_t> friends) :
    id_(id), name_(name), year_(year), zip_(zip), friends_(friends) {}

user :: user() : id_(0), year_(0), zip_(0) {}

void user :: addFriend(std::size_t id)
{
    bool e = false;
    for(int i = 0; i < friends_.size(); i++)
    {
        if(friends_[i] == id)
        {
            e = true;
        }
    }
    if(!e)
    {
        friends_.push_back(id);
    }
}


void user :: deleteFriend(std::size_t id)
{
    for (auto it = friends_.begin(); it != friends_.end(); it++)
    {
        if (*it == id)
        {
            friends_.erase(it);
            break;
        }
    }

}

void user :: addPost(Post* p)
{
    messages_.push_back(p);
}


std::string user :: displayPosts(std::size_t howMany, bool showOnlyPublic)
{
    std::string ret;

    if(howMany < messages_.size()) //checks to see that there is atleast howMant no. of posts
    {
        int count = 0;
        for(int i = messages_.size()-1; i > 0; i--) // loops backwards, from most recent
        {
            Post *temp = messages_[i];
            if(count == howMany){
                break;
            }
            if(showOnlyPublic == true) // checks to show public/private status posts
            {
                std::string newStr = temp->displayPost();
                if(newStr[7] == ':') // checks if post is pUblic
                {
                    std::string st = temp->displayPost();
                    ret += st;
                    ret += "\n\n";
                    count++;
                }
            }
            else
            {
                std::string st = temp->displayPost();
                ret += st;
                ret += "\n\n";
                count++;
            }

        }
    }

    return ret;
}

std::vector<Post*> user :: getPosts()
{
    return messages_;
}

std::vector<Post*> user :: getRecPosts()
{
    return recPosts_;
}

void user :: addRecPost(Post* p)
{
    recPosts_.push_back(p);
}

void user :: addPub(Post* p)
{
    pubPosts_.push_back(p);
}

std::vector<Post*> user :: getPub()
{
    return pubPosts_;
}
