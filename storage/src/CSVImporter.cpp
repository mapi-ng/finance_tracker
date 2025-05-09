module;
#include <filesystem>
#include <vector>
export module CSVImporter;
export import Importer;

namespace storage {

export struct CSVConfig {
  char delimiter = ',';
  bool has_header = true;
};

export class CSVImporter : public Importer {
 private:
  std::filesystem::path file_path_;
  CSVConfig config_;

 public:
  explicit CSVImporter(const std::filesystem::path &file_path,
                       const CSVConfig &config = {});
  ~CSVImporter() override = default;
  std::vector<core::Transaction> read() override;
};

}  // namespace storage