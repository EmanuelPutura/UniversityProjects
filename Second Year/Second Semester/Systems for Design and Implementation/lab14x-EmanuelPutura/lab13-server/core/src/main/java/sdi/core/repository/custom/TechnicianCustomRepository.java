package sdi.core.repository.custom;

import sdi.core.model.entities.Technician;

import java.util.List;

public interface TechnicianCustomRepository {
    List<Technician> getTechniciansWithFirstName(String firstName);
    List<Technician> getTechniciansWithLastName(String lastName);
}
