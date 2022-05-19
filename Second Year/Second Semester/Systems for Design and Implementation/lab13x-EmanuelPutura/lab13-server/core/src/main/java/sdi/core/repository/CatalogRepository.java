package sdi.core.repository;

import org.springframework.data.repository.PagingAndSortingRepository;
import sdi.core.model.BaseEntity;
import org.springframework.data.repository.NoRepositoryBean;

import java.io.Serializable;

@NoRepositoryBean
public interface CatalogRepository<T extends BaseEntity<ID>, ID extends Serializable>
        extends PagingAndSortingRepository<T, ID> {
}
