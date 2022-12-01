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

  auto num_count = test_update_count;
  std::vector<int> index_data;
  for (auto i = 0; i < num_count; i++) {
    index_data.push_back(generate_random_int(1, num_count));
  }

  std::vector<QString> update_data;
  for (auto i = 0; i < num_count; i++) {
    update_data.push_back(generate_random_string(50));
  }

  timer.restart();
  for (auto i = 0; i < num_count; i++) {
    if (!query.prepare("update test_table set val2=? where idx=?")) {
      qDebug() << query.lastError().text();
    }
    query.addBindValue(update_data.at(i));
    query.addBindValue(index_data.at(i));
    if (!query.exec()) {
      qDebug() << query.lastError().text();
    }
  }

  qDebug() << "average update time:" << timer.elapsed() / static_cast<float>(num_count) << "ms";

  QTimer::singleShot(0, &app, &QCoreApplication::quit);
  return app.exec();
}
