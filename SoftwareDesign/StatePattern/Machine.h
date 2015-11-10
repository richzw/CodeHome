#include "MachineStates.h"

class AbstractState;
class Machine {
    friend class AbstractState;
    public:
        Machine(int inStockQuantity);
        void sell(int quantity);
        void refill(int quantity);
        int getCurrentStock();
        ~Machine();
    private:
        int mStockQuantity;
        AbstractState* mState;
};

