package sdi.client.service;

import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;
import sdi.web.dto.technician.TechnicianDto;
import sdi.web.dto.technician.TechniciansDto;

import java.util.ArrayList;
import java.util.List;

@Service
public class TechnicianService implements CrudService<TechnicianDto> {
    private final String TECHNICIAN_API_URL = "http://localhost:8080/api/technicians";
    private final RestTemplate restTemplate;

    public TechnicianService(RestTemplate restTemplate) {
        this.restTemplate = restTemplate;
    }

    @Override
    public List<TechnicianDto> getAll() {
        TechniciansDto techniciansDto = restTemplate.getForObject(TECHNICIAN_API_URL, TechniciansDto.class);

        if (techniciansDto == null || techniciansDto.getTechnicians() == null)
            return null;

        return new ArrayList<>(techniciansDto.getTechnicians());
    }

    @Override
    public TechnicianDto save(TechnicianDto entity) {
        return restTemplate.postForObject(TECHNICIAN_API_URL, entity, TechnicianDto.class);
    }

    @Override
    public TechnicianDto update(TechnicianDto entity) {
        restTemplate.put(TECHNICIAN_API_URL + "/{id}", entity, entity.getId());
        return restTemplate.getForObject(TECHNICIAN_API_URL, TechnicianDto.class);
    }

    @Override
    public void deleteById(Long id) {
        restTemplate.delete(TECHNICIAN_API_URL + "/{id}", id);
    }
}
