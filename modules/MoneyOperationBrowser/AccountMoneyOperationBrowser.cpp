#include "AccountMoneyOperationBrowser.h"

#include <QLayout>
#include <QTableView>

AccountMoneyOperationBrowser::AccountMoneyOperationBrowser(QWidget *parent)
	: QWidget(parent)
{
	mModelAccountOperationTable = new MoneyOperationTableModel();
	mViewAccountOperationTable = new MoneyOperationTableView(this);
	mViewAccountOperationTable->setModel(mModelAccountOperationTable);

	mAddOperationButton = new QPushButton(QStringLiteral("Add"), this);
	mRemoveOperationButton = new QPushButton(QStringLiteral("Remove"), this);

	QVBoxLayout* vLayout = new QVBoxLayout(this);
	vLayout->addWidget(mViewAccountOperationTable);

	QHBoxLayout* buttonLayout = new QHBoxLayout(this);
	buttonLayout->addWidget(mAddOperationButton);
	buttonLayout->addWidget(mRemoveOperationButton);

	vLayout->addLayout(buttonLayout);

}
