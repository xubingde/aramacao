#pragma once

#ifndef XU_WTBASE_H_
#define XU_WTBASE_H_

#include <QAbstractScrollArea>
#include <QStandardItem>

namespace xu {

class WtBase;

class WtBase : public QAbstractScrollArea
{

    Q_OBJECT

public:

    WtBase(QWidget *  parent = nullptr);
    virtual ~WtBase() noexcept;

    QStandardItem *  getItemPtr() const;
    void  setItemPtr(QStandardItem *  value);

protected:

private:

    QStandardItem *     m_itemPtr;
};

}

#endif
