package sdi.core.repository.custom;

import sdi.core.model.entities.Technician;

import java.util.List;

public interface TechnicianCustomRepository {
    List<Technician> getTechnicianWithFirstName(String firstName);
    List<Technician> getTechnicianWithLastName(String lastName);
}
