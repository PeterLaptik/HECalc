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

        bool CheckData(void) const;

        std::string& GetMessage(void)
        {
            return msg;
        }

    private:
        InputData()
        { };
        InputData(const InputData&);
        InputData& operator=(InputData&);

        inline bool SetMessage(const std::string &message) const;
        inline bool IsCondensingOrBoiling(const Flow &flow) const;
        inline bool IsFlowUnknown(void) const;
        inline bool IsFlowHeating(const Flow &flow) const;

        mutable std::string msg;
};

#endif // INPUT_DATA_H_INCLUDED
