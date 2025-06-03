module;
#include <filesystem>
#include <vector>
module CSVImporter;

namespace storage {

CSVImporter::CSVImporter(const std::filesystem::path &file_path,
                         const CSVConfig &config)
    : file_path_{file_path},
      config_{config} {
  {
    if (!std::filesystem::exists(file_path_)) {
      throw ImporterException();
    }
  }
}

std::vector<core::Transaction> CSVImporter::read() {
  return {};
}

}  // namespace storage