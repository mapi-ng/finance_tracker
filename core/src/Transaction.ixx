module;
// Preprocessing directives
#include <uuid.h>
export module Transaction;

import Utils;

namespace core {

export class Transaction {
 public:
  using Timestamp = std::chrono::system_clock::time_point;
  Transaction(unsigned int amount,
              Timestamp timestamp = Timestamp::clock::now())
      : id_{utils::generateUuid()}, amount_{amount}, timestamp_{timestamp} {}

  unsigned int getAmount() const { return amount_; }

  uuids::uuid getId() const { return id_; }
  Timestamp getTimestamp() const { return timestamp_; }

  void setAmount(unsigned int amount) { amount_ = amount; }

 private:
  uuids::uuid id_;
  unsigned int amount_;
  Timestamp timestamp_;
};

}  // namespace core
