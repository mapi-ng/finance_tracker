module;
#include <chrono>
#include <fstream>
#include <nlohmann/json.hpp>
#include <regex>
module Transaction;

import Exceptions;

namespace core {

/**
 * @brief Transaction mapper implementation class to parse some JSON data.
 * It remains part of the implementation, because nlohmann/json.hpp
 * cannot be used in module interface units as of 3.12.0.
 */
class TransactionMapper::TransactionMapperImpl {
  using json = nlohmann::json;

 private:
  json config_;

 public:
  explicit TransactionMapperImpl(const std::filesystem::path& map_file_path) {
    std::ifstream file(map_file_path);
    if (!file) {
      throw utils::FailedToOpenFile(map_file_path, "File handle is invalid.");
    }
    try {
      file >> config_;
    } catch (const json::parse_error& e) {
      throw utils::FailedToParseJson(map_file_path, e.what());
    } catch (const std::exception& e) {
      throw std::runtime_error("Error: " + std::string(e.what()));
    }
  }

  std::chrono::year_month_day tryParseDate(const std::string& input) {
    for (const auto& format : config_["date_formats"]) {
      if (std::regex_match(input, std::regex(format["regex"]))) {
        std::istringstream in{input};
        std::chrono::year_month_day date{};
        in >> std::chrono::parse(format["format"].get<std::string>(), date);
        if (!in.fail()) {
          return date;
        }
      }
    }
    throw TransactionParsingError("Failed to parse date: " + input);
  }

  template<typename T>
    requires(std::same_as<T, std::string> || std::same_as<T, unsigned int>)
  std::optional<T> tryFirstMatchingColumnValue(const std::string& column_name,
                                               const storage::CSVRow& row) {
    const auto& column_names = config_["mapping"][column_name];
    auto it = std::ranges::find_if(column_names, [&](const json& item) {
      return row.contains(item.get<std::string>());
    });

    if (it == column_names.end())
      return std::nullopt;

    const auto& value = row.at(it->template get<std::string>());

    if constexpr (std::same_as<T, std::string>) {
      return value;
    } else if constexpr (std::same_as<T, unsigned int>) {
      if (unsigned int result;
          std::from_chars(value.data(), value.data() + value.size(), result).ec
          == std::errc{}) {
        return result;
      }
    }

    return std::nullopt;
  }

  std::vector<Transaction> map(const std::vector<storage::CSVRow>& rows) {
    std::vector<Transaction> transactions;

    for (const auto& row : rows) {
      auto date_str = tryFirstMatchingColumnValue<std::string>("date", row);
      auto amount = tryFirstMatchingColumnValue<unsigned int>("amount", row);

      if (!date_str.has_value() || !amount.has_value()) {
        throw TransactionParsingError("Missing required fields in row: "
                                      + nlohmann::json(row).dump());
      }

      auto date = tryParseDate(date_str.value());
      TransactionBuilder builder{date, amount.value()};

      auto description =
          tryFirstMatchingColumnValue<std::string>("description", row);
      builder.description(description.value_or(""));

      transactions.push_back(builder.build());
    }

    return transactions;
  }
};

TransactionMapper::TransactionMapper(const std::filesystem::path& map_file_path)
    : impl_{std::make_unique<TransactionMapperImpl>(map_file_path)} {
}

/**
 * @brief Destructor for TransactionMapper.
 * Due to the use of PImpl idiom, the destructor needs to be defined in implementation.
 */
TransactionMapper::~TransactionMapper() = default;

std::vector<Transaction> TransactionMapper::map(
    const std::vector<storage::CSVRow>& rows) const {
  return impl_->map(rows);
}

}  // namespace core