#include "criteria.h"

#include <QDebug>

QStringList CriteriaMatrix::getCriteriaList() const
{
    return criteriaList;
}

void CriteriaMatrix::setCriteriaList(const QStringList &value)
{
    criteriaList = value;
}

void CriteriaMatrix::removeRowCol(int idx)
{
    int size = m->rows();
    if (size > 1)
    {
        MatrixXd * tmpM = new MatrixXd( size - 1, size - 1 );
        int i = 0;
        for ( int row = 0; row <  size; ++row )
        {
            if ( row != idx )
            {
                int j = 0;
                for ( int  col = 0;col <  size; ++col )
                {
                    if ( col != idx )
                    {
                        (*tmpM)(i, j) = (*m)( row, col);
                        j++;
                    }
                }
                i++;
            }
        }
        delete m;
        m = tmpM;
    }
}

void CriteriaMatrix::addRowCol()
{
    const int size = m->rows();
    MatrixXd * tmpM = new MatrixXd( size + 1, size + 1 );
    tmpM->block( 0, 0, size, size) = m->block( 0, 0, size, size);
    delete m;
    m = tmpM;
    for ( int i = 0; i <= size; ++i)
    {
        (*m)( size, i) = 1;
        (*m)( i, size) = 1;
    }
}

CriteriaMatrix::CriteriaMatrix(int size) {
    if (size >= 1) m = new MatrixXd(size,size);
    else m = nullptr;

}

QString CriteriaMatrix::getName() const
{
    return name;
}

void CriteriaMatrix::setName(const QString &value)
{
    name = value;
}

void CriteriaMatrix::printMatrix() const
{
    MatrixXd mat = getMatrix();

}

int CriteriaMatrix::getSize() const
{
    return m->rows();
}

MatrixXd CriteriaMatrix::getMatrix() const
{
    return *m;
}

int CriteriaMatrix::getRows() const
{
    return m->rows();
}

int CriteriaMatrix::getCols() const
{
    return m->cols();
}

void CriteriaMatrix::addCriteria(const QString &critName)
{
  criteriaList.push_back( critName );
    // TODO:
}

void CriteriaMatrix::removeCriteria(const QString &critName)
{
    int idx = this->criteriaList.indexOf( critName );
    if ( idx > -1 )
    {
        removeRowCol(idx);
    }
    this->criteriaList.removeAll( critName );
}

int CriteriaMatrix::criteriaCount() const
{
    return criteriaList.count();
}

QString CriteriaMatrix::criteriaName(int i)
{
    return criteriaList.at(i);
}

double CriteriaMatrix::getCell(int row, int col) const
{
    if ( row >= m->rows() )
    {
        qDebug() << row;
    }
    if ( col >= m->cols() )
    {
        qDebug() << col;
    }


    return (*m)(row, col);
}

void CriteriaMatrix::setCell(int row, int col, double val)
{
    (*m)(row, col) = val;
}

void CriteriaMatrix::setIdentity()
{
    m->setIdentity();
}

void CriteriaMatrix::setMatOnes()
{
    m->setOnes();
}

void CriteriaMatrix::setSize(int s)
{
    delete m;
    m = new MatrixXd(s,s);
}

