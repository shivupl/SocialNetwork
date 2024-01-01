#include "IncomingPost.h"


IncomingPost :: IncomingPost() : Post(), isPublic_(false) {}

IncomingPost::IncomingPost(std::size_t id, std::string msg, std::size_t likes, std::string auth, bool pub) : Post(id, msg + " From: " + auth, likes), isPublic_(pub), author_(auth) {}


std::string IncomingPost :: displayPost()
{
	std::string set; 
	if(isPublic_) // checking if post is public
	{
		set = "Public :" ;
		return set + Post::displayPost();
	}
	else
	{
		set = "Private :" ;
		return set + Post::displayPost();
	}
}
