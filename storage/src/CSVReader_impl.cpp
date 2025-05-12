module;
#include <spdlog/spdlog.h>

#include <filesystem>
#include <format>
#include <fstream>
#include <vector>

module CSVReader;

namespace storage {

CSVReader::CSVReader(const std::filesystem::path &file_path,
                         const CSVConfig &config)
    : file_path_{file_path},
      config_{config} {
  {
    if (!std::filesystem::exists(file_path_)) {
      throw CSVImporterException("File does not exist: " + file_path.string());
    }
  }
}

std::vector<CSVRow> CSVReader::read() const {
  std::ifstream file{file_path_};
  if (!file.is_open()) {
    throw CSVImporterException("Couldn't open file.");
  }
  std::vector<CSVRow> rows;
  std::string line;

  bool is_first_line = true;
  std::vector<std::string> headers;
  while (std::getline(file, line)) {
    const auto &tokens = split(line);

    if (is_first_line) {
      headers = populateHeaders(tokens);
      is_first_line = false;

      if (config_.has_header) {
        continue;
      }
    }

    if (config_.has_header && (tokens.size() != headers.size())) {
      auto error =
          std::format("Row {} size does not match header size: {} vs {}",
                      rows.size(), tokens.size(), headers.size());
      spdlog::error(error);
      throw CSVImporterException(error);
    }

    CSVRow row;
    for (size_t i = 0; i < headers.size(); ++i) {
      const auto &key = config_.has_header ? headers[i] : std::to_string(i);
      row[key] = tokens[i];
    }
    rows.push_back(row);
  }
  return rows;
}

std::vector<std::string> CSVReader::populateHeaders(
    const std::vector<std::string> &tokens) const {
  std::vector<std::string> headers;
  if (config_.has_header) {
    headers = tokens;
  } else {
    for (size_t i = 0; i < tokens.size(); ++i) {
      headers.emplace_back(std::to_string(i));
    }
  }
  return headers;
}

std::vector<std::string> CSVReader::split(const std::string &line) const {
  std::vector<std::string> tokens;
  std::istringstream token_stream{std::string{line}};
  std::string token;
  while (std::getline(token_stream, token, config_.delimiter)) {
    tokens.push_back(token);
  }

  // Last character is a delimiter, meaning an empty token
  if (line.back() == config_.delimiter) {
    tokens.emplace_back();
  }

  return tokens;
}

}  // namespace storage