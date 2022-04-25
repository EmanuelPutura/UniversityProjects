//
// Created by Emanuel on 17.04.2021.
//

#include "DatabaseCoatsRepository.h"

#include <sstream>
#include <iostream>

int DatabaseCoatsRepository::callback(void *data, int argc, char **argv, char **columnName) {
    auto records = static_cast<std::string*>(data);
    std::string current_data = "";

    try {
        for (size_t i = 0; i < argc; ++i)
            current_data += std::string(argv[i]) + " ";
        *records += current_data + "\n";
    }
    catch(...) {
        return 1;
    }

    return 0;
}

void DatabaseCoatsRepository::createCoatsTable() {
    std::string query = "CREATE TABLE Coats ("  \
      "SIZE     TEXT NOT NULL," \
      "COLOUR   TEXT NOT NULL," \
      "PRICE    INT  NOT NULL," \
      "QUANTITY INT  NOT NULL," \
      "LINK     TEXT NOT NULL );";
    execute(query);
}

void DatabaseCoatsRepository::open() {
    if (sqlite3_open(database_path.c_str(), &database)) {
        throw RepositoryException(std::string("Cannot open database: ") + sqlite3_errmsg(database));
    }
    try {
        createCoatsTable();
    }  catch (...) {}
}

void DatabaseCoatsRepository::close() const {
    sqlite3_close(database);
}

const std::string DatabaseCoatsRepository::execute(const std::string &query) {
    std::string data = "";
    char* error_message = nullptr;

    if (sqlite3_exec(database, query.c_str(), callback, (void*)(&data), &error_message) != SQLITE_OK) {
        std::string errors = "";
        if (error_message == nullptr)
            errors = "An error occurred.\n";
        else errors = std::string("SQL error: ") + error_message;

        try {
            sqlite3_free(error_message);
        } catch (...) {}
        throw RepositoryException(errors);
    }
    return data;
}

void DatabaseCoatsRepository::readFromDatabase() {
    auto data = execute("SELECT * from Coats");

    std::istringstream out(data);
    std::string line;

    this->data.clear();
    while (std::getline(out, line)) {
        std::stringstream buffer;
        TrenchCoat element;

        buffer << line;
        buffer >> element;
        this->data.push_back(element);
    }
}

void DatabaseCoatsRepository::add(const TrenchCoat &element) {
    open();
    readFromDatabase();

    std::string query = "INSERT INTO Coats (SIZE,COLOUR,PRICE,QUANTITY,LINK) VALUES ";
    query += "('" + element.getSize() + "', '" + element.getColour() + "', '" + std::to_string(element.getPrice()) + "', '";
    query += std::to_string(element.getQuantity()) + "', '" + element.getPhotograph() + "');";
    Repository<TrenchCoat>::add(element);

    open();
    execute(query);
    close();
}

void DatabaseCoatsRepository::remove(const TrenchCoat &element) {
    open();
    readFromDatabase();

    std::string query = "DELETE from Coats WHERE SIZE='" + element.getSize() + "' AND COLOUR='" + element.getColour() + "' AND";
    query += " PRICE=" + std::to_string(element.getPrice()) + " AND LINK='" + element.getPhotograph() + "';";
    Repository<TrenchCoat>::remove(element);

    open();
    execute(query);
    close();
}

void DatabaseCoatsRepository::update(const TrenchCoat &element, const TrenchCoat &new_element) {
    open();
    readFromDatabase();

    std::string query = "UPDATE COATS set SIZE='" + new_element.getSize() + "', COLOUR='" + new_element.getColour() + "',";
    query += " PRICE='" + std::to_string(new_element.getPrice()) + "', QUANTITY='" + std::to_string(new_element.getQuantity()) + "',";
    query += " LINK='" + new_element.getPhotograph() + "' WHERE SIZE='" + element.getSize() + "' AND COLOUR='" + element.getColour() + "' AND";
    query += " PRICE='" + std::to_string(element.getPrice()) + "' AND LINK='" + element.getPhotograph() + "';";
    Repository<TrenchCoat>::update(element, new_element);

    open();
    execute(query);
    close();
}

int DatabaseCoatsRepository::getIndex(const TrenchCoat &element) {
    open();
    readFromDatabase();
    close();
    return Repository<TrenchCoat>::getIndex(element);
}

const TrenchCoat &DatabaseCoatsRepository::operator[](int index) {
    open();
    readFromDatabase();
    close();
    return Repository<TrenchCoat>::operator[](index);
}

int DatabaseCoatsRepository::getLength() {
    open();
    readFromDatabase();
    close();
    return Repository<TrenchCoat>::getLength();
}

const std::vector<TrenchCoat> &DatabaseCoatsRepository::getData() {
    open();
    readFromDatabase();
    close();
    return Repository<TrenchCoat>::getData();
}
