module;
#include <filesystem>
module CSVImporter;

namespace storage {

CSVImporter::CSVImporter(const std::filesystem::path &file_path) {
  if (!std::filesystem::exists(file_path)) {
    throw ImporterException();
  }
}

}  // namespace storage