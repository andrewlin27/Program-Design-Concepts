/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "Tag.h"

using std::string;
using std::vector;

Tag::Tag(string tagName) /* TODO(student): initialize */ 
  : tagName(tagName) {
  // TODO(student): implement constructor checks
  if (tagName.length() < 2 || tagName.at(0) != '#' || tagName.at(1) < 97 || tagName.at(1) > 122) {
    throw std::invalid_argument("tag constructor: invalid parameter values");
  }
  for (unsigned int i = 0; i < tagName.length(); i++) { //cannot contain uppercase
    if (tagName.at(i) < 97 && tagName.at(i) > 122) {
      throw std::invalid_argument("tag constructor: invalid parameter values");
    }
  }
  if (tagName.back()=='!'||tagName.back()==','||tagName.back()=='.'||tagName.back()=='?') {
    throw std::invalid_argument("tag constructor: invalid parameter values");
  }
}

string Tag::getTagName() {
  // TODO(student): implement getter
  return tagName;
}

vector<Post*>& Tag::getTagPosts() {
  // TODO(student): implement getter
  return tagPosts;
}

void Tag::addTagPost(Post* post) {
  // TODO(student): add post to tag posts
  if (post == nullptr) {
    throw std::invalid_argument("addTagPost: invalid parameter values");
  }
  tagPosts.push_back(post);
}
