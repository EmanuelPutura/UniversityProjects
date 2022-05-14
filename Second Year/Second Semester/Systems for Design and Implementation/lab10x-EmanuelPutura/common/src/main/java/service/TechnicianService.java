package service;

import domain.entities.Technician;

public interface TechnicianService extends GenericService<Long, Technician> {
    String GET_ALL = "getTechnicians";
    String SAVE_ONE = "saveTechnician";
    String UPDATE_ONE = "updateTechnician";
    String DELETE_ONE = "deleteTechnician";
}
