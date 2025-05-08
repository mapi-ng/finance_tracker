module;
#include <filesystem>
#include <vector>
module CSVImporter;

namespace storage {

CSVImporter::CSVImporter(const std::filesystem::path &file_path) {
  if (!std::filesystem::exists(file_path)) {
    throw ImporterException();
  }
}

std::vector<core::Transaction> CSVImporter::import() {
  return {};
}

}  // namespace storage