package sdi.core.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.NoRepositoryBean;
import sdi.core.model.BaseEntity;

import java.io.Serializable;

@NoRepositoryBean
public interface MovieAppRepository<T extends BaseEntity<ID>, ID extends Serializable> extends JpaRepository<T, ID> {
}
