#include <iostream>
#include <vector>

#ifndef POST_H
#define POST_H


class Post { 
public:

    Post() {}
    Post(std::size_t id, std::string msg, std::size_t likes);


    //pre: none
    //post: displays post information
    virtual std::string displayPost();

    //pre: none
    //post: returns user ID of post
    std::size_t getId();

    //pre: none
    //post: returns post message
    std::string getMessage();

    //pre: none
    //post: returns no. of likes on post
    std::size_t getLikes();

    //pre: none
    //post: adds s to respective vector, returns true if successful
    bool addLike(std::string s);
    bool addDislike(std::string s);
    bool addLaugh(std::string s);
    bool addSurprise(std::string s);

    //pre: nonde
    //post: adds s from respective vector
    void removeLike(std::string s);
    void removeDl(std::string s);
    void removeLaugh(std::string s);
    void removeSurprise(std::string s);


    //pre: nonde
    //post: returns respective vector
    std::vector<std::string> getLikesVec();
    std::vector<std::string> getDislikes();
    std::vector<std::string> getLaughs();
    std::vector<std::string> getSurprises();


private:
    std::size_t id_;
    std::string message_;
    std::size_t likes_;
    std::vector<std::string> likes;
    std::vector<std::string> dislikes;
    std::vector<std::string> laugh;
    std::vector<std::string> surprise;




};

#endif
