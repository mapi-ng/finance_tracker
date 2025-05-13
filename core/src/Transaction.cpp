module;
#include <uuid.h>
#include <filesystem>
export module Transaction;

import Utils;
import CSVReader;

namespace core {

export class TransactionBuilder;

export class Transaction {
 public:
  using Date = std::chrono::year_month_day;

  uuids::uuid getId() const { return id_; }
  Date getDate() const { return date_; }
  unsigned int getAmount() const { return amount_; }
  std::string getDescription() const { return description_; }
  std::string getCategory() const { return category_; }

  void setDescription(std::string_view description) {
    description_ = description;
  }

 private:
  Transaction(const Date& date, unsigned int amount)
      : date_{date},
        amount_{amount} {}

  const uuids::uuid id_{utils::generateUuid()};
  Date date_;
  unsigned int amount_;
  std::string description_;
  std::string category_;

  friend class TransactionBuilder;
};

class TransactionBuilder {
 public:
  TransactionBuilder(const Transaction::Date& date, unsigned int amount)
      : transaction_{date, amount} {}

  TransactionBuilder& description(const std::string &value) {
    transaction_.description_ = value;
    return *this;
  }

  TransactionBuilder& category(const std::string &value) {
    transaction_.category_ = value;
    return *this;
  }

  Transaction build() { return std::move(transaction_); }

 private:
  Transaction transaction_;
};

export class TransactionMapper {
 public:
  explicit TransactionMapper(const std::filesystem::path& map_file_path);
  std::vector<Transaction> map(const std::vector<storage::CSVRow>& rows);

 private:
  std::vector<std::string> date_formats_;
  std::unordered_map<std::string, std::vector<std::string>> config_;
};

}  // namespace core
