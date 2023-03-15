#pragma once

#include "user_management.h"


void User::set_name(const std::string& name) {
  name_ = name;
}

bool User::get_document_state() const {
  return document_state_;
}

void User::set_document_state(bool state) {
  document_state_ = stat;
}
//make sure this static method works TODO
static bool UserManager::user_exists(const std::string& name) {
  if(users_.count(name) > 0) {
    return true;
  } else {
    return false;
  }
}

void UserManager::add_user(const std::string& name) {
  if(!user_exists(name)) {
    new_user = User(name);
    users_.insert({name, new_user});
  } else {
    throw std::runtime_error("User already exists");
  }
}

void UserManager::remove_user(const std::string& name) {
  if(user_exists(name)) {
    users_.erase(name);
  } else {
    throw std::runtime_error("No such user exists");
  }
}

void update_document_state(const std::string& name, bool state) {
  if(user_exists(name)) {
    users_[name].set_document_state(state); 
  } else {
    throw std::runtime_erro("No such user exists");
  }
}

const User* get_user(const std::string& name) const {
  return users_[name];
}
