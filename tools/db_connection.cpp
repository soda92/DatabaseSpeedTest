#include "db_connection.h"
#include "config.h"

QSqlQuery get_connection(){
  static QSqlDatabase db;
  static std::once_flag flag;
  std::call_once(flag, [&]() {
    if(use_dameng){
db=QSqlDatabase::addDatabase("QDM");
    db.setHostName("127.0.0.1");
    db.setPort(5236);
    db.setDatabaseName("DAMENG");
    db.setUserName("SYSDBA");
    db.setPassword("SYSDBA");
    }else{
    db = QSqlDatabase::addDatabase("QMYSQL");
  db.setHostName("127.0.0.1");
  db.setPort(3306);
  db.setDatabaseName("test_insert");
  db.setUserName("root");
  db.setPassword("");
   }
    if (!db.open()) {
      qDebug() << "failed: " << db.lastError().text().toLatin1();
      std::terminate();
    }
  });
  auto query = QSqlQuery(db);
  return query;
}
