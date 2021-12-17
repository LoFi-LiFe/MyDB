#include <iostream>
#include "jdbc/mysql_connection.h"
#include "jdbc/cppconn/driver.h"
#include "jdbc/cppconn/exception.h"
#include "jdbc/cppconn/resultset.h"
#include "jdbc/cppconn/statement.h"
#include "jdbc/cppconn/prepared_statement.h"

#ifdef DEBUG
#pragma comment(lib, "./debug/mysqlcppconn.lib")
#else
#pragma comment(lib, "./mysqlcppconn.lib")
#endif
using namespace std;

int main()
{
	sql::Driver* driver = nullptr;
	sql::Connection* connection = nullptr;
	sql::Statement* statement = nullptr;
	sql::ResultSet* resultset = nullptr;
	sql::PreparedStatement* preparedstatement = nullptr;

	string userid;
	string userpw;
	bool isLogin = false;

	while (!isLogin)
	{

		cout << "유저아이디: ";
		cin >> userid;
		cout << "유저암호: ";
		cin >> userpw;

		//workbench 켜기
		driver = get_driver_instance();
		//연결 버튼 누르기
		connection = driver->connect("tcp://127.0.0.1:3306", "root", "1234");
		if (connection == nullptr)
		{
			cout << "connection error." << endl;
			exit(-1);
		}

		//use Database
		connection->setSchema("ygl");
		//Query typing
		statement = connection->createStatement();
		//쿼리 실행
		//resultset = statement->executeQuery("SELECT * from film_actor limit 0, 10");

		preparedstatement = connection->prepareStatement("SELECT * from member where user_id = ? and user_pw = ?");
		preparedstatement->setString(1, userid);
		preparedstatement->setString(2, userpw);
		preparedstatement->execute();
		resultset = preparedstatement->getResultSet();

		if (resultset && resultset->rowsCount() > 0)
		{
			cout << "로그인 성공" << endl;
			isLogin = true;
		}
		else
		{
			cout << "로그인 실패" << endl;
		}
	}

	delete resultset;
	delete statement;
	delete connection;


	return 0;
}