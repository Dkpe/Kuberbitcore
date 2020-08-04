#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include "clientmodel.h"
#include "clientversion.h"

// Copyright year (2009-this)
// Todo: update this when changing our copyright comments in the source
const int BITCOIN_COPYRIGHT_YEAR = 2014;
const int LITECOIN_COPYRIGHT_YEAR = 2013;
const int KUBERBITCOIN_COPYRIGHT_YEAR = 2020;

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    // Set current copyright year
    ui->copyrightLabel->setText(tr("Copyright") + QString(" &copy; ") +
               QString("2009-%1 The Bitcoin developers ").arg(BITCOIN_COPYRIGHT_YEAR) + tr("") + QString("<br>") + tr("Copyright") + QString(" &copy; ") +
               tr("2011-%1 The Litecoin developers").arg(LITECOIN_COPYRIGHT_YEAR) + QString("<br>") + tr("Copyright") + QString(" &copy; ") +
               tr("2014--%1 The Kuberbitcoin developers").arg(KUBERBITCOIN_COPYRIGHT_YEAR));
}

void AboutDialog::setModel(ClientModel *model)
{
    if(model)
    {
        ui->versionLabel->setText(model->formatFullVersion());
    }
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_buttonBox_accepted()
{
    close();
}
