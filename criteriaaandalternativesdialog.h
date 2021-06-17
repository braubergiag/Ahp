#ifndef CRITERIAAANDALTERNATIVESDIALOG_H
#define CRITERIAAANDALTERNATIVESDIALOG_H

#include <QDialog>

namespace Ui {
class CriteriaaAndAlternativesDialog;
}

class CriteriaaAndAlternativesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CriteriaaAndAlternativesDialog(QWidget *parent = nullptr);
    ~CriteriaaAndAlternativesDialog();


    QStringList alterNames();
    void setAlterNames(const QStringList &alterNames);

signals:
    void removeAlternative( const QString& alterName );
    void addAlternative( const QString& alterName );

private slots:
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

    void on_removePushButton_clicked();

private:
    Ui::CriteriaaAndAlternativesDialog *ui;

    QStringList  _alterNames;
};

#endif // CRITERIAAANDALTERNATIVESDIALOG_H
