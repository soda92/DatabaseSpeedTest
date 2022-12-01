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

  int num_count = test_query_count;
  std::vector<int> index_data;
  for (auto i = 0; i < num_count; i++) {
    index_data.push_back(generate_random_int(1, num_count));
  }

  timer.restart();
  for (auto i = 0; i < num_count; i++) {
    if (!query.prepare("select * from test_table where idx=?")) {
      qDebug() << query.lastError().text();
    }
    query.addBindValue(index_data.at(i));
    if (!query.exec()) {
      qDebug() << query.lastError().text();
    }
  }

  qDebug() << "average query time:" << timer.elapsed() / static_cast<float>(num_count) << "ms";

  QTimer::singleShot(0, &app, &QCoreApplication::quit);
  return app.exec();
}
