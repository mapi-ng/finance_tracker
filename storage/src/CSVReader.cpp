module;
#include <filesystem>
#include <map>
#include <vector>
export module CSVReader;

namespace storage {

export using CSVRow = std::map<std::string, std::string, std::less<>>;

export class CSVImporterException : public std::runtime_error {
 public:
  explicit CSVImporterException(const std::string &message)
      : std::runtime_error("CSV Importer Error: " + message) {}
};
export struct CSVConfig {
  char delimiter = ',';
  bool has_header = true;
};

export class CSVReader {
 public:
  explicit CSVReader(const std::filesystem::path &file_path,
                     const CSVConfig &config = {});
  [[nodiscard]] std::vector<CSVRow> read() const;

 private:
  std::filesystem::path file_path_;
  CSVConfig config_;

  [[nodiscard]] std::vector<std::string> populateHeaders(
      const std::vector<std::string> &tokens) const;
  [[nodiscard]] std::vector<std::string> split(const std::string &line) const;
};

}  // namespace storage