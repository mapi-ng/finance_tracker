module TransactionMapper;

namespace storage {

core::Transaction TransactionMapper::map(const CSVRow &row) const {
  core::Transaction transaction;
  transaction.id = row.at("id");
  transaction.amount = std::stod(row.at("amount"));
  transaction.date = row.at("date");
  transaction.description = row.at("description");
  return transaction;
}

}  // namespace storage