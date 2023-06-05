#ifndef SERVER_H
#define SERVER_H

#include <map>
#include <memory>
#include <random>
#include <string>
#include "client.h"

extern std::vector<std::string> pending_trxs;
class Client;
class Server {
 public:
  Server();

  /* This function will create a new Client with the specified id. If this id already exists, the server should add a
   *  random 4 digit number at the end of it automatically.
   *  Each client should be assigned with 5 coins at the begining.
   *  Do not use srand for your random numbers. */
  std::shared_ptr<Client> add_client(std::string id);

  /* Using this function you can get a pointer to a Client using its id. */
  std::shared_ptr<Client> get_client(std::string id) const;

  /* Using this function will return the wallet value of the client with username id. */
  double get_wallet(std::string id);

  /** Each transaction has 3 properties:
   * i) id of the sender
   * ii) id of the receiver
   * iii) value of money to transfer.
   * We will show each transaction with a string, concatenating each of these properties with a -.
   * For example if ali sends 1.5 coins to hamed the transaction will be shown by a string "ali-hamed-1.5".
   * This function will parse this string format and outputting each property separately, if the string is not standard
   * you should throw a runtime error. */
  static bool parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value);

  /** Each Client can add a pending transaction using the transaction format described in the above section. 
   * Only accept a pending transaction by authenticating the sender's signature and if he has enough money in his wallet. 
   * note. define the below variable outside the Server class and save the pending transactions in it. */
  bool add_pending_trx(std::string trx, std::string signature);

  std::size_t mine();

  std::map<std::shared_ptr<Client>, double> get_clients() const;

 private:
  /* This member variable will map each client to its wallet. The wallet is the amount of money the client has. */
  std::map<std::shared_ptr<Client>, double> clients;
};

void show_wallets(const Server& server);

#endif  // SERVER_H