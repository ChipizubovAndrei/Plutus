#include "AccountMoneyOperationBrowser.h"

#include <QTableView>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

#include "MoneyOperationDialog.h"

AccountMoneyOperationBrowser::AccountMoneyOperationBrowser(QWidget *parent)
	: QWidget(parent)
{
	QString dbPath = QString("..\\..\\..\\storage\\PlutusDB.db");
	mAddOperationButton = new QPushButton("Add");
	mRemoveOperationButton = new QPushButton("Remove");

	connect(mAddOperationButton, &QPushButton::clicked, 
		this, &AccountMoneyOperationBrowser::onAddedButtonClicked);
	connect(mRemoveOperationButton, &QPushButton::clicked,
		this, &AccountMoneyOperationBrowser::onRemoveButtonClicked);

	mViewAccountOperationTable = new MoneyOperationTableView(this);

	mDatabase = QSqlDatabase::addDatabase("QSQLITE");
	mDatabase.setDatabaseName(dbPath);
	if (mDatabase.open())
	{
 		mTableModel = QSharedPointer<QSqlTableModel>(new QSqlTableModel(this, mDatabase));
		mTableModel->setTable("MoneyOperations");
		mTableModel->select();
		mViewAccountOperationTable->setModel(mTableModel.data());
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
		MoneyOperation result = dialog->getMoneyOperation();
		QSqlQuery sql = QSqlQuery();
		sql.prepare("INSERT INTO MoneyOperations VALUES (?, ?, ?)");
		sql.bindValue(0, mTableModel->rowCount()+1);
		sql.bindValue(1, result.moneyAmount);
		sql.bindValue(2, result.category);
		sql.exec();
		if (sql.lastError().type() == QSqlError::NoError)
		{
			mTableModel->select();
		}
		//MoneyOperation result = dialog->getMoneyOperation();
		//mTableModel->setData(mTableModel->index(mTableModel->rowCount(), 0), mTableModel->rowCount());
		//mTableModel->setData(mTableModel->index(mTableModel->rowCount(), 1), result.moneyAmount);
		//mTableModel->setData(mTableModel->index(mTableModel->rowCount(), 2), result.category);
		//if (mTableModel->submitAll())
		//{
		//	emit postMessage("Success commit to DB");
		//}
		//else
		//{
		//	emit postMessage("Failed commit to DB");
		//}
	}
}

void AccountMoneyOperationBrowser::onRemoveButtonClicked()
{
	
}
