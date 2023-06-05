#include "client.h"

Client::Client(std::string id, const Server &server) : id(id), server(&server) {
  std::string public_key, private_key;
  crypto::generate_key(public_key, private_key);
  this->public_key = public_key;
  this->private_key = private_key;
}

std::string Client::get_id() {
  return this->id;
}

std::string Client::get_publickey() const {
  return this->public_key;
}

double Client::get_wallet() {
  Server* b = (Server*)(this->server);  // Server const* const server;
  return b->get_wallet(id);
}

std::string Client::sign(std::string txt) const { 
  return crypto::signMessage(this->private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value) {
  std::string transaction = this->id + "-" + receiver + "-" + std::to_string(value);
  std::string signature = this->sign(transaction);

  return ((Server*)(this->server))->add_pending_trx(transaction, signature);
}

std::size_t Client::generate_nonce() { 
  static std::default_random_engine e;
  static std::uniform_int_distribution u(0, INT_MAX);
  return u(e);
}
