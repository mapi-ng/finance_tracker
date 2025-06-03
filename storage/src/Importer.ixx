module;
#include <exception>
export module Importer;

namespace storage {

export class ImporterException : public std::exception {};

export class Importer {
 public:
  virtual ~Importer() = default;
};

}  // namespace storage
