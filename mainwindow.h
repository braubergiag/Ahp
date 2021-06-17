#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "criteria.h"
#include "decision.h"
class  CriteriaForm;

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddCriteria();
    void onAddAlternative();
    void onAddCriteriaParams();
    void onCriteriaFormClosed();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void onRemoveAlternative( const QString& alterName );
    void onAddAlternativeName( const QString& alterName );


private:
    Ui::MainWindow *ui;

    CriteriaMatrix* _criteria = nullptr;
    QVector< CriteriaMatrix* > _alternVec;
    CriteriaForm* form = nullptr;
    QStringList * _alterNames = nullptr;

};

#endif // MAINWINDOW_H
