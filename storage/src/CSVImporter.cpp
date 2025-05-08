module;
#include <filesystem>
export module CSVImporter;
export import Importer;

namespace storage {

export class CSVImporter : public Importer {
 public:
  explicit CSVImporter(const std::filesystem::path &file_path);
  ~CSVImporter() override = default;
};

}  // namespace storage