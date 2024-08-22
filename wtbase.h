#pragma once

#ifndef XU_WTBASE_H_
#define XU_WTBASE_H_

#include <QAbstractScrollArea>

namespace xu {

class WtBase;

class WtBase : public QAbstractScrollArea
{

    Q_OBJECT

public:

    WtBase(QWidget *  parent = nullptr);
    virtual ~WtBase() noexcept;

protected:

private:
};

}

#endif
