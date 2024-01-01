#include <iostream>
#include <vector>
#include "Post.h"

#ifndef INCOMINGPOST_H
#define INCOMINGPOST_H

class IncomingPost: public Post {
public:

	IncomingPost();
	IncomingPost(std::size_t id, std::string msg, std::size_t likes, std::string auth, bool pub);

    //pre: none
    //post: returns post information of incoming post
	std::string displayPost();

private:
	bool isPublic_;
	std::string author_;


};

#endif
