#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "criteria.h"
#include "criteriaform.h"
#include "criteriaaandalternativesdialog.h"
#include "alternativesdialog.h"
#include "ahp_method.h"
#include <QGridLayout>
#include <QWidget>
#include <QDebug>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( ui->actionSet_criterias_and_alternatives, &QAction::triggered, this, &MainWindow::onAddCriteria );
    connect( ui->actionSet_criteria,  &QAction::triggered, this, &MainWindow::onAddCriteriaParams );
    connect (ui->actionSet_alternatives, &QAction::triggered, this, &MainWindow::onAddAlternative );






}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddCriteria()
{
    if (!_criteria || _criteria->getCriteriaList().size() == 0) return;
    CriteriaaAndAlternativesDialog dialog;
    connect( & dialog, &CriteriaaAndAlternativesDialog::removeAlternative, this,  &MainWindow::onRemoveAlternative );
    connect( & dialog, &CriteriaaAndAlternativesDialog::addAlternative, this,  &MainWindow::onAddAlternativeName );
    connect( form, &CriteriaForm::formClosed, this, &MainWindow::onCriteriaFormClosed );
    const QStringList  alterNames = _alternVec.first()->getCriteriaList();
    if ( !alterNames.isEmpty() )
    {
        dialog.setAlterNames( alterNames );
    }

    if ( dialog.exec() == QDialog::Accepted )
    {
        bool initializeMatrix = true;
        if ( !_alterNames )
        {
            _alterNames = new QStringList();

        }
        else
        {
            initializeMatrix = false;
        }

        *_alterNames = dialog.alterNames();

        if ( initializeMatrix )
        {
            for( int i = 0; i < _alternVec.count(); ++i)
            {
                CriteriaMatrix* alternMatrix = _alternVec.at(i);
                alternMatrix->setCriteriaList( *_alterNames );
                alternMatrix->setSize(_alterNames->count());
                alternMatrix->setMatOnes();

            }
        }
    }
}

void MainWindow::onAddAlternative()
{

if (!_criteria || _criteria->getCriteriaList().size() == 0 || !_alterNames || _alterNames->size()== 0) return;
    AlternativesDialog dialog(*_alterNames ,_criteria->getCriteriaList(), &_alternVec );
    dialog.exec();

}

void MainWindow::onAddCriteriaParams()
{
    if ( !_criteria )
    {
        _criteria = new CriteriaMatrix();
    }

    if ( !form )
    {
        form = new CriteriaForm(_criteria);
    }
    connect( form, &CriteriaForm::formClosed, this, &MainWindow::onCriteriaFormClosed );
    form->show();
}

void MainWindow::onCriteriaFormClosed()
{


    for( int i = 0; i < _criteria->criteriaCount(); ++i)
    {
        const QString critName = _criteria->criteriaName(i);
        bool found = false;
        for ( int j = 0; j < _alternVec.size(); ++j)
        {
            if ( _alternVec.at(j)->getName() ==  critName )
            {
                found = true;
                break;
            }
        }
        if ( !found )
        {
            CriteriaMatrix* alternMatrix = new CriteriaMatrix();
            alternMatrix->setName( critName );
            if (_alterNames){
                     alternMatrix->setSize(_alterNames->size());
            }


            alternMatrix->setMatOnes();
            _alternVec.push_back( alternMatrix );
        }
    }

    for( int i = _alternVec.count() - 1; i > -1 ; --i)
    {
        const QString critName = _alternVec.at(i)->getName();
        if ( !_criteria->getCriteriaList().contains( critName ) )
        {
            _alternVec.remove(i);
        }
    }

}

