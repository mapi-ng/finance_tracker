#include <spdlog/spdlog.h>

#include "version.h"

import Transaction;

int main() {
  spdlog::info("Welcome to Finance Tracker version: {}", APP_VERSION);
  return 0;
}
