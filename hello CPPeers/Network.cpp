/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;

Network::Network() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {
  // TODO(student): load user and post information from file
  string userOrPost;
  string nameFromFile;
  unsigned int idFromFile;
  string postInfo;
  std::ifstream fin(fileName);
  if (!fin.good()) {
    throw std::invalid_argument("loadFromFile: invalid parameter values");
  }
  fin >> userOrPost;
  while (true) {
    if (userOrPost == "User") {
      getline(fin, nameFromFile);
      nameFromFile.erase(0,1);
      try {
        (*this).addUser(nameFromFile);
      }
      catch (std::invalid_argument& e) {
        throw std::runtime_error("loadFromFile: userName from User invalid");
      }
    }
    else if (userOrPost == "Post") {
      fin >> idFromFile >> nameFromFile;
      getline(fin, postInfo);
      postInfo.erase(0,1);
      try{
        (*this).addPost(idFromFile, nameFromFile, postInfo);
      }
      catch (std::invalid_argument& e) {
        throw std::runtime_error("loadFromFile: invalid parameter from Post");
      }
    }
    else {
      throw std::runtime_error("loadFromFile: unknown entry (neither User nor Post)");
    }
    fin >> userOrPost;
    if (fin.eof()) {
      break;
    }
  }
}

void Network::addUser(string userName) {
  // TODO(student): create user and add it to network
  // make all lowercase
  for (unsigned int i = 0; i < userName.length(); i++) {
    if (userName.at(i) > 64 && userName.at(i) < 91) {
      userName.at(i) = userName.at(i) + 32;
    }
  }
  //check if user with this name already exists
  for (unsigned int i = 0; i < users.size(); i++) {
    if (userName == (*users[i]).getUserName()) {
      throw std::invalid_argument("addUser: invalid parameter values");
    }
  }
  //create new User object and add to users
  User* newUser = new User(userName);
  users.push_back(newUser);
  std::cout << "Added User " << userName << std::endl;
}

void Network::addPost(unsigned int postId, string userName, string postText) {
  // TODO(student): create post and add it to network
  //check if postId already exists
  for (unsigned int i = 0; i < posts.size(); i++) {
    if (postId == (*posts[i]).getPostId()) {
      throw std::invalid_argument("addPost: invalid postId");
    }
  }
  //check if no user with this name exists
  bool noUser = true;
  int userIdx;
  for (unsigned int i = 0; i < users.size(); i++) {
    if (userName == (*users[i]).getUserName()) {
      userIdx = i;
      noUser = false;
    }
  }
  if (noUser) {
    throw std::invalid_argument("addPost: invalid userName");
  }
  //create new Post object and add to posts
  Post* newPost = new Post(postId, userName, postText);
  posts.push_back(newPost);
  //add post info to corresponding user
  (*users[userIdx]).addUserPost(newPost);
  //extract candidate hashtags
  vector<string> postTags = (*newPost).findTags();
  //see if each tag does not exist. if not, create new tag and add to tags
  bool existingTag = false;
  for (unsigned int i = 0; i < postTags.size(); i++) {
    for (unsigned int j = 0; j < tags.size(); j++) {
      if (postTags[i] == (*tags[j]).getTagName()) {
        existingTag = true;
      }
    }
    if (!existingTag) {
      try {
        tags.push_back(new Tag(postTags[i]));
      }
      //if exception thrown, catch and resume for next tag
      catch (std::invalid_argument& e) {
        continue;
      }
    }
  }
  //add post information to each tag
  for (unsigned int i = 0; i < postTags.size(); i++) {
    for (unsigned int j = 0; j < tags.size(); j++) {
      if (postTags[i] == (*tags[j]).getTagName()) {
        (*tags[j]).addTagPost(newPost);
      }
    }
  }
  std::cout << "Added Post " << postId << " by " << userName << std::endl;
}

vector<Post*> Network::getPostsByUser(string userName) {
  // TODO(student): return posts created by the given user
  vector<Post*> postsByUser = {};
  if (userName == "") {
    throw std::invalid_argument("getPostsByUser: invalid parameter values");
  }
  for (unsigned int i = 0; i < posts.size(); i++) {
    if ((*posts[i]).getPostUser() == userName) {
      postsByUser.push_back(posts[i]);
    }
  }
  return postsByUser;
}

vector<Post*> Network::getPostsWithTag(string tagName) {
  // TODO(student): return posts containing the given tag
  vector<Post*> postsWithTag = {};
  if (tagName == "") {
    throw std::invalid_argument("getPostsWithTag: invalid parameter values");
  }
  for (unsigned int i = 0; i < posts.size(); i++) {
    vector<string> tagsInPost = (*posts[i]).findTags();
    for (unsigned int j = 0; j < tagsInPost.size(); j++) {
      if (tagsInPost[j] == tagName) {
        postsWithTag.push_back(posts[i]);
        break;
      }
    }
  }
  return postsWithTag;
}

vector<string> Network::getMostPopularHashtag() {
  // TODO(student): return the tag occurring in most posts
  vector<string> popTag = {};
  unsigned int mostPopTagIdx = 0;
  if (tags.size() == 0) {
    return popTag;
  }
  //find index of tag that appears in most posts and add to vector
  for (unsigned int i = 0; i < tags.size(); i++) {
    if ((*tags[i]).getTagPosts().size() > (*tags[mostPopTagIdx]).getTagPosts().size()) {
      mostPopTagIdx = i;
    }
  }
  popTag.push_back((*tags[mostPopTagIdx]).getTagName());
  //if another tag tied for most popular, add to vector
  if ((mostPopTagIdx + 1) < tags.size()) {
    for (unsigned int i = mostPopTagIdx + 1; i < tags.size(); i++) {
      if ((*tags[i]).getTagPosts().size() == (*tags[mostPopTagIdx]).getTagPosts().size()) {
        popTag.push_back((*tags[i]).getTagName());
      }
    }
  }
  return popTag;
}

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}
