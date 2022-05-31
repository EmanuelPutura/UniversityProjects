package sdi.core.repository.custom;

import sdi.core.model.entities.Technician;

import java.util.List;

public interface TechnicianCustomRepository {
    List<Technician> getTechnicianByFirstName(String firstName);
    List<Technician> getTechnicianByLastName(String lastName);
}
