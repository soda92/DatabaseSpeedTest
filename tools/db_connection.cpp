#include "db_connection.h"

QSqlQuery get_connection(){
  static QSqlDatabase db;
  static std::once_flag flag;
  std::call_once(flag, [&]() {
    db=QSqlDatabase::addDatabase("QDM");
    db.setHostName("127.0.0.1");
    db.setPort(5236);
    db.setDatabaseName("DAMENG");
    db.setUserName("SYSDBA");
    db.setPassword("SYSDBA");
    if (!db.open()) {
      qDebug() << "failed: " << db.lastError().text().toLatin1();
      std::terminate();
    }
  });
  auto query = QSqlQuery(db);
  return query;
}
