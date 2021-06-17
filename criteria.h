#ifndef CRITERIA_H
#define CRITERIA_H

#include <QString>
#include <Eigen/Dense>
#include <QList>

using namespace Eigen;


//struct Criteria
//{
//    QString name;
////    double  val;
//};

class CriteriaMatrix
{
    QString name;
    QStringList criteriaList;
    MatrixXd * m = nullptr;

public: 
    CriteriaMatrix(int size=1);
    ~CriteriaMatrix(){delete m;}

    QString getName() const;
    void setName(const QString &value);
    void printMatrix() const;
    double getCell( int row, int col) const;
    void setCell( int row, int col, double val);
    void setIdentity();
    void setMatOnes();
    void setSize(int s);
    int getSize() const;
    MatrixXd getMatrix() const;
    int getRows() const;
    int getCols() const;

    void addCriteria( const QString& critName  );
    void removeCriteria( const QString& critName  );
    int criteriaCount() const;
    QString criteriaName( int i );

    QStringList getCriteriaList() const;
    void setCriteriaList(const QStringList &value);

    void removeRowCol( int idx );
    void addRowCol();
};

#endif // CRITERIA_H
