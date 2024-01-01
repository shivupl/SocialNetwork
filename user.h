#include <iostream>
#include <vector>
#include "Post.h"
#include "IncomingPost.h"



#ifndef USER_H
#define USER_H


class user { 
public:

	//CONSTRUCTORS

	//pre: none
	//post: user is initialized with given values
    user(std::size_t id, std::string name, std::size_t year, std::size_t zip, std::vector<std::size_t> friends);

    //pre: none
	//post: user is initialized with default values
    user();


    //pre: given id is a size_t
    //post: friend is added to vector
    void addFriend(std::size_t id);

    //pre: friend ID given exists
    //post: fried ID is erased from list/vector
    void deleteFriend(std::size_t id); 


    //pre: none
    //post: returns user ID
    std::size_t getId() const { return id_; }

    //pre: none
    //post: returns user year of birth
    std::size_t getYear() const { return year_; }

    //pre: none
    //post: returns user Zip code
    std::size_t getZip() const { return zip_; }

    //pre: none
    //post: returns user name
    std::string getName() const { return name_; }

    //pre: none
    //post: returns vector of users friends
    std::vector<std::size_t> getFriends() const { return friends_; }

    //pre: none
    //post: adds post to messages_ vector
    void addPost(Post* p);

    //pre: none
    //post: displays 'howMany' number of recent posts
    std::string displayPosts(std::size_t howMany, bool showOnlyPublic);

    //pre: none
    //post: returns vector of posts(messages)
    std::vector<Post*> getPosts();

    //pre: none
    //post: adds post to recPosts_ vector
    void addRecPost(Post* p);

    //pre: none
    //post: adds post to pubPosts_ vector
    void addPub(Post* p);

    //pre: none
    //post: returns pubPosts_ vector
    std::vector<Post*> getPub();


    //pre: none
    //post: returns vector of recent posts(recPosts_)
    std::vector<Post*> getRecPosts();


private:
    std::size_t id_;
    std::string name_;
    std::size_t year_;
    std::size_t zip_;
    std::vector<std::size_t> friends_;
    std::vector<Post*> messages_;
    std::vector<Post*> recPosts_;
    std::vector<Post*> pubPosts_;
};

#endif
