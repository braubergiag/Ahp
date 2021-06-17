#ifndef ALTERNATIVESDIALOG_H
#define ALTERNATIVESDIALOG_H

#include <QDialog>

namespace Ui {
class AlternativesDialog;
}

class CriteriaMatrix;

class AlternativesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlternativesDialog( const QStringList& alterNames,const QStringList& criteriaNames, QVector< CriteriaMatrix* >* alternVec, QWidget *parent = nullptr);
    ~AlternativesDialog();

    void setAlterNames(const QStringList &value);

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_tableWidget_cellChanged(int row, int column);

void on_buttonBox_accepted();

private:
    Ui::AlternativesDialog *ui;

    QStringList _alterNames;
    QStringList _criteriaNames;
    QVector< CriteriaMatrix* >* _alternVec;
    CriteriaMatrix* _currMatrix = nullptr;
    bool Flag = false;
};

#endif // ALTERNATIVESDIALOG_H
