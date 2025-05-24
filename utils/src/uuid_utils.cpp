module;
#include <uuid.h>

#include <algorithm>
export module Utils;

namespace utils {

static constexpr uuids::uuid UUID_NAMESPACE =
    uuids::uuid::from_string("e4f1c92a-d397-4ed9-aee6-3df3f5363d2e").value();

export uuids::uuid generateUuidFromData(std::string_view data_string) {
  uuids::uuid_name_generator uuid_v5_generator(UUID_NAMESPACE);
  return uuid_v5_generator(data_string);
}

export uuids::uuid generateUuid() {
  std::random_device rd;
  auto seed_data = std::array<int, std::mt19937::state_size>{};
  std::ranges::generate(seed_data, std::ref(rd));
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
  std::mt19937 generator(seq);
  uuids::uuid_random_generator gen{generator};
  return gen();
}

export inline uuids::uuid generateUuid(std::string_view str) {
  return uuids::uuid::from_string(str).value_or(uuids::uuid{});
}

}  // namespace utils