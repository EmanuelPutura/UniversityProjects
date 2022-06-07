package sdi.web.controller;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import sdi.core.service.ActorService;
import sdi.web.converter.ActorConverter;
import sdi.web.dto.actor.ActorDtos;

@RestController
public class ActorController {
    private ActorService actorService;
    private ActorConverter actorConverter;

    @RequestMapping(value = "/actors/available")
    ActorDtos getAllAvailableActors() {
        return new ActorDtos(actorConverter.convertModelsToDtos(actorService.getAllAvailableActors()));
    }
}
