#include "server.h"
#include <sstream>

std::vector<std::string> pending_trxs{};

Server::Server() {}

std::shared_ptr<Client> Server::add_client(std::string id) {
  auto produceRandom = []() {
    std::string res = "";
    for (int i = 0; i < 4; i++) {
      auto num = e() % 10;
      res += std::to_string(num);
    }
    return res;
  };

  if (get_client(id) != nullptr) {
    id += produceRandom();
  }
  auto client = std::make_shared<Client>(id, *this);
  clients[client] = 5.0;
  return client;
}

std::shared_ptr<Client> Server::get_client(std::string id) const {
  for (auto &[k, v] : clients) {
    if (k->get_id() == id) {
      return k;
    }
  }
  return nullptr;
}

double Server::get_wallet(std::string id) {
  for (auto &[k, v] : clients) {
    if (k->get_id() == id) {
      return v;
    }
  }
  return 0;
}

bool Server::parse_trx(std::string trx, std::string &sender, std::string &receiver, double &value) {
  for (auto &c : trx) {
    if (c == '-') {
      c = ' ';
    }
  }
  std::stringstream ss(trx);
  if (ss >> sender >> receiver >> value) {
    return true;
  } else {
    throw std::runtime_error("Something wrong.");
    return false;
  }
}

bool Server::add_pending_trx(std::string trx, std::string signature) {
  std::string sender{};
  std::string receiver{};
  double value = 0;
  try {
    parse_trx(trx, sender, receiver, value);
  } catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
    return false;
  }
  if (get_client(sender) == nullptr || get_client(receiver) == nullptr) {
    return false;
  }
  if (get_wallet(sender) < value) {
    return false;
  }
  this->clients[get_client(sender)] -= value;
  this->clients[get_client(receiver)] += value;

  pending_trxs.push_back(trx);
  return true;
}

std::size_t Server::mine() {
  std::string mempool{};
	for (const auto& trx : pending_trxs) {
		mempool += trx;
	}
	size_t nonce = 0;
	bool flag = false;
	while (!flag) {
		for (auto& c_w : clients) {
			nonce = c_w.first->generate_nonce();
			if (crypto::sha256(mempool + std::to_string(nonce)).substr(0, 10).find("000") != std::string::npos) {   //mined
        flag = true;
				c_w.second += 6.25;
				pending_trxs.clear();
        return nonce;
			}
		}
	}
	return nonce;
}

std::map<std::shared_ptr<Client>, double> Server::get_clients() const {
  return this->clients;
}

void show_wallets(const Server &server) {
  std::cout << std::string(20, '*') << std::endl;
  for (const auto &client : server.get_clients()) {
    std::cout << client.first->get_id() << " : " << client.second << std::endl;
  }
  std::cout << std::string(20, '*') << std::endl;
}
