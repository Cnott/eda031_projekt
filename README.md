##Projekt for the course EDA031 at Lunds University, spring 2016

This is a system that consists of a server that can handle data in the form of
newsgroups and articles (a simple version of the old Usenet system).

There are two different versions of the server, a cached memory-server and a
persistent disk-server.

There is also a terminal based client that can perform the basic commands
needed to handle the database. The commands for the client can bee seen below.
```
list						Lists newsgroups on server.
list x:						Lists articles on newsgroup number x.
get x y:					Retrieves article y from newsgroup x.
create newsgroup x:			Creates new newsgroup with name x.
create article x path:		Creates new article in newsgroup x from the content
							of the file specified. The file should have title
							on the first row followed by the author on the
							second and the text content on the remaining.
delete newsgroup x:			Deletes newsgroup x.
delete article x y:			Deletes article y from newsgroup x.
```
The servers should be run as follows:
```
  bin/newsserver_memory <port>
  bin/newsserver_disk <port>
```
and the client:
```
  bin/client <host> <port>
```
There is a folder with two example articles that can be added according to the
commands above. Ex:
```
  create article 1 /articles/article.txt
```
