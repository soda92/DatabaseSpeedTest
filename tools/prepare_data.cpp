#include "prepare_data.h"
#include "config.h"
#include "db_connection.h"

void prepare_data()
{
  auto query = get_connection();
  //  query.exec("drop table if exists test_table");
  //  query.exec("create table test_table(idx int primary key auto_increment,"
  //             "val1 int, val2 varchar(50), val3 float)");

  query.exec("select count(*) from test_table");
  auto num = 0;
  while (query.next()) {
    num = query.value(0).toInt();
  }
  qDebug() << num;
  if (num != data_count) {
    if (num < data_count) {
      for (auto i = num; i < data_count; i++) {
        if (!query.exec("insert into test_table(val1, val2, val3) values (1, 'test',"
                        "2.0)")) {
          qDebug() << query.lastError().text();
        }
      }
    }
    else {
      auto cnt = num - data_count;
      if (!query.prepare("select idx from test_table order by idx desc limit ?")) {
        qDebug() << query.lastError().text();
        std::terminate();
      }
      query.addBindValue(cnt);
      if (!query.exec()) {
        qDebug() << query.lastError().text();
        std::terminate();
      }
      QVector<int> indexes;
      while (query.next()) {
        indexes.append(query.value(0).toInt());
      }
      for (auto i = 0; i < indexes.length(); i++) {
        if (!query.prepare("delete from test_table where idx=?")) {
          qDebug() << query.lastError().text();
          std::terminate();
        }
        query.addBindValue(indexes.at(i));
        if (!query.exec()) {
          qDebug() << query.lastError().text();
          std::terminate();
        }
      }
    }
  }
  query.exec("select count(*) from test_table");

  while (query.next()) {
    num = query.value(0).toInt();
  }
  qDebug() << num;

  return;
}
