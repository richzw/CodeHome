// MachineStates.cpp
#include "MachineStates.h"

AbstractState::~AbstractState() {
}

void AbstractState::setState(Machine& machine, AbstractState* state) {
    AbstractState* aux = machine.mState;
    machine.mState = state; 
    delete aux;
}

void AbstractState::updateStock(Machine& machine, int quantity) {
    machine.mStockQuantity = quantity;
}

Normal::~Normal() {
}

void Normal::sell(Machine& machine, int quantity) {
    int currStock = machine.getCurrentStock();
    if (currStock < quantity) {
        throw std::runtime_error("Not enough stock");
    }

    updateStock(machine, currStock - quantity);

    if (machine.getCurrentStock() == 0) {
        setState(machine, new SoldOut());
    }
}

void Normal::refill(Machine& machine, int quantity) {
    int currStock = machine.getCurrentStock();
    updateStock(machine, currStock + quantity);
}

SoldOut::~SoldOut() {
}

void SoldOut::sell(Machine& machine, int quantity) {
    throw std::runtime_error("Sold out!");
}

void SoldOut::refill(Machine& machine, int quantity) {
    updateStock(machine, quantity);
    setState(machine, new Normal());
}