void MainWindow::on_pushButton_clicked()
{
    if (!_criteria || _criteria->getCriteriaList().size() == 0 || !_alterNames || _alterNames->size()== 0) return;
    ahp_method ahp(&_alternVec,_criteria);


    Decision decision = ahp.perform_ahp() ;
     QMap<QStringList,VectorXd> result = decision.sortAlternatives(*_alterNames);
    MatrixXd matrix_norm_weights = decision.getMatrix();
    VectorXd vector_weights = decision.getWeights();
    ui->tableWidget->setRowCount( matrix_norm_weights.rows());
    ui->tableWidget->setColumnCount(  matrix_norm_weights.cols());;
    for (int row = 0; row < matrix_norm_weights.rows(); ++row){

        for (int col = 0; col < matrix_norm_weights.cols();++col){
            QTableWidgetItem * newItem = new QTableWidgetItem(tr("%1").arg(matrix_norm_weights(row,col)));
            ui->tableWidget->setItem(row,col,newItem);
        }
    }

      ui->tableWidget->setVerticalHeaderLabels(*_alterNames);
    ui->tableWidget->setHorizontalHeaderLabels(_criteria->getCriteriaList());

    ui->tableWidget_3->setRowCount(vector_weights.size());
    ui->tableWidget_3->setColumnCount(1);
    for (int i = 0; i < vector_weights.size(); ++i){
             QTableWidgetItem * newItem = new QTableWidgetItem(tr("%1").arg(result.values().at(0)(i)));
           ui->tableWidget_3->setItem(i,0,newItem);
    }


 QTableWidgetItem * newItem = new QTableWidgetItem("Weights");
    ui->tableWidget_3->setHorizontalHeaderItem(0,newItem);
     ui->tableWidget_3->setVerticalHeaderLabels(result.firstKey());


QString altLabel= "";
for (int i = 0; i < result.firstKey().size(); ++i) {
    altLabel.append(result.firstKey().at(i));
    if (i < result.firstKey().size() - 1) altLabel.append(" > ");
}
ui->labelAhpRes->setText(altLabel);
}
void MainWindow::on_pushButton_2_clicked()
{
    if (!_criteria || _criteria->getCriteriaList().size() == 0 || !_alterNames || _alterNames->size()== 0) return;
    ahp_method ahp(&_alternVec,_criteria);
    Decision decision = ahp.gm_method() ;
    QMap<QStringList,VectorXd> result = decision.sortAlternatives(*_alterNames);
    MatrixXd matrix_norm_weights = decision.getMatrix();
    VectorXd vector_weights = decision.getWeights();


    ui->tableWidget_2->setRowCount( matrix_norm_weights.rows());
    ui->tableWidget_2->setColumnCount(  matrix_norm_weights.cols());;
    for (int row = 0; row < matrix_norm_weights.rows(); ++row){

        for (int col = 0; col < matrix_norm_weights.cols();++col){
            QTableWidgetItem * newItem = new QTableWidgetItem(tr("%1").arg(matrix_norm_weights(row,col)));
            ui->tableWidget_2->setItem(row,col,newItem);
        }
    }
    ui->tableWidget_2->setVerticalHeaderLabels(*_alterNames);
     ui->tableWidget_2->setHorizontalHeaderLabels(_criteria->getCriteriaList());
    ui->tableWidget_4->setRowCount(vector_weights.size());
    ui->tableWidget_4->setColumnCount(1);
    for (int i = 0; i < vector_weights.size(); ++i){
           QTableWidgetItem * newItem = new QTableWidgetItem(tr("%1").arg(result.values().at(0)(i)));
           ui->tableWidget_4->setItem(i,0,newItem);
    }
    QTableWidgetItem * newItem = new QTableWidgetItem("Weights");
       ui->tableWidget_4->setHorizontalHeaderItem(0,newItem);
       ui->tableWidget_4->setVerticalHeaderLabels(result.firstKey());

    QString altLabel= "";
    for (int i = 0; i < result.firstKey().size(); ++i) {
    altLabel.append(result.firstKey().at(i));
    if (i < result.firstKey().size() - 1) altLabel.append(" > ");

}
   ui->labelGmRes->setText(altLabel);

}

void MainWindow::onRemoveAlternative(const QString &alterName)
{
    if ( _alterNames )
    {
        const int alterIdx = _alterNames->indexOf( alterName );
        for( CriteriaMatrix* pMatrix:  _alternVec)
        {
            pMatrix->removeRowCol( alterIdx );
            qDebug() << pMatrix->getSize();

            QStringList cl = pMatrix->getCriteriaList() ;
            cl.removeAll( alterName );
            pMatrix->setCriteriaList( cl );
        }
        _alterNames->removeAll( alterName );
    }

}

void MainWindow::onAddAlternativeName(const QString &alterName)
{
    if ( _alterNames )
    {
        _alterNames->push_back( alterName );
        for( CriteriaMatrix* pMatrix:  _alternVec)
        {
            pMatrix->addRowCol();
            qDebug() << pMatrix->getSize();
            QStringList cl = pMatrix->getCriteriaList() ;
            cl.push_back( alterName );
            pMatrix->setCriteriaList( cl );
        }
    }
}

