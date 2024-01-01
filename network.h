#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include<queue>
#include <algorithm>
#include <unordered_map>
#include "user.h"

#ifndef NETWORK_H
#define NETWORK_H

class network{ 
public:

	//CONSTRUCTOR    
    //pre: none
    //post: creates a default network object
	network() {}


    //pre: none
    //post: deletes a network object and clears all associated memory
    ~network();
	

	//pre: none
	//post:
	void addUser(user* u);

	//pre: names exist in network
	//post: creates connection between 2 names, returns -1 if unsuccessful 
	int addConnection(std::string s1, std::string s2);

	//pre: names exist in network
	//post: removes connection between 2 names, returns -1 if unsuccessful 
	int removeConnection(std::string s1, std::string s2);


	//pre: none
    //post: returns user ID, -1 if not found
    std::size_t getId(std::string name);

	//pre: none
	//post: reads user data from file into network object, returns -1 if not found
	int readUsers(const char* fname);

	//pre: none
	//post: writes user data from network object onto file,returns -1 unsuccessful
	int writeUsers(const char *fname);

	//pre: none
	//post: number of users in network
	std::size_t numUsers() { return users_.size(); }

	//pre: none
	//post: returns user object 
	user* getUser(std::size_t id);

	//pre: none
	//post: returns shortest path between given user Ids
	std::vector<std::size_t> shortestPath(std::size_t from, std::size_t to);

	//pre: none
	//post: returns  path between given user Ids using given distance
	std::vector<std::size_t> distanceUser(std::size_t from, std::size_t& to, std::size_t distance);

	//pre: none
	//post: 
	std::vector<std::size_t> suggestFriends(std::size_t who, std::size_t& score);


	//pre: none
	//post: returns a vector of vectors of users in each set
	std::vector<std::vector<std::size_t>> groups();

	//pre: called from groups method with valid parameters
	//post: conducts a DFS on the given id friends
    void DFS(std::size_t id, std::vector<bool>& visited, std::vector<std::size_t>& curr);

    //pre: none
    //post: adds post to given user ID 
	void addPost(std::size_t ownerId, std::string message, std::size_t likes, bool incoming, std::size_t author, bool isPublic);

    //pre: none
    //post: calls displayPosts method of given user
	std::string displayPosts(std::string name, std::size_t howMany, bool showOnlyPublic);

	//pre: given valid filename
    //post: reads all post information from file into respective user object
	int readPosts(std::string name, const char* fname);

private:
	std::vector<user*> users_;

};

#endif

