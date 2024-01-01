#include "Post.h"

Post :: Post(std::size_t id, std::string msg, std::size_t likes) : id_(id), message_(msg), likes_(likes) {}

std::string Post :: displayPost()
{
    std::string ret = message_; //+ '\n' + "Liked by " + std::to_string(likes_) + " people" + '\n';
    return ret;
}

std::size_t Post :: getId()
{
    return id_;
}

std::string Post :: getMessage()
{
    return message_;
}

std::size_t Post :: getLikes()
{
    return likes_;
}

//new getter methods
std::vector<std::string> Post :: getLikesVec()
{
    return likes;
}
std::vector<std::string> Post :: getDislikes()
{
    return dislikes;
}

std::vector<std::string> Post :: getLaughs()
{
    return laugh;
}

std::vector<std::string> Post :: getSurprises()
{
    return surprise;
}

//add reactions

bool Post :: addLike(std::string s)
{
    if (std::find(likes.begin(), likes.end(), s) == likes.end()) // checks to see s isnt already in vector
    {
        likes.push_back(s);
        return true;
    }
    return false;
}
bool Post :: addDislike(std::string s)
{
    if (std::find(dislikes.begin(), dislikes.end(), s) == dislikes.end())
    {
        dislikes.push_back(s);
        return true;
    }
    return false;
}
bool Post :: addLaugh(std::string s)
{
    if (std::find(laugh.begin(), laugh.end(), s) == laugh.end())
    {
        laugh.push_back(s);
        return true;
    }
    return false;

}
bool Post :: addSurprise(std::string s)
{
    if (std::find(surprise.begin(), surprise.end(), s) == surprise.end())
    {
        surprise.push_back(s);
        return true;
    }
    return false;
}



//remove methods
void Post :: removeLike(std::string s)
{
    for (int i = 0; i < likes.size(); i++)
    {
        if (likes[i] == s)
        {
            likes.erase(likes.begin() + i);
            break;
        }
    }

}
void Post :: removeLaugh(std::string s)
{
    for (int i = 0; i < laugh.size(); i++)
    {
        if (laugh[i] == s)
        {
            laugh.erase(laugh.begin() + i);
            break;
        }
    }

}
void Post :: removeSurprise(std::string s)
{
    for (int i = 0; i < surprise.size(); i++)
    {
        if (surprise[i] == s)
        {
            surprise.erase(surprise.begin() + i);
            break;
        }
    }

}

void Post :: removeDl(std::string s)
{
    for (int i = 0; i < dislikes.size(); i++)
    {
        if (dislikes[i] == s)
        {
            dislikes.erase(dislikes.begin() + i);
            break;
        }
    }
}


