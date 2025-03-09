#include "AccountMoneyOperationBrowser.h"

#include <QTableView>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

#include <DatabaseManager.h>
#include <OperationManager.h>
#include <AccountManager.h>

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

	if (databaseManager->isConnected())
	{
        qDebug() << "База данных открыта, создаем модель таблицы";
        mModelAccountOperationTable = QSharedPointer<MoneyOperationTableModel>(new MoneyOperationTableModel());
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
        try
        {
            MoneyOperation result = dialog->getResult();
            QSharedPointer<OperationManager> operationManager = OperationManager::instance();
            operationManager->addOperation(result);
            mModelAccountOperationTable->refresh();
        }
        catch (const QString& ex)
        {
            QMessageBox::critical( this, "Ошибка", ex, QMessageBox::Ok);
        }

	}
}

void AccountMoneyOperationBrowser::onRemoveButtonClicked()
{
	
}
