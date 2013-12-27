#include "Mail.h"

Mail::Mail(const std::string& fileLoc)
{
   std::ofstream mailFile(fileLoc, std::ios::in);
   
   if( !mailFile.is_open() ){
       throw std::exception();
   }
   else{
       if(mailFile.good()){
           std::stringstream s;
           s << mailFile.rdbuf();
           mailData = s.str();
       }
       mailFile.close();
   }
}   

const std::string& Mail::getRawMailData() const
{
    return this->mailData;
}