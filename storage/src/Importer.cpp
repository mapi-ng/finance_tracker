module;
#include <exception>
#include <vector>
export module Importer;

export import Transaction;

namespace storage {

export class ImporterException : public std::exception {};

export class Importer {
 public:
  virtual ~Importer() = default;
  virtual std::vector<core::Transaction> read() = 0;
};

}  // namespace storage
