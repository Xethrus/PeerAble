#pragma once

#include <unordered_map>
#include <string>

enum class DocumentState {
  AVAILABLE,
  UNAVAILABLE,
};

class User {
public:
  User(const std::string& name) {
    name_ = name;
  };

  const std::string& get_name() const;
  void set_name(const std::string& name);

  DocumentState get_document_state() const;
  void set_document_state(DocumentState state);

private:
  std::string name_;
  DocumentState document_state_;
};

class UserManager {
public:
  bool user_exists(const std::string& name);
  void add_user(const std::string& name);
  void remove_user(const std::string& name);
  void update_document_state(const std::string& name, DocumentState state);

  const User* get_user(const std::string& name) const;

private:
  std::unordered_map<std::string, User> users_;
};

