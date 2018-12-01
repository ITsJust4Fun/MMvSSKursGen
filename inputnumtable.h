#ifndef INPUTNUMTABLE_H
#define INPUTNUMTABLE_H
#include "inputtable.h"


class InputNumTable : public InputTable {
    Q_OBJECT
public:
    InputNumTable();
    virtual void initTable();
    virtual ~InputNumTable();
public slots:
    void changeData(int, int);
};

#endif // INPUTNUMTABLE_H
