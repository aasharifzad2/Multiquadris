#ifndef _row_h_
#define _row_h_


#include <vector>
#include <memory>
#include "cell.h"

class Row
{
    int rowNum;
    std::vector<std::shared_ptr<Cell>> cells;
    
    public:
    Row(int rowNum, int numCells);
    void setRowNum(int);
    const std::shared_ptr<Cell> getCell(int) const;
    bool isFilled();
    void clear();
};

#endif
