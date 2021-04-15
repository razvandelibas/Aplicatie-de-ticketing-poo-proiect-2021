#include <Windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <iostream>

#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

void CloseConnectionAndRelease(SQLHANDLE& sqlconn, SQLHANDLE& sqlstmt, SQLHANDLE& sqlenv)
{
	SQLFreeHandle(SQL_HANDLE_STMT, sqlstmt);
	SQLDisconnect(sqlconn);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlconn);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlenv);
}

int main()
{
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];


	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle) != SQL_SUCCESS)
	{
		CloseConnectionAndRelease(sqlConnHandle, sqlStmtHandle, sqlEnvHandle);
		return 0;
	}
	if (SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0) != SQL_SUCCESS)
	{
		CloseConnectionAndRelease(sqlConnHandle, sqlStmtHandle, sqlEnvHandle);
		return 0;
	}
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
	{
		CloseConnectionAndRelease(sqlConnHandle, sqlStmtHandle, sqlEnvHandle);
		return 0;
	}

	std::cout << "Attempting connection to SQL Server...\n";

	// connect to SQL Server
	switch (SQLDriverConnect(sqlConnHandle, NULL, (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1434;DATABASE=Northwind;Trusted=true;",
		SQL_NTS, retconstring, 1024, NULL, SQL_DRIVER_NOPROMPT))
	{
	case SQL_SUCCESS:
		std::cout << "Successfully connected to SQL Server\n";
		break;
	case SQL_SUCCESS_WITH_INFO:
		std::cout << "Successfully connected to SQL Server\n";
		break;
	case SQL_INVALID_HANDLE:
		std::cout << "Could not connect to SQL Server\n";
		break;
	case SQL_ERROR:
		std::cout << "Could not connect to SQL Server\n";
		break;
	default:
		break;
	}

	if (SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle) != SQL_SUCCESS)
	{
		CloseConnectionAndRelease(sqlConnHandle, sqlStmtHandle, sqlEnvHandle);
		return 0;
	}

	std::cout << "\nExecuting SQL Query...\n";
	if (SQLPrepareA(sqlStmtHandle, (SQLCHAR*)"SELECT * FROM Customers", SQL_NTS) != SQL_SUCCESS)
	{
		std::cout << "Error querying SQL Server\n";
		CloseConnectionAndRelease(sqlConnHandle, sqlStmtHandle, sqlEnvHandle);
		return 0;
	}
	else
	{
		SQLExecute(sqlStmtHandle);
		std::cout << "Query executed successfully!\n";

		// declare output variable and pointer
		SQLCHAR queryResult[SQL_RESULT_LEN];
		SQLLEN ptrQueryResult;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS)
		{
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, queryResult, SQL_RESULT_LEN, &ptrQueryResult);
			std::cout << "\n";
			std::cout << queryResult;
		}
	}
	
	CloseConnectionAndRelease(sqlConnHandle, sqlStmtHandle, sqlEnvHandle);
	return 0;
}