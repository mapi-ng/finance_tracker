module;
// Preprocessing directives
#include <uuid.h>
export module Transaction;

import Utils;

namespace core {

export class Transaction {
 public:
  explicit Transaction(unsigned int amount)
      : id_{utils::generateUuid()}, amount_{amount} {}

  unsigned int getAmount() const { return amount_; }

  uuids::uuid getId() const { return id_; }

  void setAmount(unsigned int amount) { amount_ = amount; }

 private:
  uuids::uuid id_;
  unsigned int amount_;
};

}  // namespace core
