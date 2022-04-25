//
// Created by Emanuel on 17.04.2021.
//

#ifndef DATABASECOATSREPOSITORY_H
#define DATABASECOATSREPOSITORY_H

#include "../Repository/Repository.h"
#include "../../domain/TrenchCoat/TrenchCoat.h"

#include <sqlite3.h>

class DatabaseCoatsRepository : public Repository<TrenchCoat> {
private:
    std::string database_path;
    sqlite3* database;

    /*
     * Callback function used for executing database queries and for obtaining the corresponding data
     */
    static int callback(void* data, int argc, char **argv, char **columnName);

    /*
     * Creates Coats table in the database
     */
    void createCoatsTable();

    /*
     * Opens the database connection
     */
    void open();

    /*
     * Closes the database connection
     */
    void close() const;

    /*
     * Executes a database query
     */
    const std::string execute(const std::string& query);

    /*
     * Reads all data from the database
     */
    void readFromDatabase();
public:
    DatabaseCoatsRepository(const std::string& database_path) : Repository<TrenchCoat>(), database_path(database_path) {}

    /**
     * Adds an element to the repository
     * @param element: the element to be added
     */
    void add(const TrenchCoat& element) override;

    /**
     * Removes an element from the repository
     * @param element: the element to be removed
     * @return: the index of the removed element or -1 if the element was not found
     */
    void remove(const TrenchCoat& element) override;

    /**
     * Gets the index of an element of the repository
     * @param element: the element to be searched for
     * @return: the index of the element or -1 if the element was not found
     */
    int getIndex(const TrenchCoat& element) override;

    /**
     * Updates an element of the repository
     * @param element: the element to be updated
     * @param new_element: the new value for the updated element
     * @return: the index of the element or -1 if the element was not found
     */
    void update(const TrenchCoat& element, const TrenchCoat& new_element) override;

    /**
     * [] operator overloading
     */
    const TrenchCoat& operator[](int index) override;

    /**
     * Getters
     */
    int getLength() override;
    const std::vector<TrenchCoat>& getData() override;
};

#endif
