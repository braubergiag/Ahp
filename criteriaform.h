#ifndef CRITERIAFORM_H
#define CRITERIAFORM_H

#include <QWidget>

namespace Ui {
class CriteriaForm;
}

class CriteriaMatrix;

class CriteriaForm : public QWidget
{
    Q_OBJECT

public:
    explicit CriteriaForm( CriteriaMatrix* pCriteria, QWidget *parent = nullptr);
    ~CriteriaForm();

signals:
    void formClosed();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_pushButton_3_clicked();

private:
    Ui::CriteriaForm *ui;

    CriteriaMatrix* _pCriteria;
};

#endif // CRITERIAFORM_H
