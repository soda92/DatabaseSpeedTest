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

  auto cnt = test_delete_count;
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

    QElapsedTimer timer;
    timer.start();
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

    qDebug() << "average delete time:" << timer.elapsed() / static_cast<float>(cnt)
             << "ms";

  QTimer::singleShot(0, &app, &QCoreApplication::quit);
  return app.exec();
}
