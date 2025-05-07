module;
#include <filesystem>
export module CSVImporter;
import Importer;

namespace storage {

export class CSVImporter : public Importer {
 public:
  ~CSVImporter() override = default;
  explicit CSVImporter(const std::filesystem::path&) {
    // Constructor implementation
  };
};

}  // namespace storage