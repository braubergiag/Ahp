#include "criteriaform.h"
#include "ui_criteriaform.h"
#include "criteria.h"

#include <QTableWidgetItem>
#include <QDebug>

CriteriaForm::CriteriaForm( CriteriaMatrix* pCriteria, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CriteriaForm)
  , _pCriteria( pCriteria )
{
    ui->setupUi(this);
    ui->nameLineEdit->setText( _pCriteria->getName() );
    if ( _pCriteria->criteriaCount() > 0  )
    {
        ui->tableWidget->setRowCount( _pCriteria->getRows() );
        ui->tableWidget->setColumnCount( _pCriteria->getCols() );
        for ( int row = 0; row < _pCriteria->getRows(); row++)
        {
            for ( int col = 0; col < _pCriteria->getCols(); col++)
            {
                QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg( _pCriteria->getCell( row, col) ));
                ui->tableWidget->setItem(row, col, newItem);
            }
        }
    }
}

CriteriaForm::~CriteriaForm()
{
    delete ui;
}

void CriteriaForm::on_pushButton_clicked()
{
    QString critName = ui->nameLineEdit->text();
    if (_pCriteria->getCriteriaList().contains(critName) || critName == "") return;
     _pCriteria->addCriteria(critName  );
    ui->nameLineEdit->setText("");
     int rows = ui->tableWidget->rowCount();
     int cols = ui->tableWidget->columnCount();
     ui->tableWidget->setRowCount( rows + 1);
     ui->tableWidget->setColumnCount( cols + 1);
     QTableWidgetItem *itemH = new  QTableWidgetItem(critName );
     ui->tableWidget->setHorizontalHeaderItem( cols, itemH);

     QTableWidgetItem *itemV = new  QTableWidgetItem(critName );
     ui->tableWidget->setVerticalHeaderItem( rows, itemV);
     for( int row = 0; row <= rows; row++ )
     {
         QTableWidgetItem *itemV = new  QTableWidgetItem("1");
         ui->tableWidget->setItem(row,cols,itemV);
         ui->tableWidget->item( row, cols)->setData( Qt::WhatsThisRole, "1." );
     }
     for( int col = 0; col <= cols; col++ )
     {
         QTableWidgetItem *itemV = new  QTableWidgetItem("1");
         ui->tableWidget->setItem(rows,col,itemV);
          ui->tableWidget->item( rows, col)->setData( Qt::WhatsThisRole, "1." );
     }
     ui->tableWidget->item( rows, cols)->setText("1");
     ui->tableWidget->item( rows, cols)->setData( Qt::WhatsThisRole, "1." );
}

void CriteriaForm::on_pushButton_2_clicked()
{
    _pCriteria->removeCriteria( ui->nameLineEdit->text() );

    for( int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        if ( ui->tableWidget->horizontalHeaderItem( i )->text() == ui->nameLineEdit->text() )
        {
            ui->tableWidget->removeRow( i );
            ui->tableWidget->removeColumn( i );
            break;
        }
    }
}

void CriteriaForm::on_tableWidget_cellChanged(int row, int column)
{
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

   } else if ( val_text == '1') { return;}

    else {
        double value =val_text.toDouble();
        ui->tableWidget->item( row, column)->setData( Qt::WhatsThisRole, QString("%1").arg(value));
        if (value > eps and value <= max_val) {
            ui->tableWidget->item( column, row )->setText( QString("1/%1").arg( value ));
        }

    }

}

void CriteriaForm::on_pushButton_3_clicked()
{
    _pCriteria->setSize( ui->tableWidget->rowCount() );

    if ( _pCriteria->criteriaCount() > 0  )
    {
        for ( int row = 0; row < ui->tableWidget->rowCount(); row++)
        {
            for ( int col = 0; col < ui->tableWidget->columnCount(); col++)
            {
                QString s = ui->tableWidget->item( row, col)->data( Qt::WhatsThisRole).toString();

                const double d =  s.toDouble();
                qDebug() << s << " " << d;
                _pCriteria->setCell( row, col,d );
            }
        }
    }

    for (int i =0; i < _pCriteria->getRows(); ++i)
        for (int j = 0; j < _pCriteria->getCols(); ++j)
        {
           qDebug () << _pCriteria->getCell(i,j);
        }

    emit formClosed();
    close();

}
