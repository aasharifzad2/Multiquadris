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
    void setCell(std::shared_ptr<Cell>);
    void setCell(int, std::shared_ptr<Cell>);
    
    std::shared_ptr<Cell> getCell(int) const;
    std::vector<std::shared_ptr<Cell>> getCells() const;
    
    bool isFilled();
    void clear();
    // Visitor Pattern : visit(Display)
    void display(Display &);
};


#endif
