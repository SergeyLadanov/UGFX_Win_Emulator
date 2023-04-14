#ifndef __MODEL_HPP_
#define __MODEL_HPP_

#include <cstdint>

class Model
{
private:

public:
    class Listener
    {
    protected:
        Model *ModelRef = nullptr;
    public:
        void BindModel(Model *model)
        {
            ModelRef = model;
        }

    };

    void Tick(void)
    {

    }
};


#endif