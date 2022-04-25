#ifndef UNDOREDOSERVICE_H
#define UNDOREDOSERVICE_H

#include <infrastructure/Repository/Repository.h>
#include <domain/FunctionsData/UndoRedoFunction.h>

class UndoRedoService {
    /*
     *  UndoRedoService class
     *      Manages the undo/redo operations. Note that the repository whose reference is associated to the service
     *  contains pointers to dynamically allocated objects of type UndoRedoService. These objects are created in the
     *  UndoRedoService add() function, since it is the responsability of the service to delete them.
    */
private:
    Repository<UndoRedoFunction*> repository;
    int current_index = -1;
public:
    UndoRedoService(Repository<UndoRedoFunction*>& repository);

    void add(IFunctionCall* undoFunction, IFunctionCall* redoFunction);
    void undo();
    void redo();

    ~UndoRedoService();
};

#endif // UNDOREDOSERVICE_H
