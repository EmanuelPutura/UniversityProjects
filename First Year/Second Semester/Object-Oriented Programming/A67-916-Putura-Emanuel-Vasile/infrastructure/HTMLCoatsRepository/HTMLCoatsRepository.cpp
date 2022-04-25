//
// Created by Emanuel on 16.04.2021.
//

#include "HTMLCoatsRepository.h"

void HTMLCoatsRepository::add(const TrenchCoat &element) {
    Repository<TrenchCoat>::add(element);
    writeToFile();
}

void HTMLCoatsRepository::remove(const TrenchCoat &element) {
    Repository<TrenchCoat>::remove(element);
    writeToFile();
}

void HTMLCoatsRepository::update(const TrenchCoat &element, const TrenchCoat &new_element) {
    Repository<TrenchCoat>::update(element, new_element);
    writeToFile();
}

void HTMLCoatsRepository::writeToFile() const {
    if (this->file_path == "") return;
    std::ofstream fout(this->file_path);
    if (fout.is_open()) {
        std::stringbuf buffer;
        std::ostream out(&buffer);

        out << "<!DOCTYPE html>\n<html>\n<head>\n\t<title>TrenchCoats Database</title>\n</head>\n<body>\n";
        out << "<table border=\"1\">\n\t<tr>\n\t\t<td>Size</td>\n\t\t<td>Colour</td>\n\t\t<td>Price</td>";
        out << "\n\t\t<td>Quantity</td>\n\t\t<td>Photograph Link</td>\n\t\t</tr>\n";

        out << "\t<tr>\n";
        for (const auto& el : this->data) {
            out << "\t<tr>\n";
            out << "\t\t<td>" << el.getSize() << "</td>\n\t\t<td>" << el.getColour() << "</td>\n\t\t<td>";;
            out << el.getPrice() << "</td>\n\t\t<td>" << el.getQuantity() << "</td>\n\t\t<td><a href=\"";
            out << el.getPhotograph() << "\">Link</a></td>\n\t</tr>\n";
        }

        out << "</table>\n</body>\n</html>";
        fout << buffer.str();

        fout.close();
    }
    else throw RepositoryException("The file cannot be opened.\n");
}