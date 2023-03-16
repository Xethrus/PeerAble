#include "user_management.h"
#include <stdexcept>


void User::set_name(const std::string& name) {
  name_ = name;
}

DocumentState User::get_document_state() const {
  return document_state_;
}

void User::set_document_state(DocumentState state) {
  document_state_ = state;
}

bool UserManager::user_exists(const std::string& name) {
  return users_.count(name) > 0;
}

void UserManager::add_user(const std::string& name) {
  if(!user_exists(name)) {
    User new_user(name);
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

void UserManager::update_document_state(const std::string& name, DocumentState state) {
  if(user_exists(name)) {
    users_[name].set_document_state(state); 
  } else {
    throw std::runtime_error("No such user exists");
  }
}

const User* UserManager::get_user(const std::string& name) const {
  auto iterator = users_.find(name);
  if(iterator != users_.end()) {
    return &(iterator->second);
  } else {
    return nullptr;
  }
}
