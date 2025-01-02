#ifndef __VM_H__
#define __VM_H__

class VM{
private:
    // your Privite members here

public:
    VM ();
    VM (const VM &a);
    VM & operator = (const VM &a);
    ~VM ();

    /*----------------------------------------------------------------------------*/
    std::string readFileToString(const std::string& filePath);
    
};

#endif

