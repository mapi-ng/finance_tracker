module;
#include <uuid.h>
export module Transaction;

import Utils;

namespace core {

export class Transaction {
 public:
  using Timestamp = std::chrono::system_clock::time_point;
  explicit Transaction(unsigned int amount,
              Timestamp timestamp = Timestamp::clock::now())
      : amount_{amount}, timestamp_{timestamp} {}

  unsigned int getAmount() const { return amount_; }

  uuids::uuid getId() const { return id_; }
  Timestamp getTimestamp() const { return timestamp_; }
  std::string getDescription() const { return description_; }
  void setDescription(std::string_view description) {
    description_ = description;
  }

  void setAmount(unsigned int amount) { amount_ = amount; }

 private:
  uuids::uuid id_{utils::generateUuid()};
  unsigned int amount_;
  Timestamp timestamp_;
  std::string description_;
};

}  // namespace core
