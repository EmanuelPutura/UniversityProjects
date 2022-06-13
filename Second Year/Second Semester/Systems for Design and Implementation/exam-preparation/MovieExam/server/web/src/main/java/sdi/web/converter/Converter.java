package sdi.web.converter;

import sdi.web.dto.BaseDto;
import sdi.core.model.BaseEntity;

public interface Converter<Model extends BaseEntity<Long>, Dto extends BaseDto> {
    Model convertDtoToModel(Dto dto);
    Dto convertModelToDto(Model model);
}
