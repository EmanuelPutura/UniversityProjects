package sdi.core.repository.impl;

import lombok.Getter;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

@Getter
public abstract class CustomRepositorySupport {
    @PersistenceContext
    private EntityManager entityManager;
}
