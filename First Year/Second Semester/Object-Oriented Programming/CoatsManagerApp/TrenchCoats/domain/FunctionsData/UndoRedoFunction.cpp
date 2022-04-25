#include "UndoRedoFunction.h"

UndoRedoFunction::UndoRedoFunction() {
}

UndoRedoFunction::UndoRedoFunction(IFunctionCall *undoFunction, IFunctionCall *redoFunction) : undoFunction(undoFunction), redoFunction(redoFunction) {
}

void UndoRedoFunction::undo() {
    undoFunction->call();
}

void UndoRedoFunction::redo() {
    redoFunction->call();
}

UndoRedoFunction::~UndoRedoFunction() {
    delete undoFunction;
    delete redoFunction;
}
