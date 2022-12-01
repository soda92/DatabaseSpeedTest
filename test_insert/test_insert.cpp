#include "tools.h"
#include "config.h"

#include <QCoreApplication>
#include <QtCore>
#include <QtSql>


int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);

  auto query = get_connection();
  prepare_data();

  QElapsedTimer timer;

  auto num_count = test_insert_count;
  std::vector<int> var1_data;
  for (auto i = 0; i < num_count; i++) {
    var1_data.push_back(generate_random_int());
  }
  std::vector<float> var3_data;
  for (auto i = 0; i < num_count; i++) {
    var3_data.push_back(generate_random_int() / 1000.0);
  }
  std::vector<QString> var2_data;
  for (auto i = 0; i < num_count; i++) {
    var2_data.push_back(generate_random_string(50));
  }

  timer.restart();
  for (auto i = 0; i < num_count; i++) {
    if (!query.prepare("insert into test_table(val1, val2, val3) values (?, ?,"
                       "?)")) {
      qDebug() << query.lastError().text();
    }
    query.addBindValue(var1_data.at(i));
    query.addBindValue(var2_data.at(i));
    query.addBindValue(var3_data.at(i));
    if (!query.exec()) {
      qDebug() << query.lastError().text();
    }
  }

  qDebug() << "average insert time:" << timer.elapsed() / static_cast<float>(num_count) << "ms";

  QTimer::singleShot(0, &app, &QCoreApplication::quit);
  return app.exec();
}
