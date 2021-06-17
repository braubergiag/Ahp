#include "alternativesdialog.h"
#include "ui_alternativesdialog.h"
#include "criteria.h"


AlternativesDialog::AlternativesDialog(const QStringList& alterNames, const QStringList& criteriaNames,QVector< CriteriaMatrix* >* alternVec, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlternativesDialog)
  , _alterNames(alterNames)
  , _criteriaNames(criteriaNames)
  , _alternVec( alternVec )

{
    ui->setupUi(this);
    ui->comboBox->addItems( criteriaNames );
}

AlternativesDialog::~AlternativesDialog()
{
    delete ui;
}

void AlternativesDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{

    if ( _currMatrix )
    {

        // 1) сохранить данные в матрицу
        for ( int row = 0; row < _currMatrix->getRows(); row++)
        {
            // Диагональные элементы заполняем единицами
             _currMatrix->setCell( row, row, 1.0);
            for ( int col = 0; col < _currMatrix->getCols(); col++)
            {
                 const double d = ui->tableWidget->item( row, col)->data( Qt::WhatsThisRole).toDouble();
                _currMatrix->setCell( row, col,d );

            }
        }



    }
    _currMatrix = nullptr;

    // 2) найти матрицу по имени
    for( int i = 0; i < _alternVec->count(); ++i)
    {
        CriteriaMatrix* m = _alternVec->at(i);
        if ( m->getName() == arg1 )
        {
            _currMatrix = m;
            break;
        }
    }
    Flag = true;
    ui->tableWidget->clear();
    const double eps = 0.0001;

    if ( _currMatrix )
    {
        ui->tableWidget->setRowCount( _currMatrix->getRows() );
        ui->tableWidget->setColumnCount( _currMatrix->getCols() );
        for ( int row = 0; row <  _currMatrix->getRows(); row++)
        {

            for ( int col = 0; col <  _currMatrix->getCols(); col++)
            {
                double value =  _currMatrix->getCell( row, col);
                if (value < 1.0 && value > eps){
//                    if (_currMatrix->getCell( col, row) < 0.001){
//                         QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(  _currMatrix->getCell( row, col) ));
//                         ui->tableWidget->setItem(row, col, newItem);
//                    } else {
                        QTableWidgetItem *newItem = new QTableWidgetItem(tr("1/%1").arg(  _currMatrix->getCell( col, row) ));
                        ui->tableWidget->setItem(row, col, newItem);
                        ui->tableWidget->item( row,col)->setData( Qt::WhatsThisRole,value);
                    }


                 else {
                    QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(  _currMatrix->getCell( row, col) ));
                     ui->tableWidget->setItem(row, col, newItem);
                     ui->tableWidget->item( row,col)->setData( Qt::WhatsThisRole,value);
                }



            }
        }

        for (int i = 0; i < _alterNames.count();++i){
            QTableWidgetItem *itemHeaderH = new  QTableWidgetItem(_alterNames[i] );
            ui->tableWidget->setHorizontalHeaderItem( i, itemHeaderH);
            QTableWidgetItem *itemHeaderV = new  QTableWidgetItem(_alterNames[i] );
            ui->tableWidget->setVerticalHeaderItem( i, itemHeaderV);
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(  _currMatrix->getCell( i, i) ));
            newItem->setData( Qt::WhatsThisRole,1.0);
            ui->tableWidget->setItem(i,i, newItem);
        }
        // 3) заполнить таблицу данными из матрицы
    }
    Flag = false;

}

void AlternativesDialog::setAlterNames(const QStringList &value)
{
    _alterNames = value;
}

void AlternativesDialog::on_tableWidget_cellChanged(int row, int column)
{
   if (Flag) return;
    const double eps = 0.0001;
    const double max_val = 10;
    if ( row == column )
    {
        ui->tableWidget->item( column, row )->setText("1");
        return;
    }
    QString val_text = ui->tableWidget->item( row, column)->text();

    if (val_text.contains("/")) {
        double value_sym = ui->tableWidget->item(column,row)->data( Qt::WhatsThisRole).toDouble();
        if (value_sym > eps){
            const double fraction = 1./value_sym;
            ui->tableWidget->item(row,column)->setData( Qt::WhatsThisRole,QString("%1").arg(fraction));
        }

   } else {
        double value =val_text.toDouble();
        ui->tableWidget->item( row, column)->setData( Qt::WhatsThisRole, QString("%1").arg(value));
        if (value > eps and value <= max_val) {
            ui->tableWidget->item( column, row )->setText( QString("1/%1").arg( value ));
        }
    }
}

void AlternativesDialog::on_buttonBox_accepted()
{
if ( _currMatrix )
{

    // 1) сохранить данные в матрицу
    for ( int row = 0; row < _currMatrix->getRows(); row++)
    {
        // Диагональные элементы заполняем единицами
         _currMatrix->setCell( row, row, 1.0);
        for ( int col = 0; col < _currMatrix->getCols(); col++)
        {
             const double d = ui->tableWidget->item( row, col)->data( Qt::WhatsThisRole).toDouble();
            _currMatrix->setCell( row, col,d );

        }
    }



}
}
