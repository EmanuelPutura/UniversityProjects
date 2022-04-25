#include "UndoRedoService.h"

#include <exceptions/ServiceException/ServiceException.h>

#include <qDebug>

UndoRedoService::UndoRedoService(Repository<UndoRedoFunction*> &repository) : repository(repository) {
}

void UndoRedoService::add(IFunctionCall *undoFunction, IFunctionCall *redoFunction) {
    auto *function = new UndoRedoFunction {undoFunction, redoFunction};
    auto data = repository.getData();

    int index = current_index + 1;
    while (index < repository.getLength()) {
        auto current_element = data[current_index + 1];
        repository.remove(current_element);
        delete current_element;
        index++;
    }

    repository.add(function);
    current_index++;
}

void UndoRedoService::undo() {
    if (current_index == -1)
        throw ServiceException("Cannot undo anymore!");

    auto data = repository.getData();
    data[current_index]->undo();
    current_index--;
}

void UndoRedoService::redo() {
    if (current_index + 1 == repository.getLength())
        throw ServiceException("Cannot redo anymore!");

    auto data = repository.getData();
    data[current_index + 1]->redo();
    current_index++;
}

UndoRedoService::~UndoRedoService() {
    auto data = repository.getData();
    for (const auto& function : data)
        delete function;
}
