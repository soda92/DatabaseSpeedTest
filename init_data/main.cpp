#include <QCoreApplication>
#include <QtCore>
#include <QtSql>

#include "tools.h"
#include "config.h"

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  auto query = get_connection();
  prepare_data();

  //  query.exec("drop table if exists test_table");
  //  query.exec("create table test_table(idx int primary key auto_increment,"
  //             "val1 int, val2 varchar(50), val3 float)");

  query.exec("select count(*) from test_table");
  auto num = 0;
  while (query.next()) {
    num = query.value(0).toInt();
  }
  qDebug() << num;

  auto num_count = data_count;
  QElapsedTimer timer;
  timer.start();
  for (auto i = num; i < num_count; i++) {
    if (!query.exec("insert into test_table(val1, val2, val3) values (1, 'test',"
                    "2.0)")) {
      qDebug() << query.lastError().text();
    }
    if (i % 1000 == 0) {
      qDebug() << i / (num_count / 100) << "%"
               << " time:" << timer.elapsed() << "ms";
      timer.restart();
    }
  }

  QTimer::singleShot(0, &app, &QCoreApplication::quit);
  return app.exec();
}
