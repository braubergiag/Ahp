#include "criteriaaandalternativesdialog.h"
#include "ui_criteriaaandalternativesdialog.h"

CriteriaaAndAlternativesDialog::CriteriaaAndAlternativesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CriteriaaAndAlternativesDialog)
{
    ui->setupUi(this);

}

CriteriaaAndAlternativesDialog::~CriteriaaAndAlternativesDialog()
{
    delete ui;
}

void CriteriaaAndAlternativesDialog::on_buttonBox_accepted()
{
}

QStringList CriteriaaAndAlternativesDialog::alterNames()
{


    _alterNames.clear();
    for(  int i = 0; i < ui->listWidget->count(); ++i)
    {
        QString text = ui->listWidget->item( i )->text();
        _alterNames << text;
    }
    return _alterNames;
}

void CriteriaaAndAlternativesDialog::setAlterNames(const QStringList &alterNames)
{
    _alterNames = alterNames;
    ui->listWidget->clear();
    ui->listWidget->addItems(alterNames);
}


void CriteriaaAndAlternativesDialog::on_pushButton_clicked()
{
    const QString alterName =  ui->lineEdit->text();
    QStringList alter_names = alterNames();
    if (!alter_names.contains(alterName)){
        ui->listWidget->addItem( alterName );
        emit addAlternative( alterName );
        ui->lineEdit->setText("");
    }

}

void CriteriaaAndAlternativesDialog::on_removePushButton_clicked()
{
    const QString removingAlterName = ui->listWidget->currentItem()->text();
    const int row = ui->listWidget->currentRow();
    emit removeAlternative( removingAlterName );
    ui->listWidget->takeItem( row );
    update();
}
