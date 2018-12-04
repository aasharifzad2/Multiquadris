#ifndef _invalid_block_sequence_h_
#define _invalid_block_sequence_h_

#include <string>
#include "base_exception.h"

class invalid_block_char : public base_exception
{
    char invalidCharacter;
    
public:
    invalid_block_char(char);
    std::string message() const noexcept override;
};

#endif

