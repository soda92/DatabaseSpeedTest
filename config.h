#pragma once

constexpr bool use_dameng = true;

constexpr int data_count = ([]() {
  if constexpr (!use_dameng) {
    return 100'000;
  }
  return 100'000'000;
})();

constexpr int test_insert_count = 1'000;
constexpr int test_update_count = 1'000;
constexpr int test_delete_count = test_insert_count;
constexpr int test_query_count = 10'000;
