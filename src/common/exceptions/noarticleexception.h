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

#endif
