module;
// Preprocessing directives
export module Transaction;

namespace core {

export class Transaction {
 public:
  explicit Transaction(unsigned int amount) : amount_(amount) {}

  unsigned int getAmount() const { return amount_; }

  void setAmount(unsigned int amount) { amount_ = amount; }

 private:
  unsigned int amount_;
};

}  // namespace core
