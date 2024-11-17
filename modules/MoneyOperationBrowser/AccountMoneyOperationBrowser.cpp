#include "AccountMoneyOperationBrowser.h"

#include <QTableView>

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
	}
}

void AccountMoneyOperationBrowser::onRemoveButtonClicked()
{
	
}
