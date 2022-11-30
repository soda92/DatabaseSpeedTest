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

  QElapsedTimer timer;
  timer.start();
  if (num < data_count) {
    auto cnt = data_count - num;
    for (auto i = num; i < data_count; i++) {
      if (!query.exec("insert into test_table(val1, val2, val3) values (1, 'test',"
                      "2.0)")) {
        qDebug() << query.lastError().text();
      }
    }
    qDebug() << "prepare data average insert time:" << timer.elapsed() / static_cast<float>(cnt)
             << "ms";
  }
  else {
    auto cnt = num - data_count;
    for (auto i = data_count; i < num; i++) {
      if (!query.exec("delete from test_table where idx= ("
                      "select max(idx) from test_table)")) {
        qDebug() << query.lastError().text();
      }
    }
    qDebug() << "prepare data average delete time:" << timer.elapsed() / static_cast<float>(cnt)
             << "ms";
  }
  query.exec("select count(*) from test_table");

  while (query.next()) {
    num = query.value(0).toInt();
  }
  qDebug() << num;
}
