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
#include <string>
#include <stdexcept>
#include "Post.h"
#include <vector>

using std::string;
using std::vector;

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
  // TODO(student): extracts candidate tags based on occurrences of # in the post
  vector<string> tags = {};
  string tag = "";
  for (unsigned int i = 0; i < postText.length(); i++) {
    if (postText.at(i) == '#') {
      int length = 1;
      for (unsigned int j = i; j < postText.length() && postText.at(j) != ' '; j++) {
        length++;
      }
      tag = postText.substr(i, length);
      //remove punctuations
      while (tag.back()=='!' || tag.back()==',' || tag.back()=='.' || tag.back()=='?' || tag.back()==' ') {
        tag.pop_back();
      }
      //only lowercase
      for (unsigned int k = 0; k < tag.length(); k++) {
        if (tag.at(k) > 64 && tag.at(k) < 91) {
          tag.at(k) = tag.at(k) + 32;
        }
      }
      //only unique tags
      bool unique = true;
      for (unsigned int i = 0; i < tags.size(); i++) {
          if (tags[i] == tag) {
              unique = false;
          }
      }
      if (unique) {
          tags.push_back(tag);
      }
    }
  }
  return tags;
}
