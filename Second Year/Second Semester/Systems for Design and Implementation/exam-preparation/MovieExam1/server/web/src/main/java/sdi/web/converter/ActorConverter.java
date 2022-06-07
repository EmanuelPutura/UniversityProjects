package sdi.web.converter;

import org.springframework.stereotype.Component;
import sdi.core.model.Actor;
import sdi.web.dto.actor.ActorDto;

@Component
public class ActorConverter extends BaseConverter<Actor, ActorDto> {
    @Override
    public Actor convertDtoToModel(ActorDto dto) {
        var model = new Actor();

        model.setId(dto.getId());
        model.setName(dto.getName());
        model.setRating(dto.getRating());

        return model;
    }

    @Override
    public ActorDto convertModelToDto(Actor actor) {
        var dto = new ActorDto(actor.getName(), actor.getRating());
        dto.setId(actor.getId());
        return dto;
    }
}
