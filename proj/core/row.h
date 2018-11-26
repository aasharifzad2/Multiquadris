#ifndef _row_h_
#define _row_h_


#include <vector>
#include <memory>
class Cell;
class Display;


class Row
{
    int rowNum;
    std::vector<std::shared_ptr<Cell>> cells;
    
    public:
    Row(int rowNum, int numCells);
    
    void setRowNum(int);
    void setCell(Cell *);
    void setCell(int, Cell *);
    
    Cell const * getCell(int) const;
    std::vector<const Cell *> getCells() const;
    
    bool isFilled();
    void clear();
    // Visitor Pattern : visit(Display)
    void display(Display &);
};


#endif
