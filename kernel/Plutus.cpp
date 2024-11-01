#include "Plutus.h"

#include <QLayout>
#include <QLabel>

#include <MoneyOperation.h>
#include <AccountMoneyOperationBrowser.h>

Plutus::Plutus(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Plutus");
    setMinimumHeight(500);
    setMinimumWidth(700);

    AccountMoneyOperationBrowser* browser = new AccountMoneyOperationBrowser(this);
    setCentralWidget(browser);
}

Plutus::~Plutus()
{}
