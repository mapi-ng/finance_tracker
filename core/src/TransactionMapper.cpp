export module TransactionMapper;

import Transaction;
import CSVReader;

namespace storage {

class TransactionMapper {
public:
[[nodiscard]] core::Transaction map(const CSVRow &row) const;
};

}