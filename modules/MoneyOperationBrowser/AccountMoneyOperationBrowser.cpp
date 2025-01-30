#include "AccountMoneyOperationBrowser.h"

#include <QTableView>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

#include <DatabaseManager.h>
#include <OperationManager.h>

#include "MoneyOperationDialog.h"

AccountMoneyOperationBrowser::AccountMoneyOperationBrowser(QWidget *parent)
	: QWidget(parent)
{
	QSharedPointer<DatabaseManager> databaseManager = DatabaseManager::instance();

	mAddOperationButton = new QPushButton("Добавить");
	mRemoveOperationButton = new QPushButton("Удалить");

	connect(mAddOperationButton, &QPushButton::clicked, 
		this, &AccountMoneyOperationBrowser::onAddedButtonClicked);
	connect(mRemoveOperationButton, &QPushButton::clicked,
		this, &AccountMoneyOperationBrowser::onRemoveButtonClicked);

	mViewAccountOperationTable = new MoneyOperationTableView(this);

	mDatabase = databaseManager->getDatabase();
	if (mDatabase.isOpen())
	{
        qDebug() << "База данных открыта, создаем модель таблицы";
        mModelAccountOperationTable = QSharedPointer<MoneyOperationTableModel>(new MoneyOperationTableModel());
        //mModelAccountOperationTable = QSharedPointer<QSqlTableModel>(new QSqlTableModel());
        //mModelAccountOperationTable->setTable(DatabaseManager::getOperationTableName());
        //mModelAccountOperationTable->select();
		mViewAccountOperationTable->setModel(mModelAccountOperationTable.data());
	}
	mVLayout = new QVBoxLayout(this);
	mHLayout = new QHBoxLayout(this);
	mVLayout->addWidget(mViewAccountOperationTable);

	mHLayout->addWidget(mAddOperationButton);
	mHLayout->addWidget(mRemoveOperationButton);

	mVLayout->addLayout(mHLayout);

	setLayout(mVLayout);
}

void AccountMoneyOperationBrowser::onAddedButtonClicked()
{
	MoneyOperationDialog* dialog = new MoneyOperationDialog(this);
	if(dialog->exec() == QDialog::Accepted)
	{
		MoneyOperation result = dialog->getResult();
        QSharedPointer<OperationManager> operationManager = OperationManager::instance();
        operationManager->addOperation(result);
        mModelAccountOperationTable->select();

		//QSqlQuery sql = QSqlQuery();
		//sql.prepare("INSERT INTO MoneyOperations VALUES (?, ?, ?)");
		//sql.bindValue(0, mModelAccountOperationTable->rowCount()+1);
		//sql.bindValue(1, result.moneyAmount);
		//sql.bindValue(2, result.category_id);
		//sql.exec();
		//if (sql.lastError().type() == QSqlError::NoError)
		//{
		//	mTableModel->select();
		//}
		//MoneyOperation result = dialog->getMoneyOperation();
		//mTableModel->setData(mTableModel->index(mTableModel->rowCount(), 0), mTableModel->rowCount());
		//mTableModel->setData(mTableModel->index(mTableModel->rowCount(), 1), result.moneyAmount);
		//mTableModel->setData(mTableModel->index(mTableModel->rowCount(), 2), result.category);

	}
}

void AccountMoneyOperationBrowser::onRemoveButtonClicked()
{
	
}
