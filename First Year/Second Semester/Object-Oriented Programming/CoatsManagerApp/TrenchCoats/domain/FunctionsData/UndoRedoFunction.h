#ifndef UNDOREDOFUNCTION_H
#define UNDOREDOFUNCTION_H

#include "IFunctionCall.h"

#include <bits/std_function.h>

class UndoRedoFunction {
private:
    IFunctionCall* undoFunction = nullptr;
    IFunctionCall* redoFunction = nullptr;
public:
    UndoRedoFunction();
    UndoRedoFunction(IFunctionCall* undoFunction, IFunctionCall* redoFunction);
    UndoRedoFunction(const UndoRedoFunction& function) = delete;
    void undo();
    void redo();

    ~UndoRedoFunction();
};

#endif // UNDOREDOFUNCTION_H
