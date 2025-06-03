#include <spdlog/spdlog.h>

import Transaction;

int main() {
  spdlog::info("Welcome to Finance Tracker!");
  core::Transaction transaction(100.0);
  spdlog::info("Transaction amount: {}", transaction.getAmount());
  transaction.setAmount(200.0);
  spdlog::info("Updated transaction amount: {}", transaction.getAmount());
  return 0;
}
