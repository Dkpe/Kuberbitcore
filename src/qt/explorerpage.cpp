#include "explorerpage.h"
#include "ui_explorerpage.h"

#include "clientmodel.h"
#include "walletmodel.h"
#include "bitcoinunits.h"
#include "optionsmodel.h"
#include "transactiontablemodel.h"
#include "transactionfilterproxy.h"
#include "guiutil.h"
#include "guiconstants.h"

#include <QAbstractItemDelegate>
#include <QPainter>

#define DECORATION_SIZE 64

class ExplorerViewDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    ExplorerViewDelegate(): QAbstractItemDelegate(), unit(BitcoinUnits::BTC) { }

    inline void paint(QPainter *painter, const QStyleOptionViewItem &option,
                      const QModelIndex &index ) const
    {
        painter->save();

        QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
        QRect mainRect = option.rect;
        QRect decorationRect(mainRect.topLeft(), QSize(DECORATION_SIZE, DECORATION_SIZE));
        icon.paint(painter, decorationRect);

        QColor foreground = option.palette.color(QPalette::Text);
        painter->setPen(foreground);
        painter->setPen(foreground);
        painter->setPen(option.palette.color(QPalette::Text));

        painter->restore();
    }

    inline QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        return QSize(DECORATION_SIZE, DECORATION_SIZE);
    }

    int unit;

};
#include "explorerpage.moc"

ExplorerPage::ExplorerPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExplorerPage),
    clientModel(0),
    walletModel(0),
    explorerdelegate(new ExplorerViewDelegate())
{
    ui->setupUi(this);    
    nam = new QNetworkAccessManager(this);
    connect(nam,SIGNAL(finished(QNetworkReply*)),this,SLOT(finished(QNetworkReply*)));
    connect(ui->submitButton,SIGNAL(clicked()),this,SLOT(DoHttpGet()));
}

ExplorerPage::~ExplorerPage()
{
    delete ui;
}

void ExplorerPage::setClientModel(ClientModel *model)
{
    this->clientModel = model;
    if(model)
    {
    }
}

void ExplorerPage::setWalletModel(WalletModel *model)
{
    this->walletModel = model;
}

void ExplorerPage::finished(QNetworkReply *reply) {
  if(reply->error() == QNetworkReply::NoError) {
    ui->textBrowser->setText(reply->readAll());
  } else {
    ui->textBrowser->setText(reply->errorString());
  }
}

void ExplorerPage::DoHttpGet() {
  QString urltxn = "http://qt.kuberbitcoin.net/v1.0.0.1/txn.php?";
  QString urltxi = "http://qt.kuberbitcoin.net/v1.0.0.1/txi.php?";
  QString urla = "http://qt.kuberbitcoin.net/v1.0.0.1/addr.php?";
  QString urlb = "http://qt.kuberbitcoin.net/v1.0.0.1/block.php?";
  QString urle = "http://qt.kuberbitcoin.net/v1.0.0.1/error.php";
  QString data = ui->dataLine->text();
  QString final;
  int size = data.size();
  if(size == 64){
      final = urltxn + data;
  } else if(size == 68){
      final = urltxi + data;
  } else if(size == 34){
      final = urla + data;
  } else if(size >= 7){
      final = urlb + data;
  }else {
      final = urle;
  }
  QNetworkRequest req;
  QByteArray postData;
  postData.append(data.toLocal8Bit());
  req.setUrl(QUrl(final));
  req.setRawHeader("User-Agent", "Kuberbitcoin QT v1.0.0.1");
  nam->get(req);
}
