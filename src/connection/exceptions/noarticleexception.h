/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** noarticleexception.h
**
** Exception to be thrown when the client tries to access a non-existant
** article.
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef ARTICLE_DOES_NOT_EXIST_EXCEPTION_H
#define ARTICLE_DOES_NOT_EXIST_EXCEPTION_H
#include <string>

struct ArticleDoesNotExistException {
	ArticleDoesNotExistException(std::string ngId, std::string aId) {
		msg = "The article with id " + aId + " in newsgroup "
				+ ngId + " does not exist.";
	}
	std::string msg;
};

#endif // ARTICLE_DOES_NOT_EXIST_EXCEPTION_H
