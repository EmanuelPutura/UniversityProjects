package sdi.core.service;

import sdi.core.model.Actor;

import java.util.List;

public interface ActorService {
    List<Actor> getAllActors();

    List<Actor> getAllAvailableActors();
}
