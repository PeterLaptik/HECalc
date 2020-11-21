#ifndef INPUT_DATA_H_INCLUDED
#define INPUT_DATA_H_INCLUDED

#include "flow.h"

enum FlowDirection
{
    FLOW_SO_CURRENT, FLOW_COUNTER_CURRENT
};

// Input data container
class InputData
{
    public:
        static InputData& GetInstance()
        {
            static InputData instance;
            return instance;
        }

        Flow flow_1;
        Flow flow_2;
        FlowDirection direction;

    private:
        InputData()
        { };
        InputData(const InputData&);
        InputData& operator=(InputData&);
};

#endif // INPUT_DATA_H_INCLUDED
