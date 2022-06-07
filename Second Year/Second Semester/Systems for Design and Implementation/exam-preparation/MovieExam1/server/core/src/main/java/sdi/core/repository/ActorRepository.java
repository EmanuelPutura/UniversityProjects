package sdi.core.repository;

import sdi.core.model.Actor;

import java.util.List;

public interface ActorRepository extends MovieAppRepository<Actor, Long> {
    Actor findActorById(Long id);
}
